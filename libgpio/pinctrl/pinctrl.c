#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include "socket.h"

#include "sunxi/pinctrl-sunxi.h"
#include "k230/pinctrl-k230.h"

struct chip_ops
{
    bool (*init)(void);
    void (*pin_set_mode)(int chip_gpio_num, int mode);
    int (*pin_get_mode)(int chip_gpio_num);
    int (*pinctrl_read)(int chip_gpio_num);
    void (*pinctrl_write)(int chip_gpio_num, int value);
    void (*pinctrl_set_pullUpDn)(int chip_gpio_num, int pud);
    void (*who_has_function)(char *name_buf, int len);
    const char *(*pinctrl_pin_get_mode_name)(int chip_gpio_num);
    const char *(*pinctrl_pin_get_mode_name_by_num)(int chip_gpio_num, int mode_num);
    void (*mode_rename)(int chip_gpio_num, int mode_num, char *name);
};
struct chip_ops ops_list[] = {
    {
        .init = sunxi_init,
        .pin_set_mode = sunxi_pin_set_mode,
        .pin_get_mode = sunxi_pin_get_mode,
        .pinctrl_read = sunxi_pinctrl_read,
        .pinctrl_write = sunxi_pinctrl_write,
        .pinctrl_set_pullUpDn = sunxi_pinctrl_set_pullUpDn,
        .who_has_function = sunxi_print_who_has_function,
        .pinctrl_pin_get_mode_name = sunxi_pin_get_mode_name,
        .pinctrl_pin_get_mode_name_by_num = sunxi_pin_get_mode_name_by_num,
        .mode_rename = sunxi_pinctrl_mode_rename,
    },
    {
        .init = k230_init,
        .pin_set_mode = k230_pin_set_mode,
        .pin_get_mode = k230_pin_get_mode,
        .pinctrl_read = k230_pinctrl_read,
        .pinctrl_write = k230_pinctrl_write,
        .pinctrl_set_pullUpDn = k230_pinctrl_set_pullUpDn,
        .who_has_function = k230_who_has_function,
        .pinctrl_pin_get_mode_name = k230_pinctrl_pin_get_mode_name,
        .pinctrl_pin_get_mode_name_by_num = k230_pinctrl_pin_get_mode_name_by_num,
        .mode_rename = k230_mode_rename,
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

int core_pinctrl_get_mode(int chip_gpio_num)
{
    return get_chip_ops()->pin_get_mode(chip_gpio_num);
}

void core_pinctrl_set_mode(int chip_gpio_num, int mode)
{
    get_chip_ops()->pin_set_mode(chip_gpio_num, mode);
}

void core_pinctrl_set_pullUpDn(int chip_gpio_num, int pud)
{
    get_chip_ops()->pinctrl_set_pullUpDn(chip_gpio_num, pud);
}

int core_pinctrl_read(int chip_gpio_num)
{
    return get_chip_ops()->pinctrl_read(chip_gpio_num);
}

void core_pinctrl_write(int chip_gpio_num, int value)
{
    get_chip_ops()->pinctrl_write(chip_gpio_num, value);
}
void core_pinctrl_print_who_has_function(char *name_buf, int len)
{
    get_chip_ops()->who_has_function(name_buf, len);
}
const char *core_pinctrl_pin_get_mode_name(int chip_gpio_num)
{
    return get_chip_ops()->pinctrl_pin_get_mode_name(chip_gpio_num);
}
const char *core_pinctrl_pin_get_mode_name_by_num(int chip_gpio_num, int mode_num)
{
    return get_chip_ops()->pinctrl_pin_get_mode_name_by_num(chip_gpio_num, mode_num);
}
void pinctrl_mode_rename(int chip_gpio_num, int mode_num, char *name)
{
    get_chip_ops()->mode_rename(chip_gpio_num, mode_num, name);
}

/******************************************************************************/
/*如果是管理员权限运行，则调用上面的core系操作寄存器函数，不是则发送信息给server */
/******************************************************************************/
int pinctrl_get_mode(int chip_gpio_num)
{
    if (geteuid() == 0)
        return core_pinctrl_get_mode(chip_gpio_num);
    char buf[50];
    sprintf(buf, "pinctrl_get_mode(%d)", chip_gpio_num);
    socket_run_command(buf, buf);
    return atoi(buf);
}

void pinctrl_set_mode(int chip_gpio_num, int mode)
{
    if (geteuid() == 0)
    {
        core_pinctrl_set_mode(chip_gpio_num, mode);
    }
    else
    {
        char buf[50];
        sprintf(buf, "pinctrl_set_mode(%d,%d)", chip_gpio_num, mode);
        socket_run_command(buf, buf);
    }
}

void pinctrl_set_pullUpDn(int chip_gpio_num, int pud)
{
    if (geteuid() == 0)
        core_pinctrl_set_pullUpDn(chip_gpio_num, pud);
    else
    {
        char buf[50];
        sprintf(buf, "pinctrl_set_pullUpDn(%d,%d)", chip_gpio_num, pud);
        socket_run_command(buf, buf);
    }
}

int pinctrl_read(int chip_gpio_num)
{
    if (geteuid() == 0)
        return core_pinctrl_read(chip_gpio_num);
    char buf[50];
    sprintf(buf, "pinctrl_read(%d)", chip_gpio_num);
    socket_run_command(buf, buf);
    return atoi(buf);
}

void pinctrl_write(int chip_gpio_num, int value)
{
    if (geteuid() == 0)
        core_pinctrl_write(chip_gpio_num, value);
    else
    {
        char buf[50];
        sprintf(buf, "pinctrl_write(%d,%d)", chip_gpio_num, value);
        socket_run_command(buf, buf);
    }
}
void pinctrl_print_who_has_function(char *name_buf, int len)
{
    if (geteuid() == 0)
        core_pinctrl_print_who_has_function(name_buf, len);
    else
    {
        char buf[50];
        sprintf(buf, "pinctrl_print_who_has_function(%s,%d)", name_buf, len);
        socket_run_command(buf, buf);
    }
}
const char *pinctrl_pin_get_mode_name(int chip_gpio_num)
{
    if (geteuid() == 0)
        return core_pinctrl_pin_get_mode_name(chip_gpio_num);
    char buf[50];
    sprintf(buf, "pinctrl_pin_get_mode_name(%d)", chip_gpio_num);
    socket_run_command(buf, buf);
    char *str = (char *)malloc(strlen(buf));
    strncpy(str, buf, strlen(buf));
    return str;
}
const char *pinctrl_pin_get_mode_name_by_num(int chip_gpio_num, int mode_num)
{
    if (geteuid() == 0)
        return core_pinctrl_pin_get_mode_name_by_num(chip_gpio_num, mode_num);
    char buf[50];
    sprintf(buf, "pinctrl_pin_get_mode_name_by_num(%d,%d)", chip_gpio_num, mode_num);
    socket_run_command(buf, buf);
    char *str = (char *)malloc(strlen(buf));
    strncpy(str, buf, strlen(buf));
    return str;
}
