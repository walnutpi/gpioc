#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include "../chips/h616.h"
#include "../src/gpioc.h"

int main()
{
    gpio_set_Mode(77, 1);

    while(1)
    {

        gpio_write(77, 0);
        sleep(1);
        gpio_write(77, 1);
        sleep(1);
    }
    return 0;
}