#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../libgpio/board.h"
const char *command_name = "gpio";

int do_pri_all_gpio_on_ph(int argc, char *argv[])
{
    print_all_gpio_on_ph();
}
int do_pri_pin_para(int argc, char *argv[])
{
    print_pin_para();
}
int do_pri_mode_name(int argc, char *argv[])
{
    int ph_num = atoi(argv[2]);
    printf("%s\n", pin_get_mode_name_now(ph_num));
}
int do_pin(int argc, char *argv[])
{
    if (argc != 3)
    {
        // fprintf(stderr, "Usage: \n\t%s pin [keyword]\n\n", command_name);
        exit(1);
    }
    print_pin_by_mode_name(argv[2]);
}
int do_search(int argc, char *argv[])
{
    if (argc != 3)
    {
        // fprintf(stderr, "Usage: \n\t%s search [keyword]\n\n", command_name);
        exit(1);
    }
    print_pin_by_search_all_mode_name(argv[2]);
}
int do_pins(int argc, char *argv[])
{
    print_pins();
}
int do_pri_mode_para(int argc, char *argv[])
{
    print_mode_name_inoutoff(atoi(argv[2]));
    printf(" IN_PULLUP IN_PULLDOWN");
}
int do_mode(int argc, char *argv[])
{
    if (argc != 4)
    {
        // fprintf(stderr, "Usage:\n\t %s mode [pin] [mode]\n\n", command_name);
        exit(1);
    }
    int ph_num = atoi(argv[2]);
    char *str = argv[3];
    if (strcasecmp(str, "IN_PULLUP") == 0)
    {
        pin_set_pullUpDn(ph_num, PULL_UP);
        pin_set_mode(ph_num, INPUT);
    }
    else if (strcasecmp(str, "IN_PULLDOWN") == 0)
    {
        pin_set_pullUpDn(ph_num, PULL_DOWN);
        pin_set_mode(ph_num, INPUT);
    }
    else
    {
        pin_set_pullUpDn(ph_num, PULL_OFF);
        pin_set_mode_by_name(ph_num, str);
    }
}
int do_read(int argc, char *argv[])
{
    int pin, val;
    if (argc != 3)
    {
        // fprintf(stderr, "Usage: \n\t%s read [pin]\n\n", command_name);
        exit(1);
    }
    pin = atoi(argv[2]);
    val = pin_read(pin);

    printf("%s\n", val == 0 ? "0" : "1");
}
int do_pri_write_para(int argc, char *argv[])
{
    printf("high low 1 0");
}
int do_write(int argc, char *argv[])
{
    if (argc != 4)
    {
        // fprintf(stderr, "Usage: \n\t%s write [pin] [value]\n\n", command_name);
        exit(1);
    }
    int ph_num = atoi(argv[2]);
    int val = -1;
    if ((strcasecmp(argv[3], "high") == 0) || (strcasecmp(argv[3], "on") == 0))
        val = 1;
    else if ((strcasecmp(argv[3], "low") == 0) || (strcasecmp(argv[3], "off") == 0))
        val = 0;
    else
        val = atoi(argv[3]);

    if (val == 1)
        pin_write(ph_num, 1);
    else if (val == 0)
        pin_write(ph_num, 0);
    else
    {
        fprintf(stderr, "the value error\n");
    }
}

int do_toggle(int argc, char *argv[])
{
    int pin;
    pin = atoi(argv[2]);
    if (argc != 3)
    {
        // fprintf(stderr, "Usage: \n\t%s toggle [pin]\n\n", command_name);
        exit(1);
    }
    pin_write(pin, !pin_read(pin));
}

struct ops
{
    const char *name;
    int (*function)(int, char **);
};

struct ops commands[] = {
    {"do_pri_mode_para", do_pri_mode_para},
    {"do_pri_write_para", do_pri_write_para},
    {"do_pri_pin_para", do_pri_pin_para},
    {"do_pri_all_gpio_on_ph", do_pri_all_gpio_on_ph},
    {"do_pri_mode_name", do_pri_mode_name},
    {"search", do_search},
    {"pin", do_pin},
    {"pins", do_pins},
    {"mode", do_mode},
    {"read", do_read},
    {"write", do_write},
    {"toggle", do_toggle},
};

int main(int argc, char *argv[])
{

    if (argc > 1)
    {

        for (int i = 0; i < sizeof(commands) / sizeof(struct ops); i++)
        {
            if (strcasecmp(argv[1], commands[i].name) == 0)
            {
                // 执行对应的函数
                return commands[i].function(argc, argv);
            }
        }
    }

    printf("请输入一个命令。\n");
    return 1;
}