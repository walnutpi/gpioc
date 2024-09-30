#ifndef _PINCTRL_SUNXI_H
#define _PINCTRL_SUNXI_H


#include <stdint.h>
#include <stdbool.h>
// #include "kernel.h"
// #include "errno-base.h"
// #include <linux/kernel.h>
// #include <linux/spinlock.h>

#define SUNXI_BANK_OFFSET(bank, bankbase)	((bank) - (bankbase))
#define SUNXI_PIN_BASE(bank)			(SUNXI_BANK_OFFSET(bank, 'A') * 32)

#define PA_BASE			SUNXI_PIN_BASE('A')
#define PB_BASE			SUNXI_PIN_BASE('B')
#define PC_BASE			SUNXI_PIN_BASE('C')
#define PD_BASE			SUNXI_PIN_BASE('D')
#define PE_BASE			SUNXI_PIN_BASE('E')
#define PF_BASE			SUNXI_PIN_BASE('F')
#define PG_BASE			SUNXI_PIN_BASE('G')
#define PH_BASE			SUNXI_PIN_BASE('H')
#define PI_BASE			SUNXI_PIN_BASE('I')
#define PJ_BASE			SUNXI_PIN_BASE('J')
#define PK_BASE			SUNXI_PIN_BASE('K')
#define PL_BASE			SUNXI_PIN_BASE('L')
#define PM_BASE			SUNXI_PIN_BASE('M')
#define PN_BASE			SUNXI_PIN_BASE('N')


#define PINCTRL_PIN(a, b) { .number = a, .name = b }
#define SUNXI_PINCTRL_PIN(bank, pin)		\
	PINCTRL_PIN(P ## bank ## _BASE + (pin), "P" #bank #pin)

#define SUNXI_PIN_NAME_MAX_LEN	5

#define BANK_MEM_SIZE		0x24
#define MUX_REGS_OFFSET		0x0
#define MUX_FIELD_WIDTH		4
#define DATA_REGS_OFFSET	0x10
#define DATA_FIELD_WIDTH	1
#define DLEVEL_REGS_OFFSET	0x14
#define DLEVEL_FIELD_WIDTH	2
#define PULL_REGS_OFFSET	0x1c
#define PULL_FIELD_WIDTH	2

#define D1_BANK_MEM_SIZE	0x30
#define D1_DLEVEL_FIELD_WIDTH	4
#define D1_PULL_REGS_OFFSET	0x24

#define PINS_PER_BANK		32

#define IRQ_PER_BANK		32

#define IRQ_CFG_REG		0x200
#define IRQ_CFG_IRQ_PER_REG		8
#define IRQ_CFG_IRQ_BITS		4
#define IRQ_CFG_IRQ_MASK		((1 << IRQ_CFG_IRQ_BITS) - 1)
#define IRQ_CTRL_REG		0x210
#define IRQ_CTRL_IRQ_PER_REG		32
#define IRQ_CTRL_IRQ_BITS		1
#define IRQ_CTRL_IRQ_MASK		((1 << IRQ_CTRL_IRQ_BITS) - 1)
#define IRQ_STATUS_REG		0x214
#define IRQ_STATUS_IRQ_PER_REG		32
#define IRQ_STATUS_IRQ_BITS		1
#define IRQ_STATUS_IRQ_MASK		((1 << IRQ_STATUS_IRQ_BITS) - 1)

#define IRQ_DEBOUNCE_REG	0x218

#define IRQ_MEM_SIZE		0x20

#define IRQ_EDGE_RISING		0x00
#define IRQ_EDGE_FALLING	0x01
#define IRQ_LEVEL_HIGH		0x02
#define IRQ_LEVEL_LOW		0x03
#define IRQ_EDGE_BOTH		0x04

#define GRP_CFG_REG		0x300

#define IO_BIAS_MASK		GENMASK(3, 0)

#define SUN4I_FUNC_INPUT	0
#define SUN4I_FUNC_IRQ		6

#define PINCTRL_SUN5I_A10S	BIT(1)
#define PINCTRL_SUN5I_A13	BIT(2)
#define PINCTRL_SUN5I_GR8	BIT(3)
#define PINCTRL_SUN6I_A31	BIT(4)
#define PINCTRL_SUN6I_A31S	BIT(5)
#define PINCTRL_SUN4I_A10	BIT(6)
#define PINCTRL_SUN7I_A20	BIT(7)
#define PINCTRL_SUN8I_R40	BIT(8)
#define PINCTRL_SUN8I_V3	BIT(9)
#define PINCTRL_SUN8I_V3S	BIT(10)
/* Variants below here have an updated register layout. */
#define PINCTRL_SUN20I_D1	BIT(11)

#define PIO_POW_MOD_SEL_REG	0x340
#define PIO_POW_MOD_CTL_REG	0x344

enum sunxi_desc_bias_voltage {
	BIAS_VOLTAGE_NONE,
	/*
	 * Bias voltage configuration is done through
	 * Pn_GRP_CONFIG registers, as seen on A80 SoC.
	 */
	BIAS_VOLTAGE_GRP_CONFIG,
	/*
	 * Bias voltage is set through PIO_POW_MOD_SEL_REG
	 * register, as seen on H6 SoC, for example.
	 */
	BIAS_VOLTAGE_PIO_POW_MODE_SEL,
	/*
	 * Bias voltage is set through PIO_POW_MOD_SEL_REG
	 * and PIO_POW_MOD_CTL_REG register, as seen on
	 * A100 and D1 SoC, for example.
	 */
	BIAS_VOLTAGE_PIO_POW_MODE_CTL,
};
enum sunxi_pinctrl_hw_type {
	SUNXI_PCTL_HW_TYPE_0,  /* Older chips */
	SUNXI_PCTL_HW_TYPE_1,  /* Newer chips: sun8iw20, sun20iw1, sun50iw12 */
	SUNXI_PCTL_HW_TYPE_2,  /* Newer chips: sun60iw1 */
	SUNXI_PCTL_HW_TYPE_3,  /* Newer chips: sun55iw3 */
	SUNXI_PCTL_HW_TYPE_4,  /* Newer chips: sun60iw2 */
	SUNXI_PCTL_HW_TYPE_5,  /* Support self-adaption */
	/* Add new types here ... */
	SUNXI_PCTL_HW_TYPE_CNT,
};

/* Reference <Port_Controller_Spec: Port Register List> for the information below: */
struct sunxi_pinctrl_hw_info {
	uint8_t initial_bank_offset;	/* First bank offset to pin base */
	uint8_t mux_regs_offset;	/* Configure Register's offset */
	uint8_t data_regs_offset;	/* Data Register's offset */
	uint8_t dlevel_regs_offset;	/* Multi Driving Register's offset */
	uint8_t bank_mem_size;  	/* Size of the basic registers (including CFG/DAT/DRV/PUL) of any bank  */
	uint8_t pull_regs_offset;	/* Pull Register's offset */
	uint8_t dlevel_pins_per_reg; /* How many pins does a 'Multi-Driving Register' contain? */
	uint8_t dlevel_pins_bits;	/* How many bits does a 'Multi-Driving Register' use for a pin? */
	uint8_t dlevel_pins_mask;	/* Bit mask for 'dlevel_pins_bits' */
	uint8_t irq_mux_val;		/* Mux value for IRQ function */
	uint32_t irq_cfg_reg;
	uint32_t irq_ctrl_reg;
	uint32_t irq_status_reg;
	uint32_t irq_debounce_reg;
	uint32_t irq_mem_size;
	uint32_t irq_mem_base;
	uint32_t irq_mem_used;
	uint32_t power_mode_sel_reg;
	uint32_t mode_sel_vccio_bit;
	uint32_t power_mode_ctrl_reg;
	uint32_t mode_ctrl_vccio_bit;
	uint32_t power_mode_val_reg;  /* GPIO_POW_VAL: the register read the voltage withstand */
	uint32_t mode_val_vccio_bit;
	uint32_t pio_pow_ctrl_reg;
	bool power_mode_reverse;  /* true: GPIO_POW_VAL and GPIO_POW_MID_SEL bit reverse, A523 SOC, for example */
	bool power_mode_detect;  /* true: Config voltage withstand by reading power_mode_val_reg */
};


struct sunxi_desc_function {
	unsigned long	variant;
	const char	*name;
	uint8_t		muxval;
	uint8_t		irqbank;
	uint8_t		irqnum;
};
/**
 * struct pinctrl_pin_desc - boards/machines provide information on their
 * pins, pads or other muxable units in this struct
 * @number: unique pin number from the global pin number space
 * @name: a name for this pin
 * @drv_data: driver-defined per-pin data. pinctrl core does not touch this
 */
struct pinctrl_pin_desc {
	unsigned number;
	const char *name;
	void *drv_data;
};

struct sunxi_desc_pin {
	struct pinctrl_pin_desc		pin;
	unsigned long			variant;
	struct sunxi_desc_function	*functions;
};

struct sunxi_pinctrl_desc {
	const struct sunxi_desc_pin	*pins;
	int				npins;
	unsigned			pin_base;
	unsigned			irq_banks;
	const unsigned int		*irq_bank_map;
	bool				irq_read_needs_mux;
	bool				disable_strict_mode;
	enum sunxi_desc_bias_voltage	io_bias_cfg_variant;
	enum sunxi_pinctrl_hw_type	hw_type;
};

struct sunxi_pinctrl_function {
	const char	*name;
	const char	**groups;
	unsigned	ngroups;
};

struct sunxi_pinctrl_group {
	const char	*name;
	unsigned	pin;
};

struct sunxi_pinctrl_regulator {
	struct regulator	*regulator;
	// refcount_t		refcount;
};

#define SUNXI_PIN(_pin, ...)					\
	{							\
		.pin = _pin,					\
		.functions = (struct sunxi_desc_function[]){	\
			__VA_ARGS__, { } },			\
	}

#define SUNXI_PIN_VARIANT(_pin, _variant, ...)			\
	{							\
		.pin = _pin,					\
		.variant = _variant,				\
		.functions = (struct sunxi_desc_function[]){	\
			__VA_ARGS__, { } },			\
	}

#define SUNXI_FUNCTION(_val, _name)				\
	{							\
		.name = _name,					\
		.muxval = _val,					\
	}

#define SUNXI_FUNCTION_VARIANT(_val, _name, _variant)		\
	{							\
		.name = _name,					\
		.muxval = _val,					\
		.variant = _variant,				\
	}

#define SUNXI_FUNCTION_IRQ(_val, _irq)				\
	{							\
		.name = "irq",					\
		.muxval = _val,					\
		.irqnum = _irq,					\
	}

#define SUNXI_FUNCTION_IRQ_BANK(_val, _bank, _irq)		\
	{							\
		.name = "irq",					\
		.muxval = _val,					\
		.irqbank = _bank,				\
		.irqnum = _irq,					\
	}

static inline uint32_t sunxi_irq_hw_bank_num(const struct sunxi_pinctrl_desc *desc, uint8_t bank)
{
	if (!desc->irq_bank_map)
		return bank;
	else
		return desc->irq_bank_map[bank];
}

static inline uint32_t sunxi_irq_cfg_reg(const struct sunxi_pinctrl_desc *desc,
				    uint16_t irq)
{
	uint8_t bank = irq / IRQ_PER_BANK;
	uint8_t reg = (irq % IRQ_PER_BANK) / IRQ_CFG_IRQ_PER_REG * 0x04;

	return IRQ_CFG_REG +
	       sunxi_irq_hw_bank_num(desc, bank) * IRQ_MEM_SIZE + reg;
}

static inline uint32_t sunxi_irq_cfg_offset(uint16_t irq)
{
	uint32_t irq_num = irq % IRQ_CFG_IRQ_PER_REG;
	return irq_num * IRQ_CFG_IRQ_BITS;
}

static inline uint32_t sunxi_irq_ctrl_reg_from_bank(const struct sunxi_pinctrl_desc *desc, uint8_t bank)
{
	return IRQ_CTRL_REG + sunxi_irq_hw_bank_num(desc, bank) * IRQ_MEM_SIZE;
}

static inline uint32_t sunxi_irq_ctrl_reg(const struct sunxi_pinctrl_desc *desc,
				     uint16_t irq)
{
	uint8_t bank = irq / IRQ_PER_BANK;

	return sunxi_irq_ctrl_reg_from_bank(desc, bank);
}

static inline uint32_t sunxi_irq_ctrl_offset(uint16_t irq)
{
	uint32_t irq_num = irq % IRQ_CTRL_IRQ_PER_REG;
	return irq_num * IRQ_CTRL_IRQ_BITS;
}

static inline uint32_t sunxi_irq_debounce_reg_from_bank(const struct sunxi_pinctrl_desc *desc, uint8_t bank)
{
	return IRQ_DEBOUNCE_REG +
	       sunxi_irq_hw_bank_num(desc, bank) * IRQ_MEM_SIZE;
}

static inline uint32_t sunxi_irq_status_reg_from_bank(const struct sunxi_pinctrl_desc *desc, uint8_t bank)
{
	return IRQ_STATUS_REG +
	       sunxi_irq_hw_bank_num(desc, bank) * IRQ_MEM_SIZE;
}

static inline uint32_t sunxi_irq_status_reg(const struct sunxi_pinctrl_desc *desc,
				       uint16_t irq)
{
	uint8_t bank = irq / IRQ_PER_BANK;

	return sunxi_irq_status_reg_from_bank(desc, bank);
}

static inline uint32_t sunxi_irq_status_offset(uint16_t irq)
{
	uint32_t irq_num = irq % IRQ_STATUS_IRQ_PER_REG;
	return irq_num * IRQ_STATUS_IRQ_BITS;
}

static inline uint32_t sunxi_grp_config_reg(uint16_t pin)
{
	uint8_t bank = pin / PINS_PER_BANK;

	return GRP_CFG_REG + bank * 0x4;
}

int sunxi_pinctrl_init_with_variant(
				    const struct sunxi_pinctrl_desc *desc,
				    unsigned long variant);

#define sunxi_pinctrl_init(_dev, _desc) \
	sunxi_pinctrl_init_with_variant(_dev, _desc, 0)

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))


extern const struct sunxi_pinctrl_desc h616_pinctrl_data;
extern const struct sunxi_pinctrl_desc sun50i_h616_r_pinctrl_data;
extern const struct sunxi_pinctrl_desc sun55iw3_pinctrl_data;
extern const struct sunxi_pinctrl_desc sun55iw3_r_pinctrl_data;



#define GPIO_BIT(x)                        (1UL << (x))

struct pins
{
    const struct sunxi_desc_pin *pinctrl_desc; //单个引脚的描述
    uint8_t *mem_bank_base; //指向mmap映射后的bank基地址
	struct sunxi_pinctrl_hw_info *reg_info; //记录各寄存器的偏移地址
};
extern struct pins _pins[448];
int sunxi_init(void);

extern void sunxi_pin_set_mode (int gpio_num, int mode);
extern int sunxi_pin_get_mode (int gpio_num);
extern const char *sunxi_pin_get_mode_name(int gpio_num);
extern const char *sunxi_pin_get_mode_name_by_num(int gpio_num, int mode_num);

extern int sunxi_gpio_read(int gpio_num);
extern void sunxi_gpio_write(int gpio_num, int value);
extern void sunxi_gpio_set_PullUpDn (int gpio_num, int pud);

extern void sunxi_print_who_has_function(char *name_buf, int len);
#endif