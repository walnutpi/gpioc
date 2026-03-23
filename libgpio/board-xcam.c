#include "board-pin.h"
#include "pin-num.h"
struct BOARD_PIN xcamK230_pins[] = {
    DEF_A_BOARD_PIN(0, 0, "", 0),
    DEF_A_BOARD_PIN(1, PH_5V, "5v", PH_COLOR_RED),
    DEF_A_BOARD_PIN(2, PH_GND, "GND", PH_COLOR_BLACK),
    DEF_A_BOARD_PIN(3, PH_3V3, "3.3v", PH_COLOR_YELLOW),
    DEF_A_BOARD_PIN(4, PH_GND, "GND", PH_COLOR_BLACK),
    DEF_A_BOARD_PIN(5, 14, "IO14", PH_COLOR_GREEEN),
    DEF_A_BOARD_PIN(6, 15, "IO15", PH_COLOR_GREEEN),
    DEF_A_BOARD_PIN(7, 16, "IO16", PH_COLOR_GREEEN),
    DEF_A_BOARD_PIN(8, 17, "IO17", PH_COLOR_GREEEN),
    DEF_A_BOARD_PIN(9, 60, "IO60", PH_COLOR_GREEEN),
    DEF_A_BOARD_PIN(10, 61, "IO61", PH_COLOR_GREEEN),
    DEF_A_BOARD_PIN(11, PH_GND, "ADC0", PH_COLOR_GREEEN),
    DEF_A_BOARD_PIN(12, PH_GND, "ADC1", PH_COLOR_GREEEN),
    DEF_A_BOARD_PIN(13, 21, "KEY", PH_COLOR_BLACK),
    DEF_A_BOARD_PIN(14, 52, "LED", PH_COLOR_BLACK),
    DEF_A_BOARD_PIN(15, 46, "LIGHT", PH_COLOR_BLACK),
    DEF_A_BOARD_PIN(16, 47, "BEEP", PH_COLOR_BLACK),
};

static struct PIN_with_PER PIN_PER_PWM[] = {
    DEF_A_BOARD_PIN_PER(15, 3),
    DEF_A_BOARD_PIN_PER(16, 3),

};
static struct BOARD_PIN_PER xcamK230_pwms =
    {
        .count = sizeof(PIN_PER_PWM) / sizeof(struct PIN_with_PER),
        .the_pins = PIN_PER_PWM,
};
static struct PIN_with_PER PIN_PER_UART[] = {
};
static struct BOARD_PIN_PER xcamK230_uarts =
    {
        .count = sizeof(PIN_PER_UART) / sizeof(struct PIN_with_PER),
        .the_pins = PIN_PER_UART,
};

static struct PIN_with_PER PIN_PER_SPI[] = {
    DEF_A_BOARD_PIN_PER(5, 4),
    DEF_A_BOARD_PIN_PER(6, 4),
    DEF_A_BOARD_PIN_PER(7, 4),
    DEF_A_BOARD_PIN_PER(8, 4),
    DEF_A_BOARD_PIN_PER(10, 4),
};
static struct BOARD_PIN_PER xcamK230_spis =
    {
        .count = sizeof(PIN_PER_SPI) / sizeof(struct PIN_with_PER),
        .the_pins = PIN_PER_SPI,
};

static struct PIN_with_PER PIN_PER_I2C[] = {
};
static struct BOARD_PIN_PER xcamK230_i2cs =
    {
        .count = sizeof(PIN_PER_I2C) / sizeof(struct PIN_with_PER),
        .the_pins = PIN_PER_I2C,
};
static struct PIN_mode_rename pin_mode_renames[] = {
    DEF_A_BOARD_PIN_MODE_RENAME(16, 4, "SPI0_MOSI"),
    DEF_A_BOARD_PIN_MODE_RENAME(17, 4, "SPI0_MISO"),
    DEF_A_BOARD_PIN_MODE_RENAME(15, 4, "SPI0_CLK"),
    DEF_A_BOARD_PIN_MODE_RENAME(14, 4, "SPI0_CS0"),
    DEF_A_BOARD_PIN_MODE_RENAME(61, 4, "SPI0_CS1"),
};
static struct BOARD_mode_rename xcamK230_pin_mode_renames =
    {
        .count = sizeof(pin_mode_renames) / sizeof(struct PIN_mode_rename),
        .the_pins = pin_mode_renames,
};
struct BOARD_DESC xcamK230 = {
    .model = "01studio-xcam",
    .pin_num = 16,
    .header_num = 12,
    .pins = xcamK230_pins,
    .pwms = &xcamK230_pwms,
    .uarts = &xcamK230_uarts,
    .spis = &xcamK230_spis,
    .i2cs = &xcamK230_i2cs,
    .mode_renames = &xcamK230_pin_mode_renames,
};