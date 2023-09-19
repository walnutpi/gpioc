#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "../src/softpwm.h"
#include "../chips/h616.h"



static char *chips_compatible[] = {
    "占位符",
    "sun50i-h616"};



int detect()
{
    FILE *fp;
    char buffer[1024];
    char *compatible;
    int i;
    fp = fopen("/proc/device-tree/compatible", "r");
    if (fp == NULL)
    {
        printf("Failed to open /proc/device-tree/compatible \n");
        return -1;
    }

    fgets(buffer, 100, fp);
    fclose(fp);

    // printf("compatible=\t%s\r\n",buffer);
    compatible = strtok(buffer, "\n");

    for (i = 0; i < (int)sizeof(chips_compatible)/(int)sizeof(char *); i++)
    {
        // printf("[%d]=%s\r\n", i, chips_compatible[i]);
        if (strstr(compatible, chips_compatible[i]) != NULL)
        {
            return i;
        }
    }
    return -1;
}

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
