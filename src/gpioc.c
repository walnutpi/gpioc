#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../src/common.h"
#include "../src/softpwm.h"
#include "../chips/h616.h"

void (*chip_pin_set_mode[])(int, int) = {
    0,
    H616_pin_set_mode,
};

void (*chip_pin_set_alt[])(int, int) = {
    0,
    H616_pin_set_alt,
};

int (*chip_pin_get_alt[])(int) = {
    0,
    H616_pin_get_alt,
};

int (*chip_gpio_read[])(int) = {
    0,
    H616_gpio_read,
};

void (*chip_gpio_write[])(int, int) = {
    0,
    H616_gpio_write,
};

void (*chip_gpio_set_PullUpDn[])(int, int) = {
    0,
    H616_gpio_set_PullUpDn,
};



int chip_detect()
{
    int chip = detect();
    // printf("chip=%d\r\n",chip);
    int num = sizeof(chip_gpio_read) / sizeof(chip_gpio_read[0]);

    if (chip < 1)
        exit(-1);
    else if (chip > num)
        exit(-1);
    else
        return chip;
}

int gpio_get_Alt(int gpio_num)
{
    return chip_pin_get_alt[chip_detect()](gpio_num);
}

void gpio_set_Alt(int gpio_num, int mode)
{
    chip_pin_set_alt[chip_detect()](gpio_num, mode);
}

void gpio_set_Mode(int gpio_num, int mode)
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
