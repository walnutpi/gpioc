
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>

#define PORT 10007           // 目标地址端口号
#define ADDR "127.0.0.1" // 目标地址

// 将传入的字符串发给server，并获得对方的返回值
// @return: 对方返回了多少个字节的数据
// cmd:要发送过去的字符串命令
// res:会将收到的返回值传入这个指针对应区域
int socket_run_command(char *cmd, char *ret)
{
    int iSocketFD = 0; // socket句柄
    unsigned int iRemoteAddr = 0;
    socklen_t socklen = 0;

    // 创建socket
    iSocketFD = socket(AF_INET, SOCK_STREAM, 0);
    if (0 > iSocketFD)
    {
        printf("创建socket失败\n");
        return -1;
    }

    // 设置socket
    struct sockaddr_in stRemoteAddr = {0};
    stRemoteAddr.sin_family = AF_INET;
    stRemoteAddr.sin_port = htons(PORT);
    inet_pton(AF_INET, ADDR, &iRemoteAddr);
    stRemoteAddr.sin_addr.s_addr = iRemoteAddr;
    while (1)
    {

        if (0 > connect(iSocketFD, (void *)&stRemoteAddr, sizeof(stRemoteAddr)))
        {
            printf("连接失败！\n");
            sleep(1);
        }
        else
            break;
    }

    send(iSocketFD, cmd, strlen(cmd), 0);
    int res = recv(iSocketFD, ret, 10, 0);
    if (res > 0)
        ret[res] = '\0';
    close(iSocketFD); // 关闭socket
    return res;
}