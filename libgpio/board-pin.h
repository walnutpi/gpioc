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
#define A_BOARD_PIN(_pin_num, _gpio_num, _name, _color) \
    {                                                   \
        .pin_num = _pin_num,                            \
        .gpio_num = _gpio_num,                          \
        .name = _name,                                  \
        .color = _color,                                \
    }

extern struct BOARD_PIN walnutpi1b_pins[];
extern struct BOARD_PIN walnutpi1b_emmc_pins[];


// extern int walnutpi1b_pin_pwm[][2];
// extern int walnutpi1b_pin_uart[][2];
// extern int walnutpi1b_pin_spi[][2];
// extern int walnutpi1b_pin_i2c[][2];
#endif