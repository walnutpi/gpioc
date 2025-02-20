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
    {                                                       \
        .pin_num = _pin_num,                                \
        .gpio_num = _gpio_num,                              \
        .name = _name,                                      \
        .color = _color,                                    \
    }

struct PIN_with_PER
{
    int pin;  // 对应开发板上哪个引脚
    int mode; // 对应该引脚的复用功能几
};
struct BOARD_PIN_PER
{
    int count; // 共有几个引脚
    struct PIN_with_PER *the_pins;
};
#define DEF_A_BOARD_PIN_PER(_pin, _mode) \
    {                                    \
        .pin = _pin,                     \
        .mode = _mode,                   \
    }



struct PIN_mode_rename
{
    int pin;       // 对应开发板上哪个引脚
    int mode;      // 对应该引脚的复用功能几
    char *newname; // 新名字
};
struct BOARD_mode_rename
{
    int count; // 共有几个引脚
    struct PIN_mode_rename *the_pins;
};
#define DEF_A_BOARD_PIN_MODE_RENAME(_pin, _mode, _newname) \
    {                                                      \
        .pin = _pin,                                       \
        .mode = _mode,                                     \
        .newname = _newname,                               \
    }

    
struct BOARD_DESC
{
    char *model;            // 设备树model字段
    int pin_num;            // 共有几个pin脚
    struct BOARD_PIN *pins; // 描述板子所带的所有引脚
    struct BOARD_PIN_PER *pwms;
    struct BOARD_PIN_PER *uarts;
    struct BOARD_PIN_PER *spis;
    struct BOARD_PIN_PER *i2cs;
    struct BOARD_mode_rename *mode_renames;
};
extern struct BOARD_DESC walnutpi_1b;
extern struct BOARD_DESC walnutpi_1b_emmc;
extern struct BOARD_DESC walnutpi_2b;

#endif