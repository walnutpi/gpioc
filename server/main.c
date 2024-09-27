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

int get_value1_int(char *buf, int len)
{
    int val = -1;
    for (int i = 0; i < len; i++)
    {
        if (buf[i] >= '0' && buf[i] <= '9')
        {
            if (val == -1)
                val = 0;
            val *= 10;
            val += buf[i] - '0';
        }
        else if (buf[i] != ' ')
            break;
    }
    return val;
}
int get_value2_int(char *buf, int len)
{
    buf = strchr(buf, ',');
    if (buf == NULL)
        return -1;
    return get_value1_int(buf + 1, len);
}
int get_value1_char(char *buf, int len, char *value)
{
    char *marks_l = strchr(buf, '\"') + 1;
    char *marks_r = strchr(marks_l + 1, '\"');
    if (marks_l == NULL || marks_r == NULL)
        return -1;
    int str_len = marks_r - marks_l;
    strncpy(value, marks_l, str_len);
    value[str_len] = '\0';
    return 0;
}
int get_value2_char(char *buf, int len, char *value)
{
    buf = strchr(buf, ',');
    if (buf == NULL)
        return -1;
    return get_value1_char(buf, len, value);
}

int call_fun(char *buf, int len, char *return_str)
{
    time_t timep;
    time(&timep);
    printf("%ld\t[%d] : {%s}\n", timep, len, buf, return_str);

    char *pvl = strchr(buf, '(');
    char *pvr = strchr(buf, ')');
    int value_len = pvr - pvl;
    if (pvl == NULL || pvr == NULL)
        return -1;
    pvl += 1;
    switch (pvl - buf)
    {
    // case sizeof("pin_set_mode"): //字符串长度相同
    case sizeof("pin_get_mode"):
        if ((strncmp(buf, "pin_get_mode", sizeof("pin_get_mode") - 1)) == 0)
        {
            int val1 = get_value1_int(pvl, value_len);
            if (val1 != -1)
                sprintf(return_str, "%d", pin_get_mode(val1));
        }
        if ((strncmp(buf, "pin_set_mode", sizeof("pin_set_mode") - 1)) == 0)
        {
            int val1 = get_value1_int(pvl, value_len);
            int val2 = get_value2_int(pvl, value_len);
            if (val1 != -1 && val2 != -1)
                pin_set_mode(val1, val2);
        }
        break;
    case sizeof("pin_set_mode_by_name"):
        if ((strncmp(buf, "pin_set_mode_by_name", sizeof("pin_set_mode_by_name") - 1)) == 0)
        {
            char val_str[30];
            int val1 = get_value1_int(pvl, value_len);
            int val2 = get_value2_char(pvl, value_len, val_str);
            if (val1 != -1 && val2 != -1)
                pin_set_mode_by_name(val1, val_str);
        }
        break;
    case sizeof("pin_set_pullUpDn"):
        if ((strncmp(buf, "pin_set_pullUpDn", sizeof("pin_set_pullUpDn") - 1)) == 0)
        {
            int val1 = get_value1_int(pvl, value_len);
            int val2 = get_value2_int(pvl, value_len);
            if (val1 != -1 && val2 != -1)
                pin_set_pullUpDn(val1, val2);
        }
        break;
    // case sizeof("gpio_read"):
    case sizeof("pin_write"):
        if ((strncmp(buf, "gpio_read", sizeof("gpio_read") - 1)) == 0)
        {
            int val1 = get_value1_int(pvl, value_len);
            if (val1 != -1)
                sprintf(return_str, "%d", gpio_read(val1));
        }
        if ((strncmp(buf, "pin_write", sizeof("pin_write") - 1)) == 0)
        {
            int val1 = get_value1_int(pvl, value_len);
            int val2 = get_value2_int(pvl, value_len);
            if (val1 != -1 && val2 != -1)
                pin_write(val1, val2);
        }
        break;
    case sizeof("pin_read"):
        if ((strncmp(buf, "pin_read", sizeof("pin_read") - 1)) == 0)
        {
            int val1 = get_value1_int(pvl, value_len);
            if (val1 != -1)
                sprintf(return_str, "%d", pin_read(val1));
        }
        break;
    case sizeof("pin_get_mode_name_now"):
        if ((strncmp(buf, "pin_get_mode_name_now", sizeof("pin_get_mode_name_now") - 1)) == 0)
        {
            int val1 = get_value1_int(pvl, value_len);
            if (val1 != -1)
                sprintf(return_str, "%s", pin_get_mode_name_now(val1));
        }
        break;
    case sizeof("pin_get_mode_name_by_num"):
        if ((strncmp(buf, "pin_get_mode_name_by_num", sizeof("pin_get_mode_name_by_num") - 1)) == 0)
        {
            int val1 = get_value1_int(pvl, value_len);
            int val2 = get_value2_int(pvl, value_len);
            if (val1 != -1 && val2 != -1)
                sprintf(return_str, "%s", pin_get_mode_name_by_num(val1, val2));
        }
        break;
        // case sizeof("gpio_set_mode"): //字符串长度相同
    case sizeof("gpio_get_mode"):
        if ((strncmp(buf, "gpio_get_mode", sizeof("gpio_get_mode") - 1)) == 0)
        {
            int val1 = get_value1_int(pvl, value_len);
            if (val1 != -1)
                sprintf(return_str, "%d", gpio_get_mode(val1));
        }
        if ((strncmp(buf, "gpio_set_mode", sizeof("gpio_set_mode") - 1)) == 0)
        {
            int val1 = get_value1_int(pvl, value_len);
            int val2 = get_value2_int(pvl, value_len);
            if (val1 != -1 && val2 != -1)
                gpio_set_mode(val1, val2);
        }
        break;
    case sizeof("gpio_set_pullUpDn"):
        if ((strncmp(buf, "gpio_set_pullUpDn", sizeof("gpio_set_pullUpDn") - 1)) == 0)
        {
            int val1 = get_value1_int(pvl, value_len);
            int val2 = get_value2_int(pvl, value_len);
            if (val1 != -1 && val2 != -1)
                gpio_set_pullUpDn(val1, val2);
        }
        break;
    case sizeof("gpio_write"):
        if ((strncmp(buf, "gpio_write", sizeof("gpio_write") - 1)) == 0)
        {
            int val1 = get_value1_int(pvl, value_len);
            int val2 = get_value2_int(pvl, value_len);
            if (val1 != -1 && val2 != -1)
                gpio_write(val1, val2);
        }
        break;
    case sizeof("gpio_pin_get_mode_name"):
        if ((strncmp(buf, "gpio_pin_get_mode_name", sizeof("gpio_pin_get_mode_name") - 1)) == 0)
        {
            int val1 = get_value1_int(pvl, value_len);
            if (val1 != -1)
                sprintf(return_str, "%s", gpio_pin_get_mode_name(val1));
        }
        break;
    case sizeof("gpio_pin_get_mode_name_by_num"):
        if ((strncmp(buf, "gpio_pin_get_mode_name_by_num", sizeof("gpio_pin_get_mode_name_by_num") - 1)) == 0)
        {
            int val1 = get_value1_int(pvl, value_len);
            int val2 = get_value2_int(pvl, value_len);
            if (val1 != -1 && val2 != -1)
                sprintf(return_str, "%s", gpio_pin_get_mode_name_by_num(val1, val2));
        }
        break;
    // case sizeof("soft_pwm_get_duty_cycle"):
    // case sizeof("soft_pwm_set_duty_cycle"):
    //     if ((strncmp(buf, "soft_pwm_set_duty_cycle", sizeof("soft_pwm_set_duty_cycle") - 1)) == 0)
    //     {
    //         int val1 = get_value1_int(pvl, value_len);
    //         int val2 = get_value2_int(pvl, value_len);
    //         if (val1 != -1 && val2 != -1)
    //             soft_pwm_set_duty_cycle(val1, val2);
    //     }
    //     if ((strncmp(buf, "soft_pwm_get_duty_cycle", sizeof("soft_pwm_get_duty_cycle") - 1)) == 0)
    //     {
    //         int val1 = get_value1_int(pvl, value_len);
    //         if (val1 != -1)
    //             sprintf(return_str, "%d", soft_pwm_get_duty_cycle(val1));
    //     }
    //     break;
    // // case sizeof("soft_pwm_get_frequency"):
    // case sizeof("soft_pwm_set_frequency"):
    //     if ((strncmp(buf, "soft_pwm_set_frequency", sizeof("soft_pwm_set_frequency") - 1)) == 0)
    //     {
    //         int val1 = get_value1_int(pvl, value_len);
    //         int val2 = get_value2_int(pvl, value_len);
    //         if (val1 != -1 && val2 != -1)
    //             soft_pwm_set_frequency(val1, val2);
    //     }
    //     if ((strncmp(buf, "soft_pwm_get_frequency", sizeof("soft_pwm_get_frequency") - 1)) == 0)
    //     {
    //         int val1 = get_value1_int(pvl, value_len);
    //         if (val1 != -1)
    //             sprintf(return_str, "%d", soft_pwm_get_frequency(val1));
    //     }
    //     break;
    // case sizeof("soft_pwm_start"):
    //     if ((strncmp(buf, "soft_pwm_start", sizeof("soft_pwm_start") - 1)) == 0)
    //     {
    //         int val1 = get_value1_int(pvl, value_len);
    //         if (val1 != -1)
    //             soft_pwm_start(val1);
    //     }
    //     break;
    // case sizeof("soft_pwm_stop"):
    //     if ((strncmp(buf, "soft_pwm_stop", sizeof("soft_pwm_stop") - 1)) == 0)
    //     {
    //         int val1 = get_value1_int(pvl, value_len);
    //         if (val1 != -1)
    //             soft_pwm_stop(val1);
    //     }
    //     break;
    // case sizeof("soft_pwm_exists"):
    //     if ((strncmp(buf, "soft_pwm_exists", sizeof("soft_pwm_exists") - 1)) == 0)
    //     {
    //         int val1 = get_value1_int(pvl, value_len);
    //         if (val1 != -1)
    //             sprintf(return_str, "%d", soft_pwm_exists(val1));
    //     }
    default:
        break;
    }
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