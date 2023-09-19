
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>

#include "softpwm.h"
#include "gpioc.h"
#include "../chips/h616.h"

#define NS_1S 1000000000
#define DUTY_CYCLE_FULL 65535

// 不同芯片的寄存器不同，write函数也不一样
void (*gpio_out)(int, int) = H616_gpio_write;
void switch_chip(int flag)
{
    switch (flag)
    {
    case CHIP_H616:
        gpio_out = H616_gpio_write;

        break;

    default:
        break;
    }
}
struct pwm
{
    unsigned int gpio;
    int freq;
    int dutycycle;

    unsigned int cycle_high;
    unsigned int cycle_low;
    struct timespec req_on, req_off;
    int running;
    struct pwm *next;
};
struct pwm *pwm_list = NULL;

void remove_pwm(unsigned int gpio)
{
    struct pwm *p = pwm_list;
    struct pwm *prev = NULL;
    struct pwm *temp;

    while (p != NULL)
    {
        if (p->gpio == gpio)
        {
            if (prev == NULL)
            {
                pwm_list = p->next;
            }
            else
            {
                prev->next = p->next;
            }
            temp = p;
            p = p->next;
            temp->running = 0; // signal the thread to stop. The thread will free() the pwm struct when it's done with it.
        }
        else
        {
            prev = p;
            p = p->next;
        }
    }
}


void calculate_times(struct pwm *p)
{

    int full_cycle, cycle_high, cycle_low;
    // printf("freq=%d\r\n", p->freq);
    // printf("dutycycle=%d\r\n", p->dutycycle);

    full_cycle = NS_1S / p->freq;
    cycle_high = full_cycle / DUTY_CYCLE_FULL * p->dutycycle;
    cycle_low = full_cycle - cycle_high;

    // printf("cycle_high=%d\r\n", cycle_high);
    // printf("cycle_low=%d\r\n", cycle_low);
    p->req_on.tv_sec = 0;
    p->req_on.tv_nsec = (long)cycle_high;

    p->req_off.tv_sec = 0;
    p->req_off.tv_nsec = (long)cycle_low;
}
void full_sleep(struct timespec *req)
{
    struct timespec rem = {0};

    if (nanosleep(req, &rem) == -1)
    {
        // printf("nanosleep(req, &rem) == -1");
        full_sleep(&rem);
    }
        usleep(100);
}   

void *pwm_thread(void *threadarg)
{
    struct pwm *p = (struct pwm *)threadarg;
    // printf("pwm_thread\r\n");
    while (p->running)
    {
        if (p->dutycycle > 0)
        {
            // printf("-");
            gpio_out(p->gpio, 1);
            
            // usleep(p->cycle_high);
            full_sleep(&p->req_on);
        }

        if (p->dutycycle < DUTY_CYCLE_FULL)
        {
            // printf("+");
            gpio_out(p->gpio, 0);
            // usleep(p->cycle_low);

            full_sleep(&p->req_off);
        }
    }
    gpio_out(p->gpio, 0);
    // clean up
    free(p);
    pthread_exit(NULL);
}

struct pwm *add_new_pwm(unsigned int gpio)
{
    struct pwm *new_pwm;

    new_pwm = malloc(sizeof(struct pwm));
    new_pwm->gpio = gpio;
    new_pwm->running = 0;
    new_pwm->next = NULL;
    new_pwm->freq = 1000;
    new_pwm->dutycycle = 500;

    calculate_times(new_pwm);
    return new_pwm;
}

struct pwm *find_pwm(unsigned int gpio)
/* Return the pwm record for gpio, creating it if it does not exist */
{
    struct pwm *p = pwm_list;

    if (pwm_list == NULL)
    {
        pwm_list = add_new_pwm(gpio);
        return pwm_list;
    }

    while (p != NULL)
    {
        if (p->gpio == gpio)
            return p;
        if (p->next == NULL)
        {
            p->next = add_new_pwm(gpio);
            return p->next;
        }
        p = p->next;
    }
    return NULL;
}

int pwm_get_duty_cycle(unsigned int gpio)
{
    struct pwm *p;

    if ((p = find_pwm(gpio)) != NULL)
        return p->dutycycle;
    return -1;
}
int pwm_get_frequency(unsigned int gpio)
{
    struct pwm *p;

    if ((p = find_pwm(gpio)) != NULL)
        return p->freq;
    return -1;
}
void pwm_set_duty_cycle(unsigned int gpio, int dutycycle)
{
    struct pwm *p;

    if (dutycycle < 0 || dutycycle > DUTY_CYCLE_FULL)
    {
        // btc fixme - error
        return;
    }

    if ((p = find_pwm(gpio)) != NULL)
    {
        p->dutycycle = dutycycle;
        calculate_times(p);
    }
}

void pwm_set_frequency(unsigned int gpio, int freq)
{
    struct pwm *p;
    if (freq <= 0) // to avoid divide by zero
    {
        // btc fixme - error
        return;
    }

    if ((p = find_pwm(gpio)) != NULL)
    {
        p->freq = freq;
        calculate_times(p);
    }
}

void pwm_start(unsigned int gpio)
{
    pthread_t threads;
    struct pwm *p;

    if (((p = find_pwm(gpio)) == NULL) || p->running)
        return;

    p->running = 1;
    if (pthread_create(&threads, NULL, pwm_thread, (void *)p) != 0)
    {
        // btc fixme - error
        p->running = 0;
        return;
    }
    pthread_detach(threads);
}

void pwm_stop(unsigned int gpio)
{
    remove_pwm(gpio);
}

// returns 1 if there is a PWM for this gpio, 0 otherwise
int pwm_exists(unsigned int gpio)
{
    struct pwm *p = pwm_list;

    while (p != NULL)
    {
        if (p->gpio == gpio)
        {
            return 1;
        }
        else
        {
            p = p->next;
        }
    }
    return 0;
}

// int main()
// {
//     gpio_out = H616_gpio_write;
//     pwm_set_duty_cycle(270, 1);
//     pwm_set_frequency(270, 1000);
//     pwm_start(270);
//     while (1)
//         ;
//     //  gpio_out(270, 0);
//     return 0;
// }