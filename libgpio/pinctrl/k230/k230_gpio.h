#ifndef _K230_GPIO_H_
#define _K230_GPIO_H_ 

#include <stdint.h>
#define GPIO0_BASE_ADDR             (0x9140B000UL)
#define GPIO0_IO_SIZE               (0x00001000UL)

#define GPIO1_BASE_ADDR             (0x9140C000UL)
#define GPIO1_IO_SIZE               (0x00001000UL)

void kd_pin_init(void);
/* gpio output or input */
uint32_t kd_pin_get_ddr(int pin);
/* set output or input */
void kd_pin_set_ddr(int pin, int value);

/* get gpio input value */
uint32_t kd_pin_get_dr(int pin);
/* set gpio output value */
void kd_pin_set_dr(int pin, int value);


#endif
