#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include "socket.h"

#include "pinctrl-sunxi/pinctrl-sunxi.h"

struct chip_ops
{
    bool (*init)(void);
    void (*pin_set_mode)(int gpio_num, int mode);
    int (*pin_get_mode)(int gpio_num);
    int (*gpio_read)(int gpio_num);
    void (*gpio_write)(int gpio_num, int value);
    void (*gpio_set_PullUpDn)(int gpio_num, int pud);
    void (*who_has_function)(char *name_buf, int len);
    const char *(*gpio_pin_get_mode_name)(int gpio_num);
    const char *(*gpio_pin_get_mode_name_by_num)(int gpio_num, int mode_num);
    void (*mode_rename)(int gpio_num, int mode_num, char *name);
};
struct chip_ops ops_list[] = {
    {
        .init = sunxi_init,
        .pin_set_mode = sunxi_pin_set_mode,
        .pin_get_mode = sunxi_pin_get_mode,
        .gpio_read = sunxi_gpio_read,
        .gpio_write = sunxi_gpio_write,
        .gpio_set_PullUpDn = sunxi_gpio_set_PullUpDn,
        .who_has_function = sunxi_print_who_has_function,
        .gpio_pin_get_mode_name = sunxi_pin_get_mode_name,
        .gpio_pin_get_mode_name_by_num = sunxi_pin_get_mode_name_by_num,
        .mode_rename = sunxi_gpio_mode_rename,
    },

};
static int _ops_select = 0;
struct chip_ops *get_chip_ops()
{
    if (_ops_select == 0)
    {
        for (int i = 0; i < sizeof(ops_list) / sizeof(struct chip_ops); i++)
        {
            if (ops_list[i].init && ops_list[i].init())
            {
                _ops_select = i;
                break;
            }
        }
    }
    return &ops_list[_ops_select];
}

int core_gpio_get_mode(int gpio_num)
{
    return get_chip_ops()->pin_get_mode(gpio_num);
}

void core_gpio_set_mode(int gpio_num, int mode)
{
    get_chip_ops()->pin_set_mode(gpio_num, mode);
}

void core_gpio_set_pullUpDn(int gpio_num, int pud)
{
    get_chip_ops()->gpio_set_PullUpDn(gpio_num, pud);
}

int core_gpio_read(int gpio_num)
{
    return get_chip_ops()->gpio_read(gpio_num);
}

void core_gpio_write(int gpio_num, int value)
{
    get_chip_ops()->gpio_write(gpio_num, value);
}
void core_gpio_print_who_has_function(char *name_buf, int len)
{
    get_chip_ops()->who_has_function(name_buf, len);
}
const char *core_gpio_pin_get_mode_name(int gpio_num)
{
    return get_chip_ops()->gpio_pin_get_mode_name(gpio_num);
}
const char *core_gpio_pin_get_mode_name_by_num(int gpio_num, int mode_num)
{
    return get_chip_ops()->gpio_pin_get_mode_name_by_num(gpio_num, mode_num);
}
void gpio_mode_rename(int gpio_num, int mode_num, char *name)
{
    get_chip_ops()->mode_rename(gpio_num, mode_num, name);
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
    {
        core_gpio_set_mode(gpio_num, mode);
    }
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
        core_gpio_print_who_has_function(name_buf, len);
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
