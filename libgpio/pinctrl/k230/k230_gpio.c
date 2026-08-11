#include "k230_gpio.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>

#define readl(addr) (*(volatile uint32_t *)(addr))
#define writel(value, addr) (*(volatile uint32_t *)(addr) = (value))

#ifndef BIT
#define BIT(x) (1U << (x))
#endif

#define write32(addr, value) writel(value, (volatile void *)(uint64_t)(addr))
#define read32(addr) readl((const volatile void *)(uint64_t)(addr))

typedef enum _gpio_pin_value
{
    GPIO_PV_LOW,
    GPIO_PV_HIGH
} gpio_pin_value_t;

static inline __attribute__((always_inline)) void kd_pin_write_reg(volatile uint32_t *reg, int pin, int val)
{
    uint32_t reg_val = read32(reg);
    reg_val &= ~BIT(pin);
    if (val)
    {
        reg_val |= BIT(pin);
    }
    write32(reg, reg_val);
}

typedef struct _kd_gpio
{
    struct
    {
        volatile uint32_t dr;  // 0x00: Write Data register
        volatile uint32_t ddr; // 0x04: Data direction register
        volatile uint32_t ctl; // 0x08: Control register
    } port[4];                 /* 0x00 - 0x2C: port control registers */

    volatile uint32_t inten;         /* 0x30: interrupt enable register */
    volatile uint32_t intmask;       /* 0x34: interrupt mask register */
    volatile uint32_t inttype_level; /* 0x38: interrupt type level register */
    volatile uint32_t int_polarity;  /* 0x3C: interrupt polarity register */
    volatile uint32_t intstatus;     /* 0x40: interrupt status register */
    volatile uint32_t raw_intstatus; /* 0x44: raw interrupt status register */
    volatile uint32_t debounce;      /* 0x48: debounce register */
    volatile uint32_t porta_eoi;     /* 0x4C: port a end of interrupt register */

    volatile uint32_t input[4];          /* 0x50-0x5C: porta/b/c/d input */
    volatile uint32_t ls_sync;           /* 0x60: level sync register */
    volatile uint32_t id_code;           /* 0x64: ID code register */
    volatile uint32_t int_bothedge;      /* 0x68: interrupt both-edge register */
    volatile uint32_t gpio_comp_version; /* 0x6C: GPIO component version register */
    volatile uint32_t config2;           /* 0x70: configuration register 2 */
    volatile uint32_t config1;           /* 0x74: configuration register 1 */
} kd_gpio_t;

typedef struct _kd_gpio_inst
{
    volatile kd_gpio_t *reg[2]; // 0: GPIO0, 1: GPIO1

} kd_gpio_inst_t;

static kd_gpio_inst_t _gpio_inst;

void kd_pin_init()
{
    int fd = open("/dev/mem", O_RDWR | O_SYNC);
    if (fd < 0)
    {
        perror("Failed to open /dev/mem");
        exit(EXIT_FAILURE);
    }

    _gpio_inst.reg[0] = (volatile kd_gpio_t *)mmap(NULL, GPIO0_IO_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, GPIO0_BASE_ADDR);
    _gpio_inst.reg[1] = (volatile kd_gpio_t *)mmap(NULL, GPIO1_IO_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, GPIO1_BASE_ADDR);

    if (_gpio_inst.reg[0] == MAP_FAILED || _gpio_inst.reg[1] == MAP_FAILED)
    {
        perror("Failed to mmap GPIO registers");
        close(fd);
        exit(EXIT_FAILURE);
    }
}
uint32_t kd_pin_get_ddr(int pin)
{
    /* Magic pin mapping: 0-31:gpio0, 32-63:gpio1[0], 64-71:gpio1[1] */
    volatile kd_gpio_t *gpio = _gpio_inst.reg[pin >= 32];
    uint8_t port_idx = (pin >= 64);
    uint8_t port_pin = pin & 0x1F;

    /* Set GPIO direction */
    volatile uint32_t *ddr = &gpio->port[port_idx].ddr;

    /* Read pin state */
    uint32_t input_val = read32(ddr);
    return (input_val & BIT(port_pin)) ? 1 : 0;
}
void kd_pin_set_ddr(int pin, int value)
{
    /* Magic pin mapping: 0-31:gpio0, 32-63:gpio1[0], 64-71:gpio1[1] */
    volatile kd_gpio_t* gpio     = _gpio_inst.reg[pin >= 32];
    uint8_t             port_idx = (pin >= 64);
    uint8_t             port_pin = pin & 0x1F;

    /* Set GPIO direction */
    volatile uint32_t* ddr = &gpio->port[port_idx].ddr;
    kd_pin_write_reg(ddr, port_pin, value);
}
void kd_pin_set_dr(int pin, int value)
{
    /* Magic pin mapping: 0-31:gpio0, 32-63:gpio1[0], 64-71:gpio1[1] */
    volatile kd_gpio_t *gpio = _gpio_inst.reg[pin >= 32];
    uint8_t port_idx = (pin >= 64);
    uint8_t port_pin = pin & 0x1F;

    /* Set GPIO Ouput Value */
    volatile uint32_t *dr = &gpio->port[port_idx].dr;
    kd_pin_write_reg(dr, port_pin, value);
}

uint32_t kd_pin_get_dr(int pin)
{
    /* Magic pin mapping: 0-31:gpio0, 32-63:gpio1[0], 64-71:gpio1[1] */
    volatile kd_gpio_t *gpio = _gpio_inst.reg[pin >= 32];
    uint8_t port_idx = (pin >= 64);
    uint8_t port_pin = pin & 0x1F;
    volatile uint32_t *input_reg = &gpio->input[port_idx];

    /* Read pin state */
    uint32_t input_val = read32(input_reg);
    return (input_val & BIT(port_pin)) ? GPIO_PV_HIGH : GPIO_PV_LOW;
}
