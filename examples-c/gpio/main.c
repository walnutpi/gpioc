#include <stdio.h>
#include <unistd.h>

#include "gpio.h"
#define KEY 41
#define LED 42
int main()
{
    pin_set_mode(LED, OUTPUT);
    pin_set_mode(KEY, INPUT);
    pin_set_pullUpDn(KEY, PULL_UP);
    while (1)
    {
        if (pin_read(KEY) == 0)
            pin_write(LED, 1);
        else
            pin_write(LED, 0);

        sleep(1);
    }
    return 0;
}