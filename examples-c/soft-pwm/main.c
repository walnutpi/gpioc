#include <stdio.h>
#include <unistd.h>

#include "gpio.h"
#define LED 42
int main()
{
    soft_pwm_set_duty_cycle(LED, 0);
    soft_pwm_set_frequency(LED, 2000);
    soft_pwm_start(LED);
    while (1)
    {
        for (int i = 0; i < 100; i += 20)
        {
            soft_pwm_set_duty_cycle(LED, i);
            sleep(1);

        }
    }
    return 0;
}