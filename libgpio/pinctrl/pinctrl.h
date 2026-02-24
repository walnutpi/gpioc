#ifndef _PINCTRL_H
#define _PINCTRL_H

#define	INPUT			 0
#define	OUTPUT			 1

#define	PULL_OFF			 0
#define	PULL_DOWN		 1
#define	PULL_UP			 2



// 根据程序是否运行于管理员权限，选择 调用下面的寄存器操作函数 或是 通过socket发送命令
extern int pinctrl_get_mode(int chip_gpio_num);
extern void pinctrl_set_mode(int chip_gpio_num, int mode);
extern void pinctrl_set_pullUpDn(int chip_gpio_num, int pud);
extern int pinctrl_read(int chip_gpio_num);
extern void pinctrl_write(int chip_gpio_num, int value);
extern void pinctrl_print_who_has_function(char *name_buf, int len);
extern const char *pinctrl_pin_get_mode_name(int chip_gpio_num);
extern const char *pinctrl_pin_get_mode_name_by_num(int chip_gpio_num, int mode_num);

extern void pinctrl_mode_rename(int chip_gpio_num, int mode_num, char *name);

// 直接调用寄存器进行操作
extern int core_pinctrl_get_mode(int chip_gpio_num);
extern void core_pinctrl_set_mode(int chip_gpio_num, int mode);
extern void core_pinctrl_set_pullUpDn(int chip_gpio_num, int pud);
extern int core_pinctrl_read(int chip_gpio_num);
extern void core_pinctrl_write(int chip_gpio_num, int value);
extern void core_pinctrl_print_who_has_function(char *name_buf, int len);
extern const char *core_pinctrl_pin_get_mode_name(int chip_gpio_num);
extern const char *core_pinctrl_pin_get_mode_name_by_num(int chip_gpio_num, int mode_num);

#endif
