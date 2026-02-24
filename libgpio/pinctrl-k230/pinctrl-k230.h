#ifndef _PINCTRL_K230_H
#define _PINCTRL_K230_H
#include <stdbool.h>

bool k230_init();
void k230_pin_set_mode(int gpio_num, int mode);
int k230_pin_get_mode(int gpio_num);
int k230_gpio_read(int gpio_num);
void k230_gpio_write(int gpio_num, int value);
void k230_gpio_set_PullUpDn(int gpio_num, int pud);
void k230_who_has_function(char *name_buf, int len);
const char *k230_gpio_pin_get_mode_name(int gpio_num);
const char *k230_gpio_pin_get_mode_name_by_num(int gpio_num, int mode_num);
void k230_mode_rename(int gpio_num, int mode_num, char *name);

#endif
