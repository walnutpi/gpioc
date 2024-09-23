#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <time.h>
#include <string.h>
#include "../libgpio/board.h"

#define PORT 10007 // 端口号
#define BACKLOG 1  // 最大监听数

// str:函数名
// buf:要匹配的字符串
// len:buf的大小
// fun:目标函数
int call_cmd_int_fun_int(char *str, char *buf, int len, int (*fun)(int), char *return_str)
{
    if ((strncmp(buf, str, strlen(str) - 1)) == 0)
    {
        int val = 0;

        char *pl = strchr(buf, '(');
        char *pr = strrchr(buf, ')');
        val = -1;
        for (char *p = pl + 1; p < pr; p++)
        {
            if ((*p) > '0' && (*p) < '9')
            {
                if (val == -1)
                    val = 0;
                val *= 10;
                val += (*p) - '0';
            }
            else if ((*p) != ' ')
                break;
        }

        if (val != -1)
        {
            int re = fun(val);
            sprintf(return_str, "%d", re);
            return re;
        }
    }
    return -1;
}
int call_cmd_void_fun_int_int(const char *str, char *buf, int len, void (*fun)(int, int))
{

    if ((strncmp(buf, str, strlen(str) - 1)) == 0)
    {
        int val1, val2;
        // get_int_2_value(&(buf[strlen(str)]) - 1, len - strlen(str), &val1, &val2);
        char *pl = strchr(buf, '(');
        char *pr = strrchr(buf, ')');
        val1 = -1;
        val2 = -1;
        for (char *p = pl + 1; p < pr; p++)
        {
            if ((*p) >= '0' && (*p) <= '9')
            {
                if (val1 == -1)
                    val1 = 0;
                val1 *= 10;
                val1 += (*p) - '0';
            }
            else if ((*p) != ' ')
            {
                pl = p;
                break;
            }
        }
        for (pl += 1; pl < pr; pl++)
        {
            if ((*pl) >= '0' && (*pl) <= '9')
            {
                if (val2 == -1)
                    val2 = 0;
                val2 *= 10;
                val2 += (*pl) - '0';
            }
            else if ((*pl) != ' ')
                break;
        }

        if (val2 != -1)
            fun(val1, val2);
        return 0;
    }
    return -1;
}

// pin_set_mode_by_name(41,"IN")
int call_cmd_void_fun_int_char(const char *str, char *buf, int len, void (*fun)(int, char *))
{
    if ((strncmp(buf, str, strlen(str) - 1)) == 0)
    {
        int val1, val2;
        char para2[20];
        char *pl = strchr(buf, '(');
        char *pr = strrchr(buf, ')');
        val1 = -1;
        val2 = -1;
        for (char *p = pl + 1; p < pr; p++)
        {
            if ((*p) >= '0' && (*p) <= '9')
            {
                if (val1 == -1)
                    val1 = 0;
                val1 *= 10;
                val1 += (*p) - '0';
            }
            else if ((*p) != ' ')
            {
                pl = p;
                break;
            }
        }
        char *marks_l = strchr(buf, '\"') + 1;
        char *marks_r = strrchr(buf, '\"');
        int str_len = marks_r - marks_l;
        strncpy(para2, marks_l, str_len);
        para2[str_len] = '\0';
        printf("str_len=%d\n", str_len);
        printf("val1=%d, para2=%s\n", val1, para2);
        if (str_len > 0)
            fun(val1, para2);
        return 0;
    }
    return -1;
}

int call_fun(char *buf, int len, char *return_str)
{
    time_t timep;
    time(&timep);
    printf("%ld\t[%d] : {%s}\n", timep, len, buf, return_str);
    call_cmd_int_fun_int("pin_get_mode", buf, len, pin_get_mode, return_str);
    call_cmd_void_fun_int_int("pin_set_mode", buf, len, pin_set_mode);
    call_cmd_void_fun_int_char("pin_set_mode_by_name", buf, len, pin_set_mode_by_name);
    call_cmd_void_fun_int_int("pin_set_pullUpDn", buf, len, pin_set_pullUpDn);
    call_cmd_void_fun_int_int("pin_write", buf, len, pin_write);
    call_cmd_int_fun_int("pin_read", buf, len, pin_read, return_str);
}

int run_listen()
{

    int iSocketFD = 0;                     // socket句柄
    int iRecvLen = 0;                      // 接收成功后的返回值
    int new_fd = 0;                        // 建立连接后的句柄
    char buf[4096] = {0};                  //
    struct sockaddr_in stRemoteAddr = {0}; // 对方地址信息
    socklen_t socklen = 0;

    // 创建socket
    iSocketFD = socket(AF_INET, SOCK_STREAM, 0);
    if (0 > iSocketFD)
    {
        printf("创建socket失败\n");
        return 0;
    }

    // 设置socket
    struct sockaddr_in stLocalAddr = {0};
    stLocalAddr.sin_family = AF_INET;                // 接收本机或其他机器传输
    stLocalAddr.sin_port = htons(PORT);              // 端口
    stLocalAddr.sin_addr.s_addr = htonl(INADDR_ANY); // 监听ip
    if (0 > bind(iSocketFD, (void *)&stLocalAddr, sizeof(stLocalAddr)))
    {
        printf("绑定失败！\n");
        return 0;
    }

    // 开启监听
    if (0 > listen(iSocketFD, BACKLOG))
    {
        printf("监听失败！\n");
        return 0;
    }

    printf("iSocketFD: %d\n", iSocketFD);
    while (1)
    {
        // 阻塞直到接收到消息，参数分别是socket句柄，接收到的地址信息以及大小
        new_fd = accept(iSocketFD, (void *)&stRemoteAddr, &socklen);
        if (new_fd < 0)
        {
            printf("接收失败！\n");
            continue;
        }

        iRecvLen = recv(new_fd, buf, 100, 0);
        if (0 >= iRecvLen) // 对端关闭连接 返回0
        {
            printf("接收失败或者对端关闭连接！\n");
        }
        else
        {
            buf[iRecvLen] = '\0';
            char re[20] = {"NULL"};
            call_fun(buf, iRecvLen, re);
            send(new_fd, re, strlen(re), 0);
        }
        close(new_fd);
    }

    close(iSocketFD);
}

int main()
{
    run_listen();
    // char buf[] = {"pin_read(41)\n"};
    // // char buf[] = {"pin_write(42,0)\n"};
    // // char buf[] = {"pin_set_mode(5,1)\n"};
    // // char buf[] = {"pin_get_mode ( 41)\n"};
    // char re[20] = {"NULL"};
    // call_fun(buf, strlen(buf), re);
    // printf("re:%s\n", re);
    return 0;
}