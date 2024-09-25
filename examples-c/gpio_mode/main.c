#include <stdio.h>
#include <unistd.h>

#include "gpio.h"
#define KEY 41
#define LED 42

void print_mode(int pin)
{
    printf("引脚 %d 工作于 [%d]: %s\n", pin, pin_get_mode(KEY), pin_get_mode_name_now(KEY));
}

int main()
{
    print_mode(KEY);
    pin_set_mode(KEY, OUTPUT); //设置为输出模式
    print_mode(KEY);
    pin_set_mode_by_name(KEY, "IN"); //设置为输入模式
    print_mode(KEY);

    return 0;
}