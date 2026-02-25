#include "pinctrl-k230.h"
#include "../pinctrl.h"
#include "drv_fpioa.h"
#include "k230_gpio.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <dirent.h>

const char *_fpioa_func_desc[] = {
    "GPIO0",
    "GPIO1",
    "GPIO2",
    "GPIO3",
    "GPIO4",
    "GPIO5",
    "GPIO6",
    "GPIO7",
    "GPIO8",
    "GPIO9",
    "GPIO10",
    "GPIO11",
    "GPIO12",
    "GPIO13",
    "GPIO14",
    "GPIO15",
    "GPIO16",
    "GPIO17",
    "GPIO18",
    "GPIO19",
    "GPIO20",
    "GPIO21",
    "GPIO22",
    "GPIO23",
    "GPIO24",
    "GPIO25",
    "GPIO26",
    "GPIO27",
    "GPIO28",
    "GPIO29",
    "GPIO30",
    "GPIO31",
    "GPIO32",
    "GPIO33",
    "GPIO34",
    "GPIO35",
    "GPIO36",
    "GPIO37",
    "GPIO38",
    "GPIO39",
    "GPIO40",
    "GPIO41",
    "GPIO42",
    "GPIO43",
    "GPIO44",
    "GPIO45",
    "GPIO46",
    "GPIO47",
    "GPIO48",
    "GPIO49",
    "GPIO50",
    "GPIO51",
    "GPIO52",
    "GPIO53",
    "GPIO54",
    "GPIO55",
    "GPIO56",
    "GPIO57",
    "GPIO58",
    "GPIO59",
    "GPIO60",
    "GPIO61",
    "GPIO62",
    "GPIO63",
    "GPIO64",
    "GPIO65",
    "GPIO66",
    "GPIO67",
    "GPIO68",
    "GPIO69",
    "GPIO70",
    "GPIO71",
    "BOOT0",
    "BOOT1",
    "CI0",
    "CI1",
    "CI2",
    "CI3",
    "CO0",
    "CO1",
    "CO2",
    "CO3",
    "DI0",
    "DI1",
    "DI2",
    "DI3",
    "DO0",
    "DO1",
    "DO2",
    "DO3",
    "HSYNC0",
    "HSYNC1",
    "IIC0_SCL",
    "IIC0_SDA",
    "IIC1_SCL",
    "IIC1_SDA",
    "IIC2_SCL",
    "IIC2_SDA",
    "IIC3_SCL",
    "IIC3_SDA",
    "IIC4_SCL",
    "IIC4_SDA",
    "IIS_CLK",
    "IIS_D_IN0_PDM_IN3",
    "IIS_D_IN1_PDM_IN2",
    "IIS_D_OUT0_PDM_IN1",
    "IIS_D_OUT1_PDM_IN0",
    "IIS_WS",
    "JTAG_RST",
    "JTAG_TCK",
    "JTAG_TDI",
    "JTAG_TDO",
    "JTAG_TMS",
    "M_CLK1",
    "M_CLK2",
    "M_CLK3",
    "MMC1_CLK",
    "MMC1_CMD",
    "MMC1_D0",
    "MMC1_D1",
    "MMC1_D2",
    "MMC1_D3",
    "OSPI_CLK",
    "OSPI_CS",
    "OSPI_D0",
    "OSPI_D1",
    "OSPI_D2",
    "OSPI_D3",
    "OSPI_D4",
    "OSPI_D5",
    "OSPI_D6",
    "OSPI_D7",
    "OSPI_DQS",
    "PDM_IN0",
    "PDM_IN1",
    "PDM_IN2",
    "PDM_IN3",
    "PULSE_CNTR0",
    "PULSE_CNTR1",
    "PULSE_CNTR2",
    "PULSE_CNTR3",
    "PULSE_CNTR4",
    "PULSE_CNTR5",
    "PWM0",
    "PWM1",
    "PWM2",
    "PWM3",
    "PWM4",
    "PWM5",
    "QSPI0_CLK",
    "QSPI0_CS0",
    "QSPI0_CS1",
    "QSPI0_CS2",
    "QSPI0_CS3",
    "QSPI0_CS4",
    "QSPI0_D0",
    "QSPI0_D1",
    "QSPI0_D2",
    "QSPI0_D3",
    "QSPI1_CLK",
    "QSPI1_CS0",
    "QSPI1_CS1",
    "QSPI1_CS2",
    "QSPI1_CS3",
    "QSPI1_CS4",
    "QSPI1_D0",
    "QSPI1_D1",
    "QSPI1_D2",
    "QSPI1_D3",
    "SPI2AXI_CK",
    "SPI2AXI_CS",
    "SPI2AXI_DI",
    "SPI2AXI_DO",
    "UART0_RXD",
    "UART0_TXD",
    "UART1_CTS",
    "UART1_RTS",
    "UART1_RXD",
    "UART1_TXD",
    "UART2_CTS",
    "UART2_RTS",
    "UART2_RXD",
    "UART2_TXD",
    "UART3_CTS",
    "UART3_DE",
    "UART3_RE",
    "UART3_RTS",
    "UART3_RXD",
    "UART3_TXD",
    "UART4_RXD",
    "UART4_TXD",
    "PDM_CLK",
    "VSYNC0",
    "VSYNC1",
    "CTRL_IN_3D",
    "CTRL_O1_3D",
    "CTRL_O2_3D",
    "PMU_INT0",
    "PMU_INT1",
    "PMU_INT2",
    "PMU_INT3",
    "PMU_INT4",
    "PMU_INT5",
    "PMU_OUT0",
    "PMU_OUT1",
    "TEST_PIN0",
    "TEST_PIN1",
    "TEST_PIN2",
    "TEST_PIN3",
    "TEST_PIN4",
    "TEST_PIN5",
    "TEST_PIN6",
    "TEST_PIN7",
    "TEST_PIN8",
    "TEST_PIN9",
    "TEST_PIN10",
    "TEST_PIN11",
    "TEST_PIN12",
    "TEST_PIN13",
    "TEST_PIN14",
    "TEST_PIN15",
    "TEST_PIN16",
    "TEST_PIN17",
    "TEST_PIN18",
    "TEST_PIN19",
    "TEST_PIN20",
    "TEST_PIN21",
    "TEST_PIN22",
    "TEST_PIN23",
    "TEST_PIN24",
    "TEST_PIN25",
    "TEST_PIN26",
    "TEST_PIN27",
    "TEST_PIN28",
    "TEST_PIN29",
    "TEST_PIN30",
    "TEST_PIN31",
};
bool k230_init()
{
    kd_pin_init();
    return true;
}
void k230_pin_set_mode(int gpio_num, int mode)
{
    fpioa_iomux_cfg_t cfg;
    drv_fpioa_get_pin_cfg(gpio_num, &cfg.u.value);
    switch (mode)
    {
    case 0:
        cfg.u.bit.ie = 1;
        cfg.u.bit.oe = 0;
        cfg.u.bit.io_sel = 0;
        kd_pin_set_ddr(gpio_num, 0);
        break;
    case 1:
        cfg.u.bit.ie = 1;
        cfg.u.bit.oe = 1;
        cfg.u.bit.io_sel = 0;
        kd_pin_set_ddr(gpio_num, 1);
        break;
    default:
        cfg.u.bit.ie = 1;
        cfg.u.bit.oe = 0;
        cfg.u.bit.io_sel = mode - 1;
        break;
    }
    drv_fpioa_set_pin_cfg(gpio_num, cfg.u.value);
}
int k230_pin_get_mode(int gpio_num)
{
    fpioa_iomux_cfg_t cfg;
    drv_fpioa_get_pin_cfg(gpio_num, &cfg.u.value);
    if (cfg.u.bit.io_sel == 0)
    {
        return kd_pin_get_ddr(gpio_num);
    }
    return cfg.u.bit.io_sel + 1;
}
int k230_pinctrl_read(int gpio_num)
{
    return kd_pin_get_dr(gpio_num);
}
void k230_pinctrl_write(int gpio_num, int value)
{
    kd_pin_set_dr(gpio_num, value);
}
void k230_pinctrl_set_pullUpDn(int gpio_num, int pud)
{
    fpioa_iomux_cfg_t cfg;
    drv_fpioa_get_pin_cfg(gpio_num, &cfg.u.value);
    switch (pud)
    {
    case PULL_DOWN:
        cfg.u.bit.pd = 1;
        cfg.u.bit.pu = 0;
        break;
    case PULL_UP:
        cfg.u.bit.pd = 0;
        cfg.u.bit.pu = 1;
        break;
    default:
        cfg.u.bit.pd = 0;
        cfg.u.bit.pu = 0;
        break;
    }
    drv_fpioa_set_pin_cfg(gpio_num, cfg.u.value);
}
void k230_who_has_function(char *name_buf, int len) {}
const char *k230_pinctrl_pin_get_mode_name(int gpio_num)
{
    fpioa_func_t func;
    fpioa_iomux_cfg_t cfg;
    drv_fpioa_get_pin_func(gpio_num, &func);
    if (GPIO71 >= func)
    {
        drv_fpioa_get_pin_cfg(gpio_num, &cfg.u.value);
        if (kd_pin_get_ddr(gpio_num))
            return "OUT";
        else
            return "IN";
    }
    return _fpioa_func_desc[func];
}
const char *k230_pinctrl_pin_get_mode_name_by_num(int gpio_num, int mode_num)
{
    fpioa_func_t funcs[FPIOA_PIN_MAX_FUNCS];
    if (mode_num > FPIOA_PIN_MAX_FUNCS)
        return "RESERVED";
    switch (mode_num)
    {
    case 0:
        return "IN";
    case 1:
        return "OUT";
    }
    drv_fpioa_pin_supported_funcs(gpio_num, funcs);
    return _fpioa_func_desc[funcs[mode_num - 2]];
}
void k230_mode_rename(int gpio_num, int mode_num, char *name) {}