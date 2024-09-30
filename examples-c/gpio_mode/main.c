#include <stdio.h>
#include <unistd.h>

#include "gpio.h"
#define IO 41

int main()
{
    printf("引脚 %d 的mode 0 : %s\n", IO, pin_get_mode_name_by_num(IO, 0));
    printf("引脚 %d 的mode 1 : %s\n", IO, pin_get_mode_name_by_num(IO, 1));

    printf("引脚 %d 工作于 %d %s\n", IO, pin_get_mode(IO), pin_get_mode_name_now(IO));
    pin_set_mode(IO, OUTPUT); // 设置为输出模式
    printf("引脚 %d 工作于 %d %s\n", IO, pin_get_mode(IO), pin_get_mode_name_now(IO));
    pin_set_mode_by_name(IO, "IN"); // 设置为输入模式
    printf("引脚 %d 工作于 %d %s\n", IO, pin_get_mode(IO), pin_get_mode_name_now(IO));

    return 0;
}