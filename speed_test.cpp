#include <iostream>
#include <stdio.h>
#include "speed_test.h"
using namespace std;
// speedtest-cli
// Retrieving speedtest.net configuration...
// Testing from China Telecom (222.171.151.227)...
// Retrieving speedtest.net server list...
// Selecting best server based on ping...
// Hosted by Unicom (Shenyang) [661.75 km]: 47.581 ms
// Testing download speed................................................................................
// Download: 8.09 Mbit/s
// Testing upload speed......................................................................................................
// Upload: 10.09 Mbit/s
int speedtest(){//test speed of our device
    //using speed-sci tests
    char ping_cmd[100];
    sprintf(ping_cmd,"speedtest-cli");

    FILE *fp = popen(ping_cmd, "r");
    if (fp == NULL) {
        printf("popen() failed\n");
        return -1;
    }
    char output[200];
    char country[20];
    char yunyingshang[8];
    int ip1,ip2,ip3,ip4;
    char best_host[30];
    char e_best_host[30];
    float distances, time;
    float down_speed, up_speed;

    while (fgets(output, sizeof(output), fp))
    {
        // printf("%s", output);
        sscanf(output,"Testing from %s %s (%d.%d.%d.%d)...",country,yunyingshang,&ip1,&ip2,&ip3,&ip4);
        sscanf(output,"Hosted by %s %s [%f km]: %f ms",best_host,e_best_host, &distances, &time);
        sscanf(output,"Download: %f Mbit/s",&down_speed);
        sscanf(output,"Upload: %f Mbit/s",&up_speed);
    }
    printf("使用的运营商为:%s %s IP地址为:%d.%d.%d.%d\n\n",country,yunyingshang,ip1,ip2,ip3,ip4);
    printf("最佳延迟服务器:%s%s    距离:%f公里   延迟:%f毫秒\n\n",best_host,e_best_host, distances, time);
    printf("下载速度为: %.2f Mbit/s\n\n",down_speed);
    printf("上传速度为: %.2f Mbit/s\n\n",up_speed);
    return 0;

}