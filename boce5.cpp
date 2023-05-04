#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "speed_test.h"
#define PING_PACKET_SIZE 64 //定义要发送的ping数据包的大小
#define PING_NUM_PACKETS 5 //定义ping命令执行次数 

using namespace std;

int ping_test(char *ip_address){
    //-----------------------------------------------------------------------------------------------------------
    //ping指令测试
    //构造ping命令
    char ping_cmd[100];
    sprintf(ping_cmd, "ping -c %d %s",PING_NUM_PACKETS, ip_address); //对输入的域名ping10次，将语句保存到ping_cmd中

    //执行ping命令并读取输出
    FILE *fp = popen(ping_cmd, "r"); // 执行ping命令，并将输出已fopen函数保存在fp中
    if (fp == NULL) {
        printf("popen() failed\n");
        return -1;
    }
    char output[200];
    int i = 0;
    int num_trans, num_recv, num_loss, time;
    float min_rtt, avg_rtt, max_rtt, mdev_rtt;
    while (fgets(output, sizeof(output), fp)!= NULL) { // 每次读取一行 存储在output中
        if(i>PING_NUM_PACKETS+2){
            if (sizeof(output)>1){
                sscanf(output,"%d packets transmitted, %d received, %d%% packet loss, time %d ms",
                &num_trans,
                &num_recv,
                &num_loss,
                &time);
                sscanf(output,"rtt min/avg/max/mdev = %f/%f/%f/%f ms",
                &min_rtt,
                &avg_rtt,
                &max_rtt,
                &mdev_rtt);
            }

        }
        i++;
        
    }
    pclose(fp);
    printf("---------------------------共测试 %d 次----------------------------\n\n", PING_NUM_PACKETS);
    printf("共发送数据：%d 次\n \n 成功接收:% d次\n 丢包率为:%d%%\n 共耗时:%d 毫秒\n\n",
                num_trans,
                num_recv,
                num_loss,
                time);
    printf("-------------------------------------------------------------------\n\n");
    printf(" 最小延迟为%f 毫秒\n 平均延迟为%f 毫秒\n 最大延迟为%f 毫秒\n 平均抖动为%f 毫秒",
                min_rtt,
                avg_rtt,
                max_rtt,
                mdev_rtt);
    printf("-------------------------------------------------------------------\n\n");

    //-----------------------------------------------------------------------------------------------------------
    return 0;
}

// int catch_packet(char *ip_address){
    
// }
int main(int argc, char *argv[]) {
    if (argc!=2) {
        printf("Usage: %s ip\n", argv[0]);
        return -1;
    }
    ping_test(argv[1]);
    int a = speedtest();

    return 0;
}

