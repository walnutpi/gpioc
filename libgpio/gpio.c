#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>

#include "../core/board.h"

#define PORT 10007           // 目标地址端口号
#define ADDR "127.0.0.1" // 目标地址

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
int pin_get_mode(int pin_num)
{
    if (geteuid() == 0)
        return board_pin_get_mode(pin_num);
    char buf[50];
    sprintf(buf, "pin_get_mode(%d)", pin_num);
    run_commond(buf, strlen(buf));
    return atoi(buf);
}
void pin_set_mode(int pin_num, int mode)
{
    if (geteuid() == 0)
        board_pin_set_mode(pin_num, mode);
    else
    {
        char buf[50];
        sprintf(buf, "pin_set_mode(%d,%d)", pin_num, mode);
        run_commond(buf, strlen(buf));
    }
}
void pin_set_mode_by_name(int pin_num, char *mode)
{
    if (geteuid() == 0)
        board_pin_set_mode_by_name(pin_num, mode);
    else
    {
        char buf[50];
        sprintf(buf, "pin_set_mode_by_name(%d,\"%s\")", pin_num, mode);
        run_commond(buf, strlen(buf));
    }
}
void pin_set_pullUpDn(int pin_num, int pud)
{
    if (geteuid() == 0)
        board_pin_set_pullUpDn(pin_num, pud);
    else
    {
        char buf[50];
        sprintf(buf, "pin_set_pullUpDn(%d,%d)", pin_num, pud);
        run_commond(buf, strlen(buf));
    }
}
int pin_read(int pin_num)
{
    if (geteuid() == 0)
        return board_pin_read(pin_num);
    char buf[50];
    sprintf(buf, "pin_read(%d)", pin_num);
    run_commond(buf, strlen(buf));
    return atoi(buf);
}
void pin_write(int pin_num, int value)
{
    if (geteuid() == 0)
        board_pin_write(pin_num, value);
    else
    {
        char buf[50];
        sprintf(buf, "pin_write(%d,%d)", pin_num, value);
        run_commond(buf, strlen(buf));
    }
}
const char *pin_get_mode_name_now(int pin_num)
{
    if (geteuid() == 0)
        return board_pin_get_mode_name_now(pin_num);
    char buf[50];
    sprintf(buf, "pin_get_mode_name_now(%d)", pin_num);
    run_commond(buf, strlen(buf));
    char *str = (char *)malloc(strlen(buf));
    strncpy(str, buf, strlen(buf));
    return str;
}
const char *pin_get_mode_name_by_num(int pin_num, int mode_num)
{
    if (geteuid() == 0)
        return board_pin_get_mode_name_by_num(pin_num, mode_num);
    char buf[50];
    sprintf(buf, "pin_get_mode_name_by_num(%d,%d)", pin_num, mode_num);
    run_commond(buf, strlen(buf));
    char *str = (char *)malloc(strlen(buf));
    strncpy(str, buf, strlen(buf));
    return str;
}

void soft_pwm_set_duty_cycle(int pin_num, int dutycycle)
{
    if (geteuid() == 0)
        soft_pwm_set_duty_cycle(pin_num, dutycycle);
    else
    {
        char buf[50];
        sprintf(buf, "soft_pwm_set_duty_cycle(%d,%d)", pin_num, dutycycle);
        run_commond(buf, strlen(buf));
    }
}
void soft_pwm_set_frequency(int pin_num, int freq)
{
    if (geteuid() == 0)
        soft_pwm_set_frequency(pin_num, freq);
    else
    {
        char buf[50];
        sprintf(buf, "soft_pwm_set_frequency(%d,%d)", pin_num, freq);
        run_commond(buf, strlen(buf));
    }
}
int soft_pwm_get_duty_cycle(int pin_num)
{
    if (geteuid() == 0)
        return soft_pwm_get_duty_cycle(pin_num);
    char buf[50];
    sprintf(buf, "soft_pwm_get_duty_cycle(%d)", pin_num);
    run_commond(buf, strlen(buf));
    return atoi(buf);
}
int soft_pwm_get_frequency(int pin_num)
{
    if (geteuid() == 0)
        return soft_pwm_get_frequency(pin_num);
    char buf[50];
    sprintf(buf, "soft_pwm_get_frequency(%d)", pin_num);
    run_commond(buf, strlen(buf));
    return atoi(buf);
}
void soft_pwm_start(int pin_num)
{
    if (geteuid() == 0)
        soft_pwm_start(pin_num);
    else
    {
        char buf[50];
        sprintf(buf, "soft_pwm_start(%d)", pin_num);
        run_commond(buf, strlen(buf));
    }
}
void soft_pwm_stop(int pin_num)
{

    if (geteuid() == 0)
        soft_pwm_stop(pin_num);
    else
    {
        char buf[50];
        sprintf(buf, "soft_pwm_stop(%d)", pin_num);
        run_commond(buf, strlen(buf));
    }
}
int soft_pwm_exists(int pin_num)
{
    if (geteuid() == 0)
        return soft_pwm_exists(pin_num);
    char buf[50];
    sprintf(buf, "soft_pwm_exists(%d)", pin_num);
    run_commond(buf, strlen(buf));
    return atoi(buf);
}
