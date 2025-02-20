// SPDX-License-Identifier: (GPL-2.0+ or MIT)
/* Copyright(c) 2020 - 2023 Allwinner Technology Co.,Ltd. All rights reserved. */
/*
 * Copyright (c) 2021 liujuan1@allwinnertech.com
 */

// #include <linux/module.h>
// #include <linux/platform_device.h>
// #include <linux/of.h>
// #include <linux/of_device.h>
// #include <linux/pinctrl/pinctrl.h>
#include "pinctrl-sunxi.h"

static const struct sunxi_desc_pin sun55iw3_r_pins[] = {
	/* BANK L */
	SUNXI_PIN(SUNXI_PINCTRL_PIN(L, 0),
		SUNXI_FUNCTION(0x0, "IN"),		
		SUNXI_FUNCTION(0x1, "OUT"),	
		SUNXI_FUNCTION(0x2, "I2C6_SCL"),
		SUNXI_FUNCTION_IRQ_BANK(0XE, 0, 0),
		SUNXI_FUNCTION(0xf, "OFF")),	

	SUNXI_PIN(SUNXI_PINCTRL_PIN(L, 1),
		SUNXI_FUNCTION(0x0, "IN"),		
		SUNXI_FUNCTION(0x1, "OUT"),	
		SUNXI_FUNCTION(0x2, "I2C6_SDA"),
		SUNXI_FUNCTION_IRQ_BANK(0XE, 0, 1),
		SUNXI_FUNCTION(0xf, "OFF")),	

	SUNXI_PIN(SUNXI_PINCTRL_PIN(L, 2),
		SUNXI_FUNCTION(0x0, "IN"),		
		SUNXI_FUNCTION(0x1, "OUT"),	
		SUNXI_FUNCTION(0x2, "UART8_TX"),
		SUNXI_FUNCTION(0x3, "UART9_TX"),
		SUNXI_FUNCTION(0x4, "PWM3-0"),
		SUNXI_FUNCTION_IRQ_BANK(0XE, 0, 2),
		SUNXI_FUNCTION(0xf, "OFF")),	

	SUNXI_PIN(SUNXI_PINCTRL_PIN(L, 3),
		SUNXI_FUNCTION(0x0, "IN"),		
		SUNXI_FUNCTION(0x1, "OUT"),	
		SUNXI_FUNCTION(0x2, "UART8_RX"),
		SUNXI_FUNCTION(0x3, "UART9_RX"),
		SUNXI_FUNCTION(0x4, "PWM3-1"),
		SUNXI_FUNCTION_IRQ_BANK(0XE, 0, 3),
		SUNXI_FUNCTION(0xf, "OFF")),	

	SUNXI_PIN(SUNXI_PINCTRL_PIN(L, 4),
		SUNXI_FUNCTION(0x0, "IN"),		
		SUNXI_FUNCTION(0x1, "OUT"),	
		SUNXI_FUNCTION(0x2, "S_JTAG_MS"),
		SUNXI_FUNCTION(0x4, "PWM3-2"),
		SUNXI_FUNCTION_IRQ_BANK(0XE, 0, 4),
		SUNXI_FUNCTION(0xf, "OFF")),	

	SUNXI_PIN(SUNXI_PINCTRL_PIN(L, 5),
		SUNXI_FUNCTION(0x0, "IN"),		
		SUNXI_FUNCTION(0x1, "OUT"),	
		SUNXI_FUNCTION(0x2, "S_JTAG_CK"),
		SUNXI_FUNCTION(0x4, "PWM3-3"),
		SUNXI_FUNCTION(0x5, "I2S0_MCLK"),
		SUNXI_FUNCTION(0x6, "DMIC_DATA3"),
		SUNXI_FUNCTION_IRQ_BANK(0XE, 0, 5),
		SUNXI_FUNCTION(0xf, "OFF")),	

	SUNXI_PIN(SUNXI_PINCTRL_PIN(L, 6),
		SUNXI_FUNCTION(0x0, "IN"),		
		SUNXI_FUNCTION(0x1, "OUT"),	
		SUNXI_FUNCTION(0x2, "S_JTAG_DO"),
		SUNXI_FUNCTION(0x3, "PWM3-4"),
		SUNXI_FUNCTION(0x4, "I2S0_DIN1"),
		SUNXI_FUNCTION(0x5, "I2S0_DOUT0"),
		SUNXI_FUNCTION(0x6, "DMIC_DATA2"),
		SUNXI_FUNCTION_IRQ_BANK(0XE, 0, 6),
		SUNXI_FUNCTION(0xf, "OFF")),	

	SUNXI_PIN(SUNXI_PINCTRL_PIN(L, 7),
		SUNXI_FUNCTION(0x0, "IN"),		
		SUNXI_FUNCTION(0x1, "OUT"),	
		SUNXI_FUNCTION(0x2, "S_JTAG_DI"),
		SUNXI_FUNCTION(0x3, "PWM3-5"),
		SUNXI_FUNCTION(0x4, "I2S0_DOUT1"),
		SUNXI_FUNCTION(0x5, "I2S0_DIN0"),
		SUNXI_FUNCTION(0x6, "DMIC_DATA1"),
		SUNXI_FUNCTION_IRQ_BANK(0XE, 0, 7),
		SUNXI_FUNCTION(0xf, "OFF")),	

	SUNXI_PIN(SUNXI_PINCTRL_PIN(L, 8),
		SUNXI_FUNCTION(0x0, "IN"),		
		SUNXI_FUNCTION(0x1, "OUT"),	
		SUNXI_FUNCTION(0x2, "I2C7_SCL"),
		SUNXI_FUNCTION(0x3, "D_JTAG_MS"),
		SUNXI_FUNCTION(0x4, "R_JTAG_MS"),
		SUNXI_FUNCTION(0x5, "I2S0_BCLK"),
		SUNXI_FUNCTION(0x6, "DMIC_DATA0"),
		SUNXI_FUNCTION_IRQ_BANK(0XE, 0, 8),
		SUNXI_FUNCTION(0xf, "OFF")),	

	SUNXI_PIN(SUNXI_PINCTRL_PIN(L, 9),
		SUNXI_FUNCTION(0x0, "IN"),		
		SUNXI_FUNCTION(0x1, "OUT"),	
		SUNXI_FUNCTION(0x2, "I2C7_SDA"),
		SUNXI_FUNCTION(0x3, "D_JTAG_CK"),
		SUNXI_FUNCTION(0x4, "R_JTAG_CK"),
		SUNXI_FUNCTION(0x5, "PWM2-1"),
		SUNXI_FUNCTION(0x6, "DMIC_CLK"),
		SUNXI_FUNCTION_IRQ_BANK(0XE, 0, 9),
		SUNXI_FUNCTION(0xf, "OFF")),	

	SUNXI_PIN(SUNXI_PINCTRL_PIN(L, 10),
		SUNXI_FUNCTION(0x0, "IN"),		
		SUNXI_FUNCTION(0x1, "OUT"),	
		SUNXI_FUNCTION(0x2, "PWM2-0"),
		SUNXI_FUNCTION(0x3, "D_JTAG_DO"),
		SUNXI_FUNCTION(0x4, "R_JTAG_DO"),
		SUNXI_FUNCTION(0x5, "DMIC"),
		SUNXI_FUNCTION(0x6, "S_SPI0_CS"),
		SUNXI_FUNCTION_IRQ_BANK(0XE, 0, 10),
		SUNXI_FUNCTION(0xf, "OFF")),	

	SUNXI_PIN(SUNXI_PINCTRL_PIN(L, 11),
		SUNXI_FUNCTION(0x0, "IN"),		
		SUNXI_FUNCTION(0x1, "OUT"),	
		SUNXI_FUNCTION(0x2, "S_CIR_IN"),
		SUNXI_FUNCTION(0x3, "D_JTAG_DI"),
		SUNXI_FUNCTION(0x4, "R_JTAG_DI"),
		SUNXI_FUNCTION(0x5, "PWM2-1"),
		SUNXI_FUNCTION(0x6, "S_SPI0_CLK"),
		SUNXI_FUNCTION_IRQ_BANK(0XE, 0, 11),
		SUNXI_FUNCTION(0xf, "OFF")),	

	SUNXI_PIN(SUNXI_PINCTRL_PIN(L, 12),
		SUNXI_FUNCTION(0x0, "IN"),		
		SUNXI_FUNCTION(0x1, "OUT"),	
		SUNXI_FUNCTION(0x2, "I2C8_SCL"),
		SUNXI_FUNCTION(0x3, "PWM3-6"),
		SUNXI_FUNCTION(0x4, "R_UART0_TX"),
		SUNXI_FUNCTION(0x6, "S_SPI0_MOSI"),
		SUNXI_FUNCTION_IRQ_BANK(0XE, 0, 12),
		SUNXI_FUNCTION(0xf, "OFF")),	

	SUNXI_PIN(SUNXI_PINCTRL_PIN(L, 13),
		SUNXI_FUNCTION(0x0, "IN"),		
		SUNXI_FUNCTION(0x1, "OUT"),	
		SUNXI_FUNCTION(0x2, "I2C8_SDA"),
		SUNXI_FUNCTION(0x3, "PWM3-7"),
		SUNXI_FUNCTION(0x4, "R_UART0_RX"),
		SUNXI_FUNCTION(0x6, "S_SPI0_MISO"),
		SUNXI_FUNCTION_IRQ_BANK(0XE, 0, 13),
		SUNXI_FUNCTION(0xf, "OFF")),	

	/* BANK M */
	SUNXI_PIN(SUNXI_PINCTRL_PIN(M, 0),
		SUNXI_FUNCTION(0x0, "IN"),		
		SUNXI_FUNCTION(0x1, "OUT"),	
		SUNXI_FUNCTION(0x2, "UART8_TX"),
		SUNXI_FUNCTION(0x3, "UART8_TX"),
		SUNXI_FUNCTION(0x4, "PWM3-0"),
		SUNXI_FUNCTION_IRQ_BANK(0XE, 1, 0),
		SUNXI_FUNCTION(0xf, "OFF")),	

	SUNXI_PIN(SUNXI_PINCTRL_PIN(M, 1),
		SUNXI_FUNCTION(0x0, "IN"),		
		SUNXI_FUNCTION(0x1, "OUT"),	
		SUNXI_FUNCTION(0x2, "UART9_RX"),
		SUNXI_FUNCTION(0x3, "UART9_RX"),
		SUNXI_FUNCTION(0x4, "PWM3-1"),
		SUNXI_FUNCTION_IRQ_BANK(0XE, 1, 1),
		SUNXI_FUNCTION(0xf, "OFF")),	

	SUNXI_PIN(SUNXI_PINCTRL_PIN(M, 2),
		SUNXI_FUNCTION(0x0, "IN"),		
		SUNXI_FUNCTION(0x1, "OUT"),	
		SUNXI_FUNCTION(0x2, "I2C7_SCL"),
		SUNXI_FUNCTION(0x3, "S_JTAG_MS"),
		SUNXI_FUNCTION(0x4, "PWM3-4"),
		SUNXI_FUNCTION_IRQ_BANK(0XE, 1, 2),
		SUNXI_FUNCTION(0xf, "OFF")),	

	SUNXI_PIN(SUNXI_PINCTRL_PIN(M, 3),
		SUNXI_FUNCTION(0x0, "IN"),		
		SUNXI_FUNCTION(0x1, "OUT"),	
		SUNXI_FUNCTION(0x2, "I2C7_SDA"),
		SUNXI_FUNCTION(0x3, "R_JTAG_CK"),
		SUNXI_FUNCTION(0x4, "PWM3-5"),
		SUNXI_FUNCTION_IRQ_BANK(0XE, 1, 3),
		SUNXI_FUNCTION(0xf, "OFF")),	

	SUNXI_PIN(SUNXI_PINCTRL_PIN(M, 4),
		SUNXI_FUNCTION(0x0, "IN"),		
		SUNXI_FUNCTION(0x1, "OUT"),	
		SUNXI_FUNCTION(0x2, "PWM3-6"),
		SUNXI_FUNCTION(0x3, "R_JTAG_DO"),
		SUNXI_FUNCTION(0x4, "I2C8_SCL"),
		SUNXI_FUNCTION_IRQ_BANK(0XE, 1, 4),
		SUNXI_FUNCTION(0xf, "OFF")),	

	SUNXI_PIN(SUNXI_PINCTRL_PIN(M, 5),
		SUNXI_FUNCTION(0x0, "IN"),		
		SUNXI_FUNCTION(0x1, "OUT"),	
		SUNXI_FUNCTION(0x2, "S_CIR_IN"),
		SUNXI_FUNCTION(0x3, "R_JTAG_DI"),
		SUNXI_FUNCTION(0x4, "I2C8_SDA"),
		SUNXI_FUNCTION(0x5, "PWM3-7"),
		SUNXI_FUNCTION_IRQ_BANK(0XE, 1, 5),
		SUNXI_FUNCTION(0xf, "OFF")),	
};

static const unsigned int sun55iw3_r_irq_bank_map[] = {
	SUNXI_BANK_OFFSET('L', 'L'),
	SUNXI_BANK_OFFSET('M', 'L'),
};

static const unsigned int sun55iw3_r_bank_base[] = {
	SUNXI_BANK_OFFSET('L', 'L'),
	SUNXI_BANK_OFFSET('M', 'L'),
};

const struct sunxi_pinctrl_desc sun55iw3_r_pinctrl_data = {
	.pins = sun55iw3_r_pins,
	.npins = ARRAY_SIZE(sun55iw3_r_pins),
	// .banks = ARRAY_SIZE(sun55iw3_r_bank_base),
	// .bank_base = sun55iw3_r_bank_base,
	.irq_banks = ARRAY_SIZE(sun55iw3_r_irq_bank_map),
	.irq_bank_map = sun55iw3_r_irq_bank_map,
	.pin_base = SUNXI_PIN_BASE('L'),
	.hw_type = SUNXI_PCTL_HW_TYPE_1,
};

// static int sun55iw3_r_pinctrl_probe(struct platform_device *pdev)
// {
// 	return sunxi_bsp_pinctrl_init(pdev, &sun55iw3_r_pinctrl_data);
// }

// static struct of_device_id sun55iw3_r_pinctrl_match[] = {
// 	{ .compatible = "allwinner,sun55iw3-r-pinctrl", },
// 	{}
// };
// MODULE_DEVICE_TABLE(of, sun55iw3_r_pinctrl_match);

// static struct platform_driver sun55iw3_r_pinctrl_driver = {
// 	.probe	= sun55iw3_r_pinctrl_probe,
// 	.driver	= {
// 		.name		= "sun55iw3-r-pinctrl",
// 		.of_match_table	= sun55iw3_r_pinctrl_match,
// 	},
// };

// static int __init sun55iw3_r_pio_init(void)
// {
// 	return platform_driver_register(&sun55iw3_r_pinctrl_driver);
// }
// postcore_initcall(sun55iw3_r_pio_init);

// MODULE_DESCRIPTION("Allwinner sun55iw3 R_PIO pinctrl driver");
// MODULE_LICENSE("GPL");
// MODULE_AUTHOR("<rengaomin@allwinnertech>");
// MODULE_VERSION("1.1.4");
