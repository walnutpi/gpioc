#ifndef _PINCTRL_H
#define _PINCTRL_H

#define	INPUT			 0
#define	OUTPUT			 1

#define	PULL_OFF			 0
#define	PULL_DOWN		 1
#define	PULL_UP			 2



// 根据程序是否运行于管理员权限，选择 调用下面的寄存器操作函数 或是 通过socket发送命令
extern int gpio_get_mode(int gpio_num);
extern void gpio_set_mode(int gpio_num, int mode);
extern void gpio_set_pullUpDn(int gpio_num, int pud);
extern int gpio_read(int gpio_num);
extern void gpio_write(int gpio_num, int value);
extern void gpio_print_who_has_function(char *name_buf, int len);
extern const char *gpio_pin_get_mode_name(int gpio_num);
extern const char *gpio_pin_get_mode_name_by_num(int gpio_num, int mode_num);

// 直接调用寄存器进行操作
extern int core_gpio_get_mode(int gpio_num);
extern void core_gpio_set_mode(int gpio_num, int mode);
extern void core_gpio_set_pullUpDn(int gpio_num, int pud);
extern int core_gpio_read(int gpio_num);
extern void core_gpio_write(int gpio_num, int value);
extern void core_gpio_print_who_has_function(char *name_buf, int len);
extern const char *core_gpio_pin_get_mode_name(int gpio_num);
extern const char *core_gpio_pin_get_mode_name_by_num(int gpio_num, int mode_num);

#endif
