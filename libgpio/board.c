#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pinctrl/pinctrl.h"
#include "pinctrl/softpwm.h"
#include "board.h"
#include "board-pin.h"

static struct BOARD_DESC *board_list[] = {
    &walnutpi_1b,
    &walnutpi_1b_emmc,
    &walnutpi_2b,
    &canMVk230,
    &cybercamK230,
};

static struct BOARD_DESC *now_board_desc = NULL;
struct BOARD_DESC *get_board_desc()
{
    FILE *fp;
    char buffer[1024];
    char *model;
    int i;

    if (now_board_desc != NULL)
        return now_board_desc;
    fp = fopen("/proc/device-tree/model", "r");
    if (fp == NULL)
    {
        printf("Failed to open /proc/device-tree/model \n");
        exit(-1);
    }

    fgets(buffer, 100, fp);
    fclose(fp);

    model = strtok(buffer, "\n");

    for (i = 0; i < sizeof(board_list) / sizeof(board_list[0]); i++)
    {
        if (strcmp(model, board_list[i]->model) == 0)
        {
            now_board_desc = board_list[i];
            if (now_board_desc->mode_renames != NULL)
            {
                struct BOARD_mode_rename *board_reanme_pins = now_board_desc->mode_renames;

                for (int pin = 0; pin < board_reanme_pins->count; pin++)
                {
                    struct PIN_mode_rename *rename_pin = &(board_reanme_pins->the_pins[pin]);
                    pinctrl_mode_rename(rename_pin->pin, rename_pin->mode, rename_pin->newname);
                }
            }
            return now_board_desc;
        }
    }

    printf("\n/proc/device-tree/model string [%s] is not in support list\n", model);
    exit(-1);
}

static struct BOARD_PIN *get_BOARD_PIN()
{
    struct BOARD_PIN *PIN;
    return get_board_desc()->pins;
}
int board_ph_to_gpio(int pin_num)
{
    if (pin_num > get_board_desc()->pin_num)
        return PH_NUM_ERROR;
    return get_BOARD_PIN()[pin_num].gpio_num;
}
void exit_if_no_gpio(int pin_num)
{
    int gpio_num = board_ph_to_gpio(pin_num);
    if (gpio_num < 0)
    {
        printf("ERROR: pin %d cannot do this operation \n", pin_num);
        exit(-1);
    }
}
int pin_get_mode(int pin_num)
{
    int gpio_num = board_ph_to_gpio(pin_num);
    if (gpio_num < 0)
        return -1;
    return pinctrl_get_mode(gpio_num);
}

void pin_set_mode(int pin_num, int mode)
{
    if (board_ph_to_gpio(pin_num) < 0)
        return;
    pinctrl_set_mode(board_ph_to_gpio(pin_num), mode);
}
void pin_set_mode_by_name(int pin_num, char *mode)
{
    if (board_ph_to_gpio(pin_num) < 0)
        return;
    for (int i = 0; i <= 0xf; i++)
    {
        const char *str = pin_get_mode_name_by_num(pin_num, i);
        if (str != NULL)
            if (strcasecmp(str, mode) == 0)
            {
                pin_set_mode(pin_num, i);
                return;
            }
    }
}
void pin_set_pullUpDn(int pin_num, int pud)
{
    // exit_if_no_gpio(pin_num);
    if (board_ph_to_gpio(pin_num) < 0)
        return;
    pinctrl_set_pullUpDn(board_ph_to_gpio(pin_num), pud);
}
int pin_read(int pin_num)
{
    // exit_if_no_gpio(pin_num);
    if (board_ph_to_gpio(pin_num) < 0)
        return -1;
    return pinctrl_read(board_ph_to_gpio(pin_num));
}
void pin_write(int pin_num, int value)
{
    if (board_ph_to_gpio(pin_num) < 0)
        return;
    // exit_if_no_gpio(pin_num);
    pinctrl_write(board_ph_to_gpio(pin_num), value);
}
const char *pin_get_mode_name_now(int pin_num)
{
    int gpio_num = board_ph_to_gpio(pin_num);
    if (gpio_num < 0)
    {
        return "";
    }
    return pinctrl_pin_get_mode_name(gpio_num);
}
const char *pin_get_mode_name_by_num(int pin_num, int mode_num)
{
    int gpio_num = board_ph_to_gpio(pin_num);
    if (gpio_num < 0)
    {
        return "";
    }
    return pinctrl_pin_get_mode_name_by_num(gpio_num, mode_num);
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

static void print_pin_value_and_mode_left(int ph)
{
    // 左列: | V | Mode | Name | Physical |
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
    printf(" %8s ", get_BOARD_PIN()[ph].name);
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

static void print_pin_value_and_mode_right(int ph)
{
    // 右列: | Physical | Name | Mode | V |
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
    printf(" %-8s ", get_BOARD_PIN()[ph].name);
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

static void print_header_dual_row(struct HEADER_DESC *header)
{
    if (header->label)
        printf("\n=== %s ===\n", header->label);
    printf("+---+-----------+----------+----------+----------+-----------+---+\n");
    printf("| V |    Mode   |   Name   | Physical |   Name   |    Mode   | V |\n");
    printf("+---+-----------+----------+----------+----------+-----------+---+\n");

    int end = header->start_pin + header->count - 1;
    if (end % 2 == 1)
        end--; // 确保成对
    for (int ph = header->start_pin; ph <= end; ph += 2)
    {
        print_pin_value_and_mode_left(ph);
        print_pin_value_and_mode_right(ph + 1);
        printf("\n");
    }
    printf("+---+-----------+----------+----------+----------+-----------+---+\n");
}

static void print_header_single_row(struct HEADER_DESC *header)
{
    if (header->label)
        printf("\n=== %s ===\n", header->label);
    printf("+---+-----------+----------+----------+\n");
    printf("| V |    Mode   |   Name   | Physical |\n");
    printf("+---+-----------+----------+----------+\n");

    int end = header->start_pin + header->count;
    for (int ph = header->start_pin; ph < end; ph++)
    {
        // 与双排针左半边一致的样式: V | Mode | Name | Physical |
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
        printf(" %8s ", get_BOARD_PIN()[ph].name);
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
        printf("\033[0m");
        printf("||    |");
        printf("\n");
    }
    printf("+---+-----------+----------+----------+\n");
}

void print_pins()
{
    get_board_desc();

    // 按接头打印
    for (int i = 0; i < now_board_desc->header_count; i++)
    {
        struct HEADER_DESC *h = &now_board_desc->headers[i];
        printf("\n");
        switch (h->type)
        {
        case HEADER_TYPE_DUAL_ROW:
            print_header_dual_row(h);
            break;
        case HEADER_TYPE_SINGLE_ROW:
            print_header_single_row(h);
            break;
        }
    }

    // 所有引脚都由 headers 覆盖，不在此处额外打印
}

static void print_search_none_dual_l(int ph)
{
    printf("|");
    printf(" %9s ", "");
    printf("|");
    printf(" %8s ", get_BOARD_PIN()[ph].name);
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
static void print_search_none_dual_r(int ph)
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
    printf(" %-8s ", get_BOARD_PIN()[ph].name);
    printf("|");
    printf(" %9s ", "");
    printf("|");
}
static void print_search_none_single(int ph)
{
    printf("|");
    printf(" %9s ", "");
    printf("|");
    printf(" %-8s ", get_BOARD_PIN()[ph].name);
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
    printf("|    |");
}

static void print_search_hit_dual_l(int ph, int mode_num)
{
    printf("\033[30;42m");
    printf("|");
    printf(" %9s ", pin_get_mode_name_by_num(ph, mode_num));
    printf("|");
    printf(" %8s ", get_BOARD_PIN()[ph].name);
    printf("|");
    if (get_BOARD_PIN()[ph].gpio_num == PH_NC)
        printf(" -- ");
    else
        printf(" %2d ", ph);
    printf("|");
    printf("\033[0m");
}
static void print_search_hit_dual_r(int ph, int mode_num)
{
    printf("\033[30;42m");
    printf("|");
    if (get_BOARD_PIN()[ph].gpio_num == PH_NC)
        printf(" -- ");
    else
        printf(" %-2d ", ph);
    printf("|");
    printf(" %-8s ", get_BOARD_PIN()[ph].name);
    printf("|");
    printf(" %-9s ", pin_get_mode_name_by_num(ph, mode_num));
    printf("|");
    printf("\033[0m");
}
static void print_search_hit_single(int ph, int mode_num)
{
    printf("\033[30;42m");
    printf("|");
    printf(" %-9s ", pin_get_mode_name_by_num(ph, mode_num));
    printf("|");
    printf(" %-8s ", get_BOARD_PIN()[ph].name);
    printf("|");
    if (get_BOARD_PIN()[ph].gpio_num == PH_NC)
        printf(" -- ");
    else
        printf(" %2d ", ph);
    printf("|");
    printf("\033[0m");
}

void print_pin_by_search_all_mode_name(char *str)
{
    printf("serach: %s\n", str);

    struct BOARD_DESC *desc = get_board_desc();

    for (int hi = 0; hi < desc->header_count; hi++)
    {
        struct HEADER_DESC *h = &desc->headers[hi];
        int is_dual = (h->type == HEADER_TYPE_DUAL_ROW);
        int end = h->start_pin + h->count;

        if (h->label)
            printf("\n=== %s ===\n", h->label);
        if (is_dual)
        {
            printf("+-----------+----------+----------+----------+-----------+\n");
            printf("|    Mode   |   Name   | Physical |   Name   |    Mode   |\n");
            printf("+-----------+----------+----------+----------+-----------+\n");
        }
        else
        {
            printf("+-----------+----------+----------+\n");
            printf("|    Mode   |   Name   | Physical |\n");
            printf("+-----------+----------+----------+\n");
        }

        for (int ph = h->start_pin; ph < end; ph++)
        {
            int j = 7;
            int hit = 0;
            if (board_ph_to_gpio(ph) > 0)
            {
                for (j = 0; j < 7; j++)
                {
                    const char *mode_desc = pinctrl_pin_get_mode_name_by_num(board_ph_to_gpio(ph), j);
                    if (mode_desc != NULL)
                    {
                        if (strncasecmp(str, mode_desc, strlen(str)) == 0)
                        {
                            hit = 1;
                            if (is_dual)
                            {
                                if ((ph - h->start_pin) % 2 == 0)
                                {
                                    print_search_hit_dual_l(ph, j);
                                }
                                else
                                {
                                    print_search_hit_dual_r(ph, j);
                                    printf("\n");
                                }
                            }
                            else
                            {
                                print_search_hit_single(ph, j);
                                printf("\n");
                            }
                            break;
                        }
                    }
                }
            }
            if (!hit)
            {
                if (is_dual)
                {
                    if ((ph - h->start_pin) % 2 == 0)
                        print_search_none_dual_l(ph);
                    else
                    {
                        print_search_none_dual_r(ph);
                        printf("\n");
                    }
                }
                else
                {
                    print_search_none_single(ph);
                    printf("\n");
                }
            }
        }
        if (is_dual)
            printf("+-----------+----------+----------+----------+-----------+\n");
        else
            printf("+-----------+----------+----------+\n");
    }
}

void print_pin_para()
{
    printf("pwm uart i2c spi");
}

void print_pin_by_mode_name(char *str)
{
    int pins[43] = {-1};
    get_board_desc();

    if (strcasecmp(str, "pwm") == 0)
        for (int i = 0; i < now_board_desc->pwms->count; i++)
            pins[now_board_desc->pwms->the_pins[i].pin] = now_board_desc->pwms->the_pins[i].mode;
    else if (strcasecmp(str, "uart") == 0)
        for (int i = 0; i < now_board_desc->uarts->count; i++)
            pins[now_board_desc->uarts->the_pins[i].pin] = now_board_desc->uarts->the_pins[i].mode;
    else if (strcasecmp(str, "i2c") == 0)
        for (int i = 0; i < now_board_desc->i2cs->count; i++)
            pins[now_board_desc->i2cs->the_pins[i].pin] = now_board_desc->i2cs->the_pins[i].mode;
    else if (strcasecmp(str, "spi") == 0)
        for (int i = 0; i < now_board_desc->spis->count; i++)
            pins[now_board_desc->spis->the_pins[i].pin] = now_board_desc->spis->the_pins[i].mode;

    for (int hi = 0; hi < now_board_desc->header_count; hi++)
    {
        struct HEADER_DESC *h = &now_board_desc->headers[hi];
        int is_dual = (h->type == HEADER_TYPE_DUAL_ROW);
        int end = h->start_pin + h->count;

        if (h->label)
            printf("\n=== %s ===\n", h->label);
        if (is_dual)
        {
            printf("+-----------+----------+----------+----------+-----------+\n");
            printf("|    Mode   |   Name   | Physical |   Name   |    Mode   |\n");
            printf("+-----------+----------+----------+----------+-----------+\n");
        }
        else
        {
            printf("+-----------+----------+----------+\n");
            printf("|    Mode   |   Name   | Physical |\n");
            printf("+-----------+----------+----------+\n");
        }

        for (int ph = h->start_pin; ph < end; ph++)
        {
            if (pins[ph] > 0)
            {
                if (is_dual)
                {
                    if ((ph - h->start_pin) % 2 == 0)
                        print_search_hit_dual_l(ph, pins[ph]);
                    else
                    {
                        print_search_hit_dual_r(ph, pins[ph]);
                        printf("\n");
                    }
                }
                else
                {
                    print_search_hit_single(ph, pins[ph]);
                    printf("\n");
                }
            }
            else
            {
                if (is_dual)
                {
                    if ((ph - h->start_pin) % 2 == 0)
                        print_search_none_dual_l(ph);
                    else
                    {
                        print_search_none_dual_r(ph);
                        printf("\n");
                    }
                }
                else
                {
                    print_search_none_single(ph);
                    printf("\n");
                }
            }
        }
        if (is_dual)
            printf("+-----------+----------+----------+----------+-----------+\n");
        else
            printf("+-----------+----------+----------+\n");
    }
}

void print_all_gpio_on_ph()
{
    struct BOARD_PIN *board_pins = get_BOARD_PIN();
    for (int ph = 1; ph <= now_board_desc->pin_num; ph++)
    {
        if (board_pins[ph].gpio_num >= 0)
            printf(" %d ", ph);
    }
}
