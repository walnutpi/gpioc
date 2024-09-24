#include "board-pin.h"

struct BOARD_PIN walnutpi1b_pins[] = {
    DEF_A_BOARD_PIN(0, 0, "", 0),
    DEF_A_BOARD_PIN(1, PH_3V3, "3.3v", PH_COLOR_YELLOW),
    DEF_A_BOARD_PIN(2, PH_5V, "5v", PH_COLOR_RED),
    DEF_A_BOARD_PIN(3, 264, "PI8", PH_COLOR_GREEEN),
    DEF_A_BOARD_PIN(4, PH_5V, "5v", PH_COLOR_RED),
    DEF_A_BOARD_PIN(5, 263, "PI7", PH_COLOR_GREEEN),
    DEF_A_BOARD_PIN(6, PH_GND, "GND", PH_COLOR_BLACK),
    DEF_A_BOARD_PIN(7, 72, "PC8", PH_COLOR_GREEEN),
    DEF_A_BOARD_PIN(8, 261, "PI5", PH_COLOR_GREEEN),
    DEF_A_BOARD_PIN(9, PH_GND, "GND", PH_COLOR_BLACK),
    DEF_A_BOARD_PIN(10, 262, "PI6", PH_COLOR_GREEEN),
    DEF_A_BOARD_PIN(11, 73, "PC9", PH_COLOR_GREEEN),
    DEF_A_BOARD_PIN(12, 74, "PC10", PH_COLOR_GREEEN),
    DEF_A_BOARD_PIN(13, 75, "PC11", PH_COLOR_GREEEN),
    DEF_A_BOARD_PIN(14, PH_GND, "GND", PH_COLOR_BLACK),
    DEF_A_BOARD_PIN(15, 267, "PI11", PH_COLOR_GREEEN),
    DEF_A_BOARD_PIN(16, 268, "PI12", PH_COLOR_GREEEN),
    DEF_A_BOARD_PIN(17, PH_3V3, "3.3v", PH_COLOR_YELLOW),
    DEF_A_BOARD_PIN(18, 78, "PC14", PH_COLOR_GREEEN),
    DEF_A_BOARD_PIN(19, 231, "PH7", PH_COLOR_GREEEN),
    DEF_A_BOARD_PIN(20, PH_GND, "GND", PH_COLOR_BLACK),
    DEF_A_BOARD_PIN(21, 232, "PH8", PH_COLOR_GREEEN),
    DEF_A_BOARD_PIN(22, 79, "PC15", PH_COLOR_GREEEN),
    DEF_A_BOARD_PIN(23, 230, "PH6", PH_COLOR_GREEEN),
    DEF_A_BOARD_PIN(24, 229, "PH5", PH_COLOR_GREEEN),
    DEF_A_BOARD_PIN(25, PH_GND, "GND", PH_COLOR_BLACK),
    DEF_A_BOARD_PIN(26, 233, "PH9", PH_COLOR_GREEEN),
    DEF_A_BOARD_PIN(27, 266, "PI10", PH_COLOR_BLUE),
    DEF_A_BOARD_PIN(28, 265, "PI9", PH_COLOR_BLUE),
    DEF_A_BOARD_PIN(29, 256, "PI0", PH_COLOR_GREEEN),
    DEF_A_BOARD_PIN(30, PH_GND, "GND", PH_COLOR_BLACK),
    DEF_A_BOARD_PIN(31, 257, "PI1", PH_COLOR_GREEEN),
    DEF_A_BOARD_PIN(32, 272, "PI16", PH_COLOR_GREEEN),
    DEF_A_BOARD_PIN(33, 258, "PI2", PH_COLOR_GREEEN),
    DEF_A_BOARD_PIN(34, PH_GND, "GND", PH_COLOR_BLACK),
    DEF_A_BOARD_PIN(35, 259, "PI3", PH_COLOR_GREEEN),
    DEF_A_BOARD_PIN(36, 271, "PI15", PH_COLOR_GREEEN),
    DEF_A_BOARD_PIN(37, 260, "PI4", PH_COLOR_GREEEN),
    DEF_A_BOARD_PIN(38, 269, "PI13", PH_COLOR_GREEEN),
    DEF_A_BOARD_PIN(39, PH_GND, "GND", PH_COLOR_BLACK),
    DEF_A_BOARD_PIN(40, 270, "PI14", PH_COLOR_GREEEN),
    DEF_A_BOARD_PIN(41, 76, "KEY", PH_COLOR_BLACK),
    DEF_A_BOARD_PIN(42, 77, "LED", PH_COLOR_BLACK),
};
static int walnutpi1b_pwms_pins[] = {15, 16, 38, 40};
static int walnutpi1b_pwms_modes[] = {5, 5, 5, 5};
static struct BOARD_PIN_PER walnutpi1b_pwms =
    {
        .count = 4,
        .pins = walnutpi1b_pwms_pins,
        .modes = walnutpi1b_pwms_modes,
};

static int walnutpi1b_uarts_pins[] = {8, 10, 38, 40};
static int walnutpi1b_uarts_modes[] = {3, 3, 3, 3};
static struct BOARD_PIN_PER walnutpi1b_uarts =
    {
        .count = 4,
        .pins = walnutpi1b_uarts_pins,
        .modes = walnutpi1b_uarts_modes,
};
static int walnutpi1b_spis_pins[] = {19, 21, 23, 24, 26};
static int walnutpi1b_spis_modes[] = {4, 4, 4, 4, 4};
static struct BOARD_PIN_PER walnutpi1b_spis =
    {
        .count = 4,
        .pins = walnutpi1b_spis_pins,
        .modes = walnutpi1b_spis_modes,
};
static int walnutpi1b_i2cs_pins[] = {3, 5, 27, 28};
static int walnutpi1b_i2cs_modes[] = {5, 5, 5, 5};
static struct BOARD_PIN_PER walnutpi1b_i2cs =
    {
        .count = 4,
        .pins = walnutpi1b_i2cs_pins,
        .modes = walnutpi1b_i2cs_modes,
};
struct BOARD_DESC walnutpi_1b = {
    .model = "walnutpi-1b",
    .pin_num = 42,
    .pins = walnutpi1b_pins,
    .pwms = &walnutpi1b_pwms,
    .uarts = &walnutpi1b_uarts,
    .spis = &walnutpi1b_spis,
    .i2cs = &walnutpi1b_i2cs,
};