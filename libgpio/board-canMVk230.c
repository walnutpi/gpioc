#include "board-pin.h"
#include "pin-num.h"
struct BOARD_PIN canMVk230_pins[] = {
    DEF_A_BOARD_PIN(0, 0, "", 0),
    DEF_A_BOARD_PIN(1, PH_3V3, "3.3v", PH_COLOR_YELLOW),
    DEF_A_BOARD_PIN(2, PH_5V, "5v", PH_COLOR_RED),
    DEF_A_BOARD_PIN(3, 12, "IO12", PH_COLOR_GREEEN),
    DEF_A_BOARD_PIN(4, PH_5V, "5v", PH_COLOR_RED),
    DEF_A_BOARD_PIN(5, 11, "IO11", PH_COLOR_GREEEN),
    DEF_A_BOARD_PIN(6, PH_GND, "GND", PH_COLOR_BLACK),
    DEF_A_BOARD_PIN(7, 2, "IO2", PH_COLOR_GREEEN),
    DEF_A_BOARD_PIN(8, 3, "IO3", PH_COLOR_GREEEN),
    DEF_A_BOARD_PIN(9, PH_GND, "GND", PH_COLOR_BLACK),
    DEF_A_BOARD_PIN(10, 4, "IO4", PH_COLOR_GREEEN),
    DEF_A_BOARD_PIN(11, 5, "IO5", PH_COLOR_GREEEN),
    DEF_A_BOARD_PIN(12, 6, "IO6", PH_COLOR_GREEEN),
    DEF_A_BOARD_PIN(13, 42, "IO42", PH_COLOR_GREEEN),
    DEF_A_BOARD_PIN(14, PH_GND, "GND", PH_COLOR_BLACK),
    DEF_A_BOARD_PIN(15, 43, "IO43", PH_COLOR_GREEEN),
    DEF_A_BOARD_PIN(16, 46, "IO10", PH_COLOR_GREEEN),
    DEF_A_BOARD_PIN(17, PH_3V3, "3.3v", PH_COLOR_YELLOW),
    DEF_A_BOARD_PIN(18, 47, "IO9", PH_COLOR_GREEEN),
    DEF_A_BOARD_PIN(19, 16, "IO16", PH_COLOR_GREEEN),
    DEF_A_BOARD_PIN(20, PH_GND, "GND", PH_COLOR_BLACK),
    DEF_A_BOARD_PIN(21, 17, "IO17", PH_COLOR_GREEEN),
    DEF_A_BOARD_PIN(22, 18, "IO18", PH_COLOR_GREEEN),
    DEF_A_BOARD_PIN(23, 15, "IO15", PH_COLOR_GREEEN),
    DEF_A_BOARD_PIN(24, 14, "IO14", PH_COLOR_GREEEN),
    DEF_A_BOARD_PIN(25, PH_GND, "GND", PH_COLOR_BLACK),
    DEF_A_BOARD_PIN(26, 61, "IO61", PH_COLOR_GREEEN),
    DEF_A_BOARD_PIN(27, 19, "IO19", PH_COLOR_BLUE),
    DEF_A_BOARD_PIN(28, 60, "IO60", PH_COLOR_BLUE),
    DEF_A_BOARD_PIN(29, 20, "IO20", PH_COLOR_GREEEN),
    DEF_A_BOARD_PIN(30, PH_GND, "GND", PH_COLOR_BLACK),
    DEF_A_BOARD_PIN(31, 32, "IO32", PH_COLOR_GREEEN),
    DEF_A_BOARD_PIN(32, PH_GND, "ADC0", PH_COLOR_GREEEN),
    DEF_A_BOARD_PIN(33, 33, "IO33", PH_COLOR_GREEEN),
    DEF_A_BOARD_PIN(34, PH_GND, "GND", PH_COLOR_BLACK),
    DEF_A_BOARD_PIN(35, 34, "IO34", PH_COLOR_GREEEN),
    DEF_A_BOARD_PIN(36, PH_GND, "ADC1", PH_COLOR_GREEEN),
    DEF_A_BOARD_PIN(37, 35, "IO35", PH_COLOR_GREEEN),
    DEF_A_BOARD_PIN(38, PH_GND, "ADC2", PH_COLOR_GREEEN),
    DEF_A_BOARD_PIN(39, PH_GND, "GND", PH_COLOR_BLACK),
    DEF_A_BOARD_PIN(40, PH_GND, "ADC3", PH_COLOR_GREEEN),
    DEF_A_BOARD_PIN(41, 21, "KEY", PH_COLOR_BLACK),
    DEF_A_BOARD_PIN(42, 52, "LED", PH_COLOR_BLACK),
};

static struct PIN_with_PER PIN_PER_PWM[] = {
    DEF_A_BOARD_PIN_PER(5, 5),
    DEF_A_BOARD_PIN_PER(7, 5),
    DEF_A_BOARD_PIN_PER(13, 4),
    DEF_A_BOARD_PIN_PER(15, 4),
    DEF_A_BOARD_PIN_PER(19, 4),
    DEF_A_BOARD_PIN_PER(21, 4),
    DEF_A_BOARD_PIN_PER(23, 4),
    DEF_A_BOARD_PIN_PER(27, 4),
    DEF_A_BOARD_PIN_PER(29, 3),
    DEF_A_BOARD_PIN_PER(31, 4),
    DEF_A_BOARD_PIN_PER(33, 4),
    DEF_A_BOARD_PIN_PER(35, 4),
    DEF_A_BOARD_PIN_PER(37, 4),
    DEF_A_BOARD_PIN_PER(16, 4),
    DEF_A_BOARD_PIN_PER(22, 4),
    DEF_A_BOARD_PIN_PER(24, 4),
    DEF_A_BOARD_PIN_PER(26, 4),
    DEF_A_BOARD_PIN_PER(28, 4),
    DEF_A_BOARD_PIN_PER(32, 4),
    DEF_A_BOARD_PIN_PER(36, 4),
    DEF_A_BOARD_PIN_PER(38, 4),
    DEF_A_BOARD_PIN_PER(40, 4),
    DEF_A_BOARD_PIN_PER(42, 6),
};
static struct BOARD_PIN_PER canMVk230_pwms =
    {
        .count = sizeof(PIN_PER_PWM) / sizeof(struct PIN_with_PER),
        .the_pins = PIN_PER_PWM,
};
static struct PIN_with_PER PIN_PER_UART[] = {
    DEF_A_BOARD_PIN_PER(11, 3),
    DEF_A_BOARD_PIN_PER(13, 2),
    DEF_A_BOARD_PIN_PER(15, 2),
    DEF_A_BOARD_PIN_PER(23, 2),
    DEF_A_BOARD_PIN_PER(35, 2),
    DEF_A_BOARD_PIN_PER(37, 2),
    DEF_A_BOARD_PIN_PER(8, 2),
    DEF_A_BOARD_PIN_PER(10, 2),
    DEF_A_BOARD_PIN_PER(12, 3),
    DEF_A_BOARD_PIN_PER(22, 2),
    DEF_A_BOARD_PIN_PER(24, 2),
    DEF_A_BOARD_PIN_PER(26, 2),
    DEF_A_BOARD_PIN_PER(38, 3),
    DEF_A_BOARD_PIN_PER(40, 3),

};
static struct BOARD_PIN_PER canMVk230_uarts =
    {
        .count = sizeof(PIN_PER_UART) / sizeof(struct PIN_with_PER),
        .the_pins = PIN_PER_UART,
};

static struct PIN_with_PER PIN_PER_SPI[] = {
    DEF_A_BOARD_PIN_PER(19, 3),
    DEF_A_BOARD_PIN_PER(21, 3),
    DEF_A_BOARD_PIN_PER(23, 3),
    DEF_A_BOARD_PIN_PER(24, 3),
    DEF_A_BOARD_PIN_PER(26, 1),
};
static struct BOARD_PIN_PER canMVk230_spis =
    {
        .count = sizeof(PIN_PER_SPI) / sizeof(struct PIN_with_PER),
        .the_pins = PIN_PER_SPI,
};

static struct PIN_with_PER PIN_PER_I2C[] = {
    DEF_A_BOARD_PIN_PER(3, 2),
    DEF_A_BOARD_PIN_PER(5, 2),
    DEF_A_BOARD_PIN_PER(27, 3),
    DEF_A_BOARD_PIN_PER(28, 3),
};
static struct BOARD_PIN_PER canMVk230_i2cs =
    {
        .count = sizeof(PIN_PER_I2C) / sizeof(struct PIN_with_PER),
        .the_pins = PIN_PER_I2C,
};
static struct PIN_mode_rename pin_mode_renames[] = {
};
static struct BOARD_mode_rename canMVk230_pin_mode_renames =
    {
        .count = sizeof(pin_mode_renames) / sizeof(struct PIN_mode_rename),
        .the_pins = pin_mode_renames,
};
struct BOARD_DESC canMVk230 = {
    .model = "CanMV-K230",
    .pin_num = 42,
    .pins = canMVk230_pins,
    .pwms = &canMVk230_pwms,
    .uarts = &canMVk230_uarts,
    .spis = &canMVk230_spis,
    .i2cs = &canMVk230_i2cs,
    .mode_renames = &canMVk230_pin_mode_renames,
};