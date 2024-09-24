#ifndef BOARD_PIN_H
#define BOARD_PIN_H

#define _BOARD_DEF_WANUTPI_1B 1
#define _BOARD_DEF_WANUTPI_1B_EMMC 2

#define PH_NUM_ERROR -1
#define PH_5V -2
#define PH_3V3 -3
#define PH_GND -4
#define PH_NC -1
#define PH_COLOR_BLACK 0
#define PH_COLOR_RED 1
#define PH_COLOR_GREEEN 2
#define PH_COLOR_BLUE 3
#define PH_COLOR_YELLOW 4

struct BOARD_PIN
{
    int pin_num;  // 在板上的引脚编号
    int gpio_num; // 芯片上的gpio编号
    char *name;   // 要显示出来的引脚名称
    int color;    // 引脚颜色
};
#define DEF_A_BOARD_PIN(_pin_num, _gpio_num, _name, _color) \
    {                                                   \
        .pin_num = _pin_num,                            \
        .gpio_num = _gpio_num,                          \
        .name = _name,                                  \
        .color = _color,                                \
    }

struct BOARD_PIN_PER
{
    int count;  // 共有几个引脚
    int *pins;  // 哪些引脚
    int *modes; // 对应引脚需要设置为什么模式
};

struct BOARD_DESC
{
    char *model;            // 设备树model字段
    int pin_num;            // 共有几个pin脚
    struct BOARD_PIN *pins; // 描述板子所带的所有引脚
    struct BOARD_PIN_PER *pwms;
    struct BOARD_PIN_PER *uarts;
    struct BOARD_PIN_PER *spis;
    struct BOARD_PIN_PER *i2cs;
};
extern struct BOARD_DESC walnutpi_1b;
extern struct BOARD_DESC walnutpi_1b_emmc;

#endif