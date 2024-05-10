#ifndef _GPIO_H
#define _GPIO_H

int pin_get_mode(int ph_num);
void pin_set_mode(int ph_num, int mode);
void pin_set_mode_by_name(int ph_num, char *mode);
void pin_set_pullUpDn(int ph_num, int pud);
int pin_read(int ph_num);
void pin_write(int ph_num, int value);
const char *pin_get_mode_name_now(int ph_num);
const char *pin_get_mode_name_by_num(int ph_num, int mode_num);

#endif
