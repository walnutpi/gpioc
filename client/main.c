#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>

#define PORT 10007           // 目标地址端口号
#define ADDR "192.168.2.131" // 目标地址IP

// 将传入的字符串发给server，并获得对方的返回值
// @return: 对方返回了多少个字节的数据
int run_commond(char *buf, int len)
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

    send(iSocketFD, buf, len, 0);
    int res = recv(iSocketFD, buf, 10, 0);
    if (res > 0)
        buf[res] = '\0';
    close(iSocketFD); // 关闭socket

    return res;
}

int main()
{
    // char buf[] = {"hello"};
    // char buf[] = {"pin_set_pullUpDn(42,2)"};
    // char buf[] = {"pin_set_pullUpDn(42,1)"};
    // char buf[] = {"pin_set_mode_by_name(42,\"IN\")"};
    char buf[] = {"pin_set_mode_by_name(42,\"OUT\")"};
    // char buf[] = {"pin_set_mode(42,1)"};
    // char buf[] = {"pin_set_mode(42,0)"};
    // char buf[] = {"pin_write(42,1)"};
    // char buf[] = {"pin_write(42,0)"};
    // char buf[] = {"pin_read(41)"};
    // char buf[] = {"pin_get_mode(12)"};
    run_commond(buf, strlen(buf));
    printf("buf={%s}\n", buf);
    return 0;
}

