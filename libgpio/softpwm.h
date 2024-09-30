#ifndef _SOFTPWM_H
#define _SOFTPWM_H

// 直接调用寄存器进行操作
void core_pwm_set_duty_cycle(unsigned int gpio, int dutycycle);
void core_pwm_set_frequency(unsigned int gpio, int freq);
int core_pwm_get_duty_cycle(unsigned int gpio);
int core_pwm_get_frequency(unsigned int gpio);
void core_pwm_start(unsigned int gpio);
void core_pwm_stop(unsigned int gpio);
int core_pwm_exists(unsigned int gpio);


void pwm_set_duty_cycle(unsigned int gpio, int dutycycle);
void pwm_set_frequency(unsigned int gpio, int freq);
int pwm_get_duty_cycle(unsigned int gpio);
int pwm_get_frequency(unsigned int gpio);
void pwm_start(unsigned int gpio);
void pwm_stop(unsigned int gpio);
int pwm_exists(unsigned int gpio);

#endif