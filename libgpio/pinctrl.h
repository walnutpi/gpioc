#ifndef _PINCTRL_H
#define _PINCTRL_H

#define	INPUT			 0
#define	OUTPUT			 1

#define	PULL_OFF			 0
#define	PULL_DOWN		 1
#define	PULL_UP			 2



// 使用gpio编号
extern int gpio_get_mode(int gpio_num);
extern void gpio_set_mode(int gpio_num, int mode);
extern void gpio_set_pullUpDn(int gpio_num, int pud);
extern int gpio_read(int gpio_num);
extern void gpio_write(int gpio_num, int value);
extern void gpio_print_who_has_function(char *name_buf, int len);
extern const char *gpio_pin_get_mode_name(int gpio_num);
extern const char *gpio_pin_get_mode_name_by_num(int gpio_num, int mode_num);


#endif
