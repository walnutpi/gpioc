#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

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

int gpio_get_mode(int gpio_num)
{
    return chip_pin_get_mode[chip_detect()](gpio_num);
}

void gpio_set_mode(int gpio_num, int mode)
{
    chip_pin_set_mode[chip_detect()](gpio_num, mode);
}

void gpio_set_pullUpDn(int gpio_num, int pud)
{
    chip_gpio_set_PullUpDn[chip_detect()](gpio_num, pud);
}

int gpio_read(int gpio_num)
{
    return chip_gpio_read[chip_detect()](gpio_num);
}

void gpio_write(int gpio_num, int value)
{
    chip_gpio_write[chip_detect()](gpio_num, value);
}
void gpio_print_who_has_function(char *name_buf, int len)
{
    chip_who_has_function[chip_detect()](name_buf, len);
}
const char *gpio_pin_get_mode_name(int gpio_num)
{
    return chip_gpio_pin_get_mode_name[chip_detect()](gpio_num);
}
const char *gpio_pin_get_mode_name_by_num(int gpio_num, int mode_num)
{
    return chip_gpio_pin_get_mode_name_by_num[chip_detect()](gpio_num, mode_num);
}