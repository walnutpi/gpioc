#include "pinctrl-k230.h"
#include "drv_fpioa.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <dirent.h>

bool k230_init()
{
    return true;
}
void k230_pin_set_mode(int gpio_num, int mode)
{
}
int k230_pin_get_mode(int gpio_num)
{
    fpioa_func_t func;
    drv_fpioa_get_pin_func(gpio_num, &func);
    usleep(1000);
    return func;
}
int k230_gpio_read(int gpio_num)
{
    return 0;
}
void k230_gpio_write(int gpio_num, int value) {}
void k230_gpio_set_PullUpDn(int gpio_num, int pud) {}
void k230_who_has_function(char *name_buf, int len) {}
const char *k230_gpio_pin_get_mode_name(int gpio_num)
{
    return "off";
}
const char *k230_gpio_pin_get_mode_name_by_num(int gpio_num, int mode_num)
{
    return "off";
}
void k230_mode_rename(int gpio_num, int mode_num, char *name) {}