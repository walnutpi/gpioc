#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pinctrl.h"
#include "softpwm.h"
#include "board.h"

static int _board_select = 0;
#define _BOARD_DEF_WANUTPI_1B 1
#define _BOARD_DEF_WANUTPI_1B_EMMC 2

#define PH_NUM_ERROR -1
#define PH_5V -2
#define PH_3V3 -3
#define PH_GND -4
#define PH_NC -1
#define PH_COLOR_BLACK 0
#define PH_COLOR_RED 1
#define PH_COLOR_GREEEN 2
#define PH_COLOR_BLUE 3
#define PH_COLOR_YELLOW 4

struct BOARD_PIN
{
    int pin_num;  // 在板上的引脚编号
    int gpio_num; // 芯片上的gpio编号
    char *name;   // 要显示出来的引脚名称
    int color;    // 引脚颜色
};
#define A_BOARD_PIN(_pin_num, _gpio_num, _name, _color) \
    {                                                   \
        .pin_num = _pin_num,                            \
        .gpio_num = _gpio_num,                          \
        .name = _name,                                  \
        .color = _color,                                \
    }

static struct BOARD_PIN walnutpi1b_pins[] = {
    A_BOARD_PIN(0, 0, "", 0),
    A_BOARD_PIN(1, PH_3V3, "3.3v", PH_COLOR_YELLOW),
    A_BOARD_PIN(2, PH_5V, "5v", PH_COLOR_RED),
    A_BOARD_PIN(3, 264, "PI8", PH_COLOR_GREEEN),
    A_BOARD_PIN(4, PH_5V, "5v", PH_COLOR_RED),
    A_BOARD_PIN(5, 263, "PI7", PH_COLOR_GREEEN),
    A_BOARD_PIN(6, PH_GND, "GND", PH_COLOR_BLACK),
    A_BOARD_PIN(7, 72, "PC8", PH_COLOR_GREEEN),
    A_BOARD_PIN(8, 261, "PI5", PH_COLOR_GREEEN),
    A_BOARD_PIN(9, PH_GND, "GND", PH_COLOR_BLACK),
    A_BOARD_PIN(10, 262, "PI6", PH_COLOR_GREEEN),
    A_BOARD_PIN(11, 73, "PC9", PH_COLOR_GREEEN),
    A_BOARD_PIN(12, 74, "PC10", PH_COLOR_GREEEN),
    A_BOARD_PIN(13, 75, "PC11", PH_COLOR_GREEEN),
    A_BOARD_PIN(14, PH_GND, "GND", PH_COLOR_BLACK),
    A_BOARD_PIN(15, 267, "PI11", PH_COLOR_GREEEN),
    A_BOARD_PIN(16, 268, "PI12", PH_COLOR_GREEEN),
    A_BOARD_PIN(17, PH_3V3, "3.3v", PH_COLOR_YELLOW),
    A_BOARD_PIN(18, 78, "PC14", PH_COLOR_GREEEN),
    A_BOARD_PIN(19, 231, "PH7", PH_COLOR_GREEEN),
    A_BOARD_PIN(20, PH_GND, "GND", PH_COLOR_BLACK),
    A_BOARD_PIN(21, 232, "PH8", PH_COLOR_GREEEN),
    A_BOARD_PIN(22, 79, "PC15", PH_COLOR_GREEEN),
    A_BOARD_PIN(23, 230, "PH6", PH_COLOR_GREEEN),
    A_BOARD_PIN(24, 229, "PH5", PH_COLOR_GREEEN),
    A_BOARD_PIN(25, PH_GND, "GND", PH_COLOR_BLACK),
    A_BOARD_PIN(26, 233, "PH9", PH_COLOR_GREEEN),
    A_BOARD_PIN(27, 266, "PI10", PH_COLOR_BLUE),
    A_BOARD_PIN(28, 265, "PI9", PH_COLOR_BLUE),
    A_BOARD_PIN(29, 256, "PI0", PH_COLOR_GREEEN),
    A_BOARD_PIN(30, PH_GND, "GND", PH_COLOR_BLACK),
    A_BOARD_PIN(31, 257, "PI1", PH_COLOR_GREEEN),
    A_BOARD_PIN(32, 272, "PI16", PH_COLOR_GREEEN),
    A_BOARD_PIN(33, 258, "PI2", PH_COLOR_GREEEN),
    A_BOARD_PIN(34, PH_GND, "GND", PH_COLOR_BLACK),
    A_BOARD_PIN(35, 259, "PI3", PH_COLOR_GREEEN),
    A_BOARD_PIN(36, 271, "PI15", PH_COLOR_GREEEN),
    A_BOARD_PIN(37, 260, "PI4", PH_COLOR_GREEEN),
    A_BOARD_PIN(38, 269, "PI13", PH_COLOR_GREEEN),
    A_BOARD_PIN(39, PH_GND, "GND", PH_COLOR_BLACK),
    A_BOARD_PIN(40, 270, "PI14", PH_COLOR_GREEEN),
    A_BOARD_PIN(41, 76, "KEY", PH_COLOR_BLACK),
    A_BOARD_PIN(42, 77, "LED", PH_COLOR_BLACK),
};
static int walnutpi1b_pin_pwm[][2] = {{15, 5}, {16, 5}, {38, 5}, {40, 5}};
static int walnutpi1b_pin_uart[][2] = {{8, 3}, {10, 3}, {38, 3}, {40, 3}};
static int walnutpi1b_pin_spi[][2] = {{19, 4}, {21, 4}, {23, 4}, {24, 4}, {26, 4}};
static int walnutpi1b_pin_i2c[][2] = {{3, 5}, {5, 5}, {27, 5}, {28, 5}};

static struct BOARD_PIN walnutpi1b_emmc_pins[] = {
    A_BOARD_PIN(0, 0, "", 0),
    A_BOARD_PIN(1, PH_3V3, "3.3v", PH_COLOR_YELLOW),
    A_BOARD_PIN(2, PH_5V, "5v", PH_COLOR_RED),
    A_BOARD_PIN(3, 264, "PI8", PH_COLOR_GREEEN),
    A_BOARD_PIN(4, PH_5V, "5v", PH_COLOR_RED),
    A_BOARD_PIN(5, 263, "PI7", PH_COLOR_GREEEN),
    A_BOARD_PIN(6, PH_GND, "GND", PH_COLOR_BLACK),
    A_BOARD_PIN(7, PH_NC, "----", PH_COLOR_GREEEN),
    A_BOARD_PIN(8, 261, "PI5", PH_COLOR_GREEEN),
    A_BOARD_PIN(9, PH_GND, "GND", PH_COLOR_BLACK),
    A_BOARD_PIN(10, 262, "PI6", PH_COLOR_GREEEN),
    A_BOARD_PIN(11, PH_NC, "----", PH_COLOR_GREEEN),
    A_BOARD_PIN(12, PH_NC, "----", PH_COLOR_GREEEN),
    A_BOARD_PIN(13, PH_NC, "----", PH_COLOR_GREEEN),
    A_BOARD_PIN(14, PH_GND, "GND", PH_COLOR_BLACK),
    A_BOARD_PIN(15, 267, "PI11", PH_COLOR_GREEEN),
    A_BOARD_PIN(16, 268, "PI12", PH_COLOR_GREEEN),
    A_BOARD_PIN(17, PH_3V3, "3.3v", PH_COLOR_YELLOW),
    A_BOARD_PIN(18, PH_NC, "----", PH_COLOR_GREEEN),
    A_BOARD_PIN(19, 231, "PH7", PH_COLOR_GREEEN),
    A_BOARD_PIN(20, PH_GND, "GND", PH_COLOR_BLACK),
    A_BOARD_PIN(21, 232, "PH8", PH_COLOR_GREEEN),
    A_BOARD_PIN(22, PH_NC, "----", PH_COLOR_GREEEN),
    A_BOARD_PIN(23, 230, "PH6", PH_COLOR_GREEEN),
    A_BOARD_PIN(24, 229, "PH5", PH_COLOR_GREEEN),
    A_BOARD_PIN(25, PH_GND, "GND", PH_COLOR_BLACK),
    A_BOARD_PIN(26, 233, "PH9", PH_COLOR_GREEEN),
    A_BOARD_PIN(27, 266, "PI10", PH_COLOR_BLUE),
    A_BOARD_PIN(28, 265, "PI9", PH_COLOR_BLUE),
    A_BOARD_PIN(29, 256, "PI0", PH_COLOR_GREEEN),
    A_BOARD_PIN(30, PH_GND, "GND", PH_COLOR_BLACK),
    A_BOARD_PIN(31, 257, "PI1", PH_COLOR_GREEEN),
    A_BOARD_PIN(32, 272, "PI16", PH_COLOR_GREEEN),
    A_BOARD_PIN(33, 258, "PI2", PH_COLOR_GREEEN),
    A_BOARD_PIN(34, PH_GND, "GND", PH_COLOR_BLACK),
    A_BOARD_PIN(35, 259, "PI3", PH_COLOR_GREEEN),
    A_BOARD_PIN(36, 271, "PI15", PH_COLOR_GREEEN),
    A_BOARD_PIN(37, 260, "PI4", PH_COLOR_GREEEN),
    A_BOARD_PIN(38, 269, "PI13", PH_COLOR_GREEEN),
    A_BOARD_PIN(39, PH_GND, "GND", PH_COLOR_BLACK),
    A_BOARD_PIN(40, 270, "PI14", PH_COLOR_GREEEN),
    A_BOARD_PIN(41, 76, "KEY", PH_COLOR_BLACK),
    A_BOARD_PIN(42, 71, "LED", PH_COLOR_BLACK),
};

static int select_board()
{
    FILE *fp;
    char buffer[1024];
    char *model;
    int i;

    fp = fopen("/proc/device-tree/model", "r");
    if (fp == NULL)
    {
        printf("Failed to open /proc/device-tree/model \n");
        exit(-1);
    }

    fgets(buffer, 100, fp);
    fclose(fp);

    model = strtok(buffer, "\n");

    if (strcmp(model, "walnutpi-1b") == 0)
        _board_select = _BOARD_DEF_WANUTPI_1B;
    else if (strcmp(model, "walnutpi-1b-emmc") == 0)
        _board_select = _BOARD_DEF_WANUTPI_1B_EMMC;
    else
    {
        printf("you /proc/device-tree/model string is not in support list");
        exit(-1);
    }
    return _board_select;
}
static struct BOARD_PIN *get_BOARD_PIN()
{
    struct BOARD_PIN *PIN;
    switch (select_board())
    {
    case _BOARD_DEF_WANUTPI_1B:
        return walnutpi1b_pins;
    case _BOARD_DEF_WANUTPI_1B_EMMC:
        return walnutpi1b_emmc_pins;
    }
    return NULL;
}
int board_ph_to_gpio(int pin_num)
{
    switch (select_board())
    {
    case _BOARD_DEF_WANUTPI_1B:
    case _BOARD_DEF_WANUTPI_1B_EMMC:
        if (pin_num > 42)
        {
            return PH_NUM_ERROR;
        }
        return get_BOARD_PIN()[pin_num].gpio_num;
    default:
        printf("ERROR: no support for your board\n");
    }
    return -99;
}
void exit_if_no_gpio(int pin_num)
{
    int gpio_num = board_ph_to_gpio(pin_num);
    if (gpio_num < 0)
    {
        printf("ERROR: pin %d cannot do this operation \n");
        exit(-1);
    }
}
int pin_get_mode(int pin_num)
{
    int gpio_num = board_ph_to_gpio(pin_num);
    if (gpio_num < 0)
    {
        return -1;
    }
    return gpio_get_mode(gpio_num);
}

void pin_set_mode(int pin_num, int mode)
{
    if (board_ph_to_gpio(pin_num) < 0)
        return;
    gpio_set_mode(board_ph_to_gpio(pin_num), mode);
}
void pin_set_mode_by_name(int pin_num, char *mode)
{
    if (board_ph_to_gpio(pin_num) < 0)
        return;
    for (int i = 0; i <= 7; i++)
    {
        const char *str = pin_get_mode_name_by_num(pin_num, i);
        if (str != NULL)
            if (strcasecmp(str, mode) == 0)
            {
                pin_set_mode(pin_num, i);
            }
    }
}
void pin_set_pullUpDn(int pin_num, int pud)
{
    // exit_if_no_gpio(pin_num);
    if (board_ph_to_gpio(pin_num) < 0)
        return;
    gpio_set_pullUpDn(board_ph_to_gpio(pin_num), pud);
}
int pin_read(int pin_num)
{
    // exit_if_no_gpio(pin_num);
    if (board_ph_to_gpio(pin_num) < 0)
        return -1;
    return gpio_read(board_ph_to_gpio(pin_num));
}
void pin_write(int pin_num, int value)
{
    if (board_ph_to_gpio(pin_num) < 0)
        return;
    // exit_if_no_gpio(pin_num);
    gpio_write(board_ph_to_gpio(pin_num), value);
}
const char *pin_get_mode_name_now(int pin_num)
{
    int gpio_num = board_ph_to_gpio(pin_num);
    if (gpio_num < 0)
    {
        return "";
    }
    return gpio_pin_get_mode_name(gpio_num);
}
const char *pin_get_mode_name_by_num(int pin_num, int mode_num)
{
    int gpio_num = board_ph_to_gpio(pin_num);
    if (gpio_num < 0)
    {
        return "";
    }
    return gpio_pin_get_mode_name_by_num(gpio_num, mode_num);
}

void soft_pwm_set_duty_cycle(int pin_num, int dutycycle)
{
    if (board_ph_to_gpio(pin_num) < 0)
        return;
    pwm_set_duty_cycle(board_ph_to_gpio(pin_num), dutycycle);
}
void soft_pwm_set_frequency(int pin_num, int freq)
{
    if (board_ph_to_gpio(pin_num) < 0)
        return;
    pwm_set_frequency(board_ph_to_gpio(pin_num), freq);
}
int soft_pwm_get_duty_cycle(int pin_num)
{
    if (board_ph_to_gpio(pin_num) < 0)
        return -1;
    return pwm_get_duty_cycle(board_ph_to_gpio(pin_num));
}
int soft_pwm_get_frequency(int pin_num)
{
    if (board_ph_to_gpio(pin_num) < 0)
        return -1;
    return pwm_get_frequency(board_ph_to_gpio(pin_num));
}
void soft_pwm_start(int pin_num)
{
    if (board_ph_to_gpio(pin_num) < 0)
        return;
    pwm_start(board_ph_to_gpio(pin_num));
}
void soft_pwm_stop(int pin_num)
{
    if (board_ph_to_gpio(pin_num) < 0)
        return;
    pwm_stop(board_ph_to_gpio(pin_num));
}
int soft_pwm_exists(int pin_num)
{
    if (board_ph_to_gpio(pin_num) < 0)
        return -1;
    return pwm_exists(board_ph_to_gpio(pin_num));
}

void printf_pins_l(int ph)
{
    printf("|");
    if (board_ph_to_gpio(ph) >= 0 && pin_get_mode(ph) < 2)
        printf(" %d ", pin_read(ph));
    else
        printf("   ");

    printf("|");
    if (board_ph_to_gpio(ph) >= 0)
        printf(" %9s ", pin_get_mode_name_now(ph));
    else
        printf(" %9s ", "");

    printf("|");
    printf(" %4s ", get_BOARD_PIN()[ph].name);

    switch (get_BOARD_PIN()[ph].color)
    {
    case PH_COLOR_RED:
        printf("\033[37;41m");
        break;
    case PH_COLOR_BLUE:
        printf("\033[37;44m");
        break;
    case PH_COLOR_YELLOW:
        printf("\033[30;43m");
        break;
    case PH_COLOR_GREEEN:
        printf("\033[30;42m");
        break;
    default:
        printf("\033[37;40m");
    }
    printf("|");
    if (get_BOARD_PIN()[ph].gpio_num == PH_NC)
        printf(" -- ");
    else
        printf(" %2d ", ph);
    printf("|");
    printf("\033[0m");
}
void printf_pins_r(int ph)
{
    switch (get_BOARD_PIN()[ph].color)
    {
    case PH_COLOR_RED:
        printf("\033[37;41m");
        break;
    case PH_COLOR_BLUE:
        printf("\033[37;44m");
        break;
    case PH_COLOR_YELLOW:
        printf("\033[30;43m");
        break;
    case PH_COLOR_GREEEN:
        printf("\033[30;42m");
        break;
    default:
        printf("\033[37;40m");
    }
    printf("|");
    if (get_BOARD_PIN()[ph].gpio_num == PH_NC)
        printf(" -- ");
    else
        printf(" %-2d ", ph);
    printf("|");
    printf("\033[0m");
    printf(" %4s ", get_BOARD_PIN()[ph].name);

    printf("|");
    if (board_ph_to_gpio(ph) >= 0)
        printf(" %-9s ", pin_get_mode_name_now(ph));
    else
        printf(" %9s ", "");

    printf("|");
    if (board_ph_to_gpio(ph) >= 0 && pin_get_mode(ph) < 2)
        printf(" %d ", pin_read(ph));
    else
        printf("   ");
    printf("|");
}

void print_pins()
{
    switch (select_board())
    {
    case _BOARD_DEF_WANUTPI_1B:
    case _BOARD_DEF_WANUTPI_1B_EMMC:
        printf("+---+-----------+------+----------+------+-----------+---+\n");
        printf("| V |    Mode   | Name | Physical | Name |    Mode   | V |\n");
        printf("+---+-----------+------+----------+------+-----------+---+\n");
        for (int ph = 1; ph < 40; ph++)
        {
            printf_pins_l(ph);
            ph++;
            printf_pins_r(ph);
            printf("\n");
        }
        printf("+---+-----------+------+----------+------+-----------+---+\n");
        printf("\n");
        printf("+---+-----------+------+----------+------+-----------+---+\n");
        printf("| V |    Mode   | Name | Physical | Name |    Mode   | V |\n");
        printf("+---+-----------+------+----------+------+-----------+---+\n");
        printf_pins_l(41);
        printf_pins_r(42);
        printf("\n");
        printf("+---+-----------+------+----------+------+-----------+---+\n");

        break;

    default:
        break;
    }

    printf("");
}

void print_search_none_l(int ph)
{

    printf("|");
    printf(" %9s ", "");
    printf("|");
    printf(" %4s ", get_BOARD_PIN()[ph].name);

    switch (get_BOARD_PIN()[ph].color)
    {
    case PH_COLOR_RED:
        printf("\033[37;41m");
        break;
    case PH_COLOR_BLUE:
        printf("\033[37;44m");
        break;
    case PH_COLOR_YELLOW:
        printf("\033[30;43m");
        break;
    case PH_COLOR_GREEEN:
        printf("\033[30;42m");
        break;
    default:
        printf("\033[37;40m");
    }
    printf("|");
    if (get_BOARD_PIN()[ph].gpio_num == PH_NC)
        printf(" -- ");
    else
        printf(" %2d ", ph);
    printf("|");
    printf("\033[0m");
}
void print_search_none_r(int ph)
{
    switch (get_BOARD_PIN()[ph].color)
    {
    case PH_COLOR_RED:
        printf("\033[37;41m");
        break;
    case PH_COLOR_BLUE:
        printf("\033[37;44m");
        break;
    case PH_COLOR_YELLOW:
        printf("\033[30;43m");
        break;
    case PH_COLOR_GREEEN:
        printf("\033[30;42m");
        break;
    default:
        printf("\033[37;40m");
    }
    printf("|");
    if (get_BOARD_PIN()[ph].gpio_num == PH_NC)
        printf(" -- ");
    else
        printf(" %-2d ", ph);
    printf("|");
    printf("\033[0m");
    printf(" %-4s ", get_BOARD_PIN()[ph].name);

    printf("|");
    printf(" %9s ", "");

    printf("|");
}

void print_search_hit_l(int ph, int mode_num)
{
    printf("\033[30;42m");
    printf("|");
    printf(" %9s ", pin_get_mode_name_by_num(ph, mode_num));
    printf("|");
    printf(" %4s ", get_BOARD_PIN()[ph].name);
    printf("|");
    if (get_BOARD_PIN()[ph].gpio_num == PH_NC)
        printf(" -- ");
    else
        printf(" %2d ", ph);
    printf("|");
    printf("\033[0m");
}
void print_search_hit_r(int ph, int mode_num)
{
    printf("\033[30;42m");
    printf("|");
    if (get_BOARD_PIN()[ph].gpio_num == PH_NC)
        printf(" -- ");
    else
        printf(" %-2d ", ph);
    printf("|");
    printf(" %-4s ", get_BOARD_PIN()[ph].name);
    printf("|");
    printf(" %-9s ", pin_get_mode_name_by_num(ph, mode_num));
    printf("|");
    printf("\033[0m");
}
void print_pin_by_search_all_mode_name(char *str)
{
    printf("serach: %s\n", str);
    printf("+-----------+------+----------+------+-----------+\n");
    printf("|    Mode   | Name | Physical | Name |    Mode   |\n");
    printf("+-----------+------+----------+------+-----------+\n");

    int max_pin = 0;
    switch (select_board())
    {
    case _BOARD_DEF_WANUTPI_1B:
    case _BOARD_DEF_WANUTPI_1B_EMMC:
        max_pin = 43;
        break;
    default:
        printf("ERROR: no support for your board\n");
    }
    for (int ph = 1; ph < max_pin; ph++)
    {
        int j = 7;
        if (board_ph_to_gpio(ph) > 0) // 不是电源引脚
        {
            for (j = 0; j < 7; j++) // 遍历引脚的复用功能0到7
            {
                const char *mode_desc = gpio_pin_get_mode_name_by_num(board_ph_to_gpio(ph), j);
                if (mode_desc != NULL)
                {
                    if (strncasecmp(str, mode_desc, strlen(str)) == 0)
                    {
                        if (ph % 2 == 1)
                            print_search_hit_l(ph, j);
                        else
                        {
                            print_search_hit_r(ph, j);
                            printf("\n");
                        }
                        break;
                    }
                }
            }
        }
        if (j >= 7)
        {
            // 输出代表空的行
            if (ph % 2 == 1)
                print_search_none_l(ph);
            else
            {
                print_search_none_r(ph);
                printf("\n");
            }
        }
    }
    printf("+-----------+------+----------+------+-----------+\n");
}
void print_pin_para()
{
    printf("pwm uart i2c spi");
}
void print_pin_by_mode_name(char *str)
{
    switch (select_board())
    {
    case _BOARD_DEF_WANUTPI_1B:
    case _BOARD_DEF_WANUTPI_1B_EMMC:
        int pins[43] = {-1};
        if (strcasecmp(str, "pwm") == 0)
            for (int i = 0; i < sizeof(walnutpi1b_pin_pwm) / (sizeof(int) * 2); i++)
                pins[walnutpi1b_pin_pwm[i][0]] = walnutpi1b_pin_pwm[i][1];
        else if (strcasecmp(str, "uart") == 0)
            for (int i = 0; i < sizeof(walnutpi1b_pin_uart) / (sizeof(int) * 2); i++)
                pins[walnutpi1b_pin_uart[i][0]] = walnutpi1b_pin_uart[i][1];
        else if (strcasecmp(str, "i2c") == 0)
            for (int i = 0; i < sizeof(walnutpi1b_pin_i2c) / (sizeof(int) * 2); i++)
                pins[walnutpi1b_pin_i2c[i][0]] = walnutpi1b_pin_i2c[i][1];
        else if (strcasecmp(str, "spi") == 0)
            for (int i = 0; i < sizeof(walnutpi1b_pin_spi) / (sizeof(int) * 2); i++)
                pins[walnutpi1b_pin_spi[i][0]] = walnutpi1b_pin_spi[i][1];
        printf("+-----------+------+----------+------+-----------+\n");
        printf("|    Mode   | Name | Physical | Name |    Mode   |\n");
        printf("+-----------+------+----------+------+-----------+\n");
        for (int ph = 1; ph <= 42; ph++)
        {
            if (pins[ph] > 0)
            {
                if (ph % 2 == 1)
                    print_search_hit_l(ph, pins[ph]);
                else
                {
                    print_search_hit_r(ph, pins[ph]);
                    printf("\n");
                }
            }
            else
            {

                if (ph % 2 == 1)
                    print_search_none_l(ph);
                else
                {
                    print_search_none_r(ph);
                    printf("\n");
                }
            }
            if (ph == 40)
                printf("+-----------+------+----------+------+-----------+\n");
        }
        printf("+-----------+------+----------+------+-----------+\n");
        break;
    }
}
void print_all_gpio_on_ph()
{
    switch (select_board())
    {
    case _BOARD_DEF_WANUTPI_1B:
    case _BOARD_DEF_WANUTPI_1B_EMMC:

        for (int ph = 1; ph <= 42; ph++)
        {
            if (get_BOARD_PIN()[ph].gpio_num >= 0)
                printf(" %d ", ph);
        }
        break;

    default:
        break;
    }
}
void print_mode_name_inoutoff(int pin_num)
{
    switch (select_board())
    {
    case _BOARD_DEF_WANUTPI_1B:
    case _BOARD_DEF_WANUTPI_1B_EMMC:
        printf("%s ", pin_get_mode_name_by_num(pin_num, 0));
        printf("%s ", pin_get_mode_name_by_num(pin_num, 1));
        printf("%s ", pin_get_mode_name_by_num(pin_num, 7));
    }
}
