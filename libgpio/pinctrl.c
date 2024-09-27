#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "socket.h"

#include "pinctrl-sunxi.h"

static int _ops_select = 0;

void (*chip_pin_set_mode[])(int, int) = {
    0,
    sunxi_pin_set_mode,
};

int (*chip_pin_get_mode[])(int) = {
    0,
    sunxi_pin_get_mode,
};

int (*chip_gpio_read[])(int) = {
    0,
    sunxi_gpio_read,
};

void (*chip_gpio_write[])(int, int) = {
    0,
    sunxi_gpio_write,
};

void (*chip_gpio_set_PullUpDn[])(int, int) = {
    0,
    sunxi_gpio_set_PullUpDn,
};

void (*chip_who_has_function[])(char *, int) = {
    0,
    sunxi_print_who_has_function,
};
const char *(*chip_gpio_pin_get_mode_name[])(int) = {
    0,
    sunxi_pin_get_mode_name,
};
const char *(*chip_gpio_pin_get_mode_name_by_num[])(int, int) = {
    0,
    sunxi_pin_get_mode_name_by_num,
};

int chip_detect()
{
    if (_ops_select == 0)
    {
        if (sunxi_init())
        {
            _ops_select = 1;
        }
    }

    return _ops_select;
}

int core_gpio_get_mode(int gpio_num)
{
    return chip_pin_get_mode[chip_detect()](gpio_num);
}

void core_gpio_set_mode(int gpio_num, int mode)
{
    chip_pin_set_mode[chip_detect()](gpio_num, mode);
}

void core_gpio_set_pullUpDn(int gpio_num, int pud)
{
    chip_gpio_set_PullUpDn[chip_detect()](gpio_num, pud);
}

int core_gpio_read(int gpio_num)
{
    return chip_gpio_read[chip_detect()](gpio_num);
}

void core_gpio_write(int gpio_num, int value)
{
    chip_gpio_write[chip_detect()](gpio_num, value);
}
void core_gpio_print_who_has_function(char *name_buf, int len)
{
    chip_who_has_function[chip_detect()](name_buf, len);
}
const char *core_gpio_pin_get_mode_name(int gpio_num)
{
    return chip_gpio_pin_get_mode_name[chip_detect()](gpio_num);
}
const char *core_gpio_pin_get_mode_name_by_num(int gpio_num, int mode_num)
{
    return chip_gpio_pin_get_mode_name_by_num[chip_detect()](gpio_num, mode_num);
}

/******************************************************************************/
/*如果是管理员权限运行，则调用上面的core系操作寄存器函数，不是则发送信息给server */
/******************************************************************************/
int gpio_get_mode(int gpio_num)
{
    if (geteuid() == 0)
        return core_gpio_get_mode(gpio_num);
    char buf[50];
    sprintf(buf, "gpio_get_mode(%d)", gpio_num);
    socket_run_command(buf, buf);
    return atoi(buf);
}

void gpio_set_mode(int gpio_num, int mode)
{
    if (geteuid() == 0)
        core_gpio_set_mode(gpio_num, mode);
    else
    {
        char buf[50];
        sprintf(buf, "gpio_set_mode(%d,%d)", gpio_num, mode);
        socket_run_command(buf, buf);
    }
}

void gpio_set_pullUpDn(int gpio_num, int pud)
{
    if (geteuid() == 0)
        core_gpio_set_pullUpDn(gpio_num, pud);
    else
    {
        char buf[50];
        sprintf(buf, "gpio_set_pullUpDn(%d,%d)", gpio_num, pud);
        socket_run_command(buf, buf);
    }
}

int gpio_read(int gpio_num)
{
    if (geteuid() == 0)
        return core_gpio_read(gpio_num);
    char buf[50];
    sprintf(buf, "gpio_read(%d)", gpio_num);
    socket_run_command(buf, buf);
    return atoi(buf);
}

void gpio_write(int gpio_num, int value)
{
    if (geteuid() == 0)
        core_gpio_write(gpio_num, value);
    else
    {
        char buf[50];
        sprintf(buf, "gpio_write(%d,%d)", gpio_num, value);
        socket_run_command(buf, buf);
    }
}
void gpio_print_who_has_function(char *name_buf, int len)
{
    if (geteuid() == 0)
        chip_who_has_function[chip_detect()](name_buf, len);
    else
    {
        char buf[50];
        sprintf(buf, "gpio_print_who_has_function(%s,%d)", name_buf, len);
        socket_run_command(buf, buf);
    }
}
const char *gpio_pin_get_mode_name(int gpio_num)
{
    if (geteuid() == 0)
        return core_gpio_pin_get_mode_name(gpio_num);
    char buf[50];
    sprintf(buf, "gpio_pin_get_mode_name(%d)", gpio_num);
    socket_run_command(buf, buf);
    char *str = (char *)malloc(strlen(buf));
    strncpy(str, buf, strlen(buf));
    return str;
}
const char *gpio_pin_get_mode_name_by_num(int gpio_num, int mode_num)
{
    if (geteuid() == 0)
        return core_gpio_pin_get_mode_name_by_num(gpio_num, mode_num);
    char buf[50];
    sprintf(buf, "gpio_pin_get_mode_name_by_num(%d,%d)", gpio_num, mode_num);
    socket_run_command(buf, buf);
    char *str = (char *)malloc(strlen(buf));
    strncpy(str, buf, strlen(buf));
    return str;
}