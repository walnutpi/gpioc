#ifndef _GPIOC_H
#define _GPIOC_H

#define	INPUT			 0
#define	OUTPUT			 1

#define	PUD_OFF			 0
#define	PUD_DOWN		 1
#define	PUD_UP			 2

#define	CHIP_H616       1

// 使用gpio编号
extern int gpio_get_Alt(int gpio_num);
extern void gpio_set_Alt(int gpio_num, int mode);
extern void gpio_set_Mode(int gpio_num, int mode);
extern void gpio_set_pullUpDn(int gpio_num, int pud);
extern int gpio_read(int gpio_num);
extern void gpio_write(int gpio_num, int value);

// WiringPi格式，对适配wiringpi的板子使用，WiringPi编码
extern int getAlt(int pin);
extern void pinModeAlt(int pin, int mode);
extern void pinMode(int pin, int mode);
extern void pullUpDnControl(int pin, int pud);
extern int digitalRead(int pin);
extern void digitalWrite(int pin, int value);

#endif
