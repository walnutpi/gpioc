#ifndef _GPIO_H
#define _GPIO_H
// version: 1.0


#define	INPUT			 0
#define	OUTPUT			 1

#define	PULL_OFF			 0
#define	PULL_DOWN		 1
#define	PULL_UP			 2

int pin_get_mode(int pin_num);
void pin_set_mode(int pin_num, int mode);
void pin_set_mode_by_name(int pin_num, char *mode);
void pin_set_pullUpDn(int pin_num, int pud);
int pin_read(int pin_num);
void pin_write(int pin_num, int value);
const char *pin_get_mode_name_now(int pin_num);
const char *pin_get_mode_name_by_num(int pin_num, int mode_num);

void soft_pwm_set_duty_cycle(int pin_num, int dutycycle);
void soft_pwm_set_frequency(int pin_num, int freq);
int soft_pwm_get_duty_cycle(int pin_num);
int soft_pwm_get_frequency(int pin_num);
void soft_pwm_start(int pin_num);
void soft_pwm_stop(int pin_num);
int soft_pwm_exists(int pin_num);

#endif
