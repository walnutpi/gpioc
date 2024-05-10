#ifndef _BOARD_H
#define _BOARD_H

#include "pinctrl.h"

// 使用板上排针编号

extern int pin_get_mode(int pin_num);
extern void pin_set_mode(int pin_num, int mode);
extern void pin_set_mode_by_name(int pin_num, char *mode);
extern void pin_set_pullUpDn(int pin_num, int pud);
extern int pin_read(int pin_num);
extern void pin_write(int pin_num, int value);
extern const char *pin_get_mode_name_now(int pin_num);
extern const char *pin_get_mode_name_by_num(int pin_num, int mode_num);

void soft_pwm_set_duty_cycle(int pin_num, int dutycycle);
void soft_pwm_set_frequency(int pin_num, int freq);
int soft_pwm_get_duty_cycle(int pin_num);
int soft_pwm_get_frequency(int pin_num);
void soft_pwm_start(int pin_num);
void soft_pwm_stop(int pin_num);
int soft_pwm_exists(int pin_num);

// 供gpio指令使用
extern void print_pins();                                 // 将当前所有引脚的状态输出到终端
extern void print_all_gpio_on_ph();                       // 输出所有可作为gpio使用的pin编号
extern void print_pin_para();                             // 输出pin功能可用的参数
extern void print_pin_by_mode_name(char *str);            // 传入指定字符串，输出所对应的引脚，这里输出的引脚都在板上带有可直接调用的设备树插件
extern void print_pin_by_search_all_mode_name(char *str); // 传入字符串，在所有引脚复用功能中查找以该字符串开头的，并直接输出到终端，可能需要自己编写设备树以启用
extern void print_mode_name_inoutoff(int pin_num);        // 输出pin功能可用的参数

#endif
