#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <dirent.h>

#include "pinctrl.h"
#include "pinctrl-sunxi.h"

static int fd_mem = 0;
struct pins _pins[448];

struct sunxi_pinctrl_hw_info sunxi_pinctrl_hw_info[SUNXI_PCTL_HW_TYPE_CNT] = {
    {
        .initial_bank_offset = 0x0,
        .mux_regs_offset = 0x0,
        .data_regs_offset = 0x10,
        .dlevel_regs_offset = 0x14,
        .bank_mem_size = 0x24,
        .pull_regs_offset = 0x1c,
        .dlevel_pins_per_reg = 16,
        .dlevel_pins_bits = 2,
        .dlevel_pins_mask = 0x3,
        .irq_mux_val = 0x6,
        .irq_cfg_reg = 0x200,
        .irq_ctrl_reg = 0x210,
        .irq_status_reg = 0x214,
        .irq_debounce_reg = 0x218,
        .irq_mem_base = 0x200,
        .irq_mem_size = 0x20,
        .irq_mem_used = 0x20,
        .power_mode_sel_reg = 0x340,
        .power_mode_ctrl_reg = 0x344,
        .power_mode_val_reg = 0x348,
        .pio_pow_ctrl_reg = 0x350,
        .power_mode_reverse = false,
    },
    {
        .initial_bank_offset = 0x0,
        .mux_regs_offset = 0x0,
        .data_regs_offset = 0x10,
        .dlevel_regs_offset = 0x14,
        .bank_mem_size = 0x30,
        .pull_regs_offset = 0x24,
        .dlevel_pins_per_reg = 8,
        .dlevel_pins_bits = 4,
        .dlevel_pins_mask = 0xF,
        .irq_mux_val = 0xE,
        .irq_cfg_reg = 0x200,
        .irq_ctrl_reg = 0x210,
        .irq_status_reg = 0x214,
        .irq_debounce_reg = 0x218,
        .irq_mem_base = 0x200,
        .irq_mem_size = 0x20,
        .irq_mem_used = 0x20,
        .power_mode_sel_reg = 0x340,
        .power_mode_ctrl_reg = 0x344,
        .power_mode_val_reg = 0x348,
        .pio_pow_ctrl_reg = 0x350,
        .power_mode_reverse = false,
    },
    {

        .initial_bank_offset = 0x80,
        .mux_regs_offset = 0x00,
        .data_regs_offset = 0x10,
        .dlevel_regs_offset = 0x20,
        .bank_mem_size = 0x80,
        .pull_regs_offset = 0x30,
        .dlevel_pins_per_reg = 8,
        .dlevel_pins_bits = 4,
        .dlevel_pins_mask = 0xF,
        .irq_mux_val = 0xE,
        .irq_cfg_reg = 0xc0,
        .irq_ctrl_reg = 0xd0,
        .irq_status_reg = 0xd4,
        .irq_debounce_reg = 0xd8,
        .irq_mem_base = 0xc0,
        .irq_mem_size = 0x80,
        .irq_mem_used = 0x20,
        .power_mode_sel_reg = 0x340,
        .power_mode_ctrl_reg = 0x344,
        .power_mode_val_reg = 0x348,
        .pio_pow_ctrl_reg = 0x350,
        .power_mode_reverse = false,
    },
    {
        .initial_bank_offset = 0x0,
        .mux_regs_offset = 0x0,
        .data_regs_offset = 0x10,
        .dlevel_regs_offset = 0x14,
        .bank_mem_size = 0x30,
        .pull_regs_offset = 0x24,
        .dlevel_pins_per_reg = 8,
        .dlevel_pins_bits = 4,
        .dlevel_pins_mask = 0xF,
        .irq_mux_val = 0xE,
        .irq_cfg_reg = 0x200,
        .irq_ctrl_reg = 0x210,
        .irq_status_reg = 0x214,
        .irq_debounce_reg = 0x218,
        .irq_mem_base = 0x200,
        .irq_mem_size = 0x20,
        .irq_mem_used = 0x20,
        .power_mode_sel_reg = 0x380,
        .mode_sel_vccio_bit = 12,
        .power_mode_ctrl_reg = 0x384,
        .mode_ctrl_vccio_bit = 12,
        .power_mode_val_reg = 0x388,
        .mode_val_vccio_bit = 16,
        .pio_pow_ctrl_reg = 0x390,
        .power_mode_reverse = true,
        .power_mode_detect = true,
    },
    {
        .initial_bank_offset = 0x80,
        .mux_regs_offset = 0x0,
        .data_regs_offset = 0x10,
        .dlevel_regs_offset = 0x20,
        .bank_mem_size = 0x80,
        .pull_regs_offset = 0x30,
        .dlevel_pins_per_reg = 8,
        .dlevel_pins_bits = 4,
        .dlevel_pins_mask = 0xF,
        .irq_mux_val = 0xE,
        .irq_cfg_reg = 0xC0,
        .irq_ctrl_reg = 0xD0,
        .irq_status_reg = 0xD4,
        .irq_debounce_reg = 0xD8,
        .irq_mem_base = 0xC0,
        .irq_mem_size = 0x80,
        .irq_mem_used = 0x20,
        .power_mode_sel_reg = 0x40,
        .power_mode_ctrl_reg = 0x48,
        .power_mode_val_reg = 0x48,
        .pio_pow_ctrl_reg = 0x70,
        .power_mode_reverse = false,
    },
    {
        .initial_bank_offset = 0x0,
        .mux_regs_offset = 0x0,
        .data_regs_offset = 0x10,
        .dlevel_regs_offset = 0x14,
        .bank_mem_size = 0x24,
        .pull_regs_offset = 0x1c,
        .dlevel_pins_per_reg = 16,
        .dlevel_pins_bits = 2,
        .dlevel_pins_mask = 0x3,
        .irq_mux_val = 0x6,
        .irq_cfg_reg = 0x200,
        .irq_ctrl_reg = 0x210,
        .irq_status_reg = 0x214,
        .irq_debounce_reg = 0x218,
        .irq_mem_base = 0x200,
        .irq_mem_size = 0x20,
        .irq_mem_used = 0x20,
        .power_mode_sel_reg = 0x340,
        .power_mode_ctrl_reg = 0x344,
        .power_mode_val_reg = 0x348,
        .pio_pow_ctrl_reg = 0x350,
        .power_mode_reverse = false,
        .power_mode_detect = true,
    },
};

static const struct sunxi_pinctrl_desc *compatible_to_pinctrl_desc(char *str)
{
    if (strcmp(str, "allwinner,sun50i-h616-pinctrl") == 0)
        return &h616_pinctrl_data;
    else if (strcmp(str, "allwinner,sun50i-h616-r-pinctrl") == 0)
        return &sun50i_h616_r_pinctrl_data;
    else if (strcmp(str, "allwinner,sun55iw3-pinctrl") == 0)
        return &sun55iw3_pinctrl_data;
    else if (strcmp(str, "allwinner,sun55iw3-r-pinctrl") == 0)
        return &sun55iw3_r_pinctrl_data;
    else
    {
        printf("can not support pinctrl compatible : %s\n", str);
        return NULL;
    }
}
void dtb_get_compatible_str(char *path_pinctrl, char *buf)
{
    char file_path[100];
    sprintf(file_path, "%s/compatible", path_pinctrl);

    FILE *file = fopen(file_path, "r");
    if (file != NULL)
    {
        fgets(buf, 50, file);
        fclose(file);
    }
}
int dtb_get_address_cells(char *path_node)
{
    char file_path[100];
    sprintf(file_path, "%s/#address-cells", path_node);

    int fd = open(file_path, O_RDONLY);

    uint8_t tmp[4];
    read(fd, tmp, 4);
    return (tmp[0] << 24) + (tmp[1] << 16) + (tmp[2] << 8) + tmp[3];
}
int dtb_get_size_cells(char *path_node)
{
    char file_path[100];
    sprintf(file_path, "%s/#size-cells", path_node);

    int fd = open(file_path, O_RDONLY);

    uint8_t tmp[4];
    read(fd, tmp, 4);
    return (tmp[0] << 24) + (tmp[1] << 16) + (tmp[2] << 8) + tmp[3];
}
void dtb_get_reg_number(char *path_node, int address_cells, int size_cells, uint32_t *reg, uint32_t *offset)
{
    char file_path[100];
    sprintf(file_path, "%s/reg", path_node);

    int fd = open(file_path, O_RDONLY);

    uint8_t tmp[4];
    if (address_cells == 2)
        read(fd, tmp, 4);
    read(fd, tmp, 4);
    *reg = (tmp[0] << 24) + (tmp[1] << 16) + (tmp[2] << 8) + tmp[3];

    if (size_cells == 2)
        read(fd, tmp, 4);
    read(fd, tmp, 4);
    *offset = (tmp[0] << 24) + (tmp[1] << 16) + (tmp[2] << 8) + tmp[3];
    close(fd);
}

int sunxi_init()
{
    if (fd_mem > 0) // 代表已经初始化过了
        return true;

    struct dirent *entry;
    DIR *dir_dtree = opendir("/proc/device-tree/");
    DIR *dir_soc;
    if (dir_dtree == NULL)
    {
        printf("无法打开目录\n");
        return 1;
    }
    char path_soc[300];
    while ((entry = readdir(dir_dtree)) != NULL)
    {
        if (strncmp(entry->d_name, "soc", 3) == 0)
        {
            sprintf(path_soc, "/proc/device-tree/%s", entry->d_name);
            dir_soc = opendir(path_soc);
        }
    }
    closedir(dir_dtree);

    if (dir_soc == NULL)
    {
        printf("error! can not open dir : /proc/device-tree/soc/\n");
        exit(-1);
    }

    // 遍历设备树中的pinctrl节点
    char count_scan = 0;
    while ((entry = readdir(dir_soc)) != NULL)
    {
        if (strncmp(entry->d_name, "pinctrl@", 8) == 0)
        {
            char path_pinctrl[600];
            sprintf(path_pinctrl, "%s/%s", path_soc, entry->d_name);

            // 读取compatible值
            char buf[50] = "";
            dtb_get_compatible_str(path_pinctrl, buf);

            // 获取与compatible对应的引脚desc结构体
            const struct sunxi_pinctrl_desc *pinctrl_desc = compatible_to_pinctrl_desc(buf);

            if (pinctrl_desc == NULL)
                continue;
            count_scan++;
            // 读取reg属性所描述的地址
            uint32_t men_reg;
            uint32_t men_offset;

            int address_cells = dtb_get_address_cells(path_soc);
            int size_cells = dtb_get_size_cells(path_soc);
            dtb_get_reg_number(path_pinctrl, address_cells, size_cells,&men_reg, &men_offset);
            fd_mem = open("/dev/mem", O_RDWR);

            if (fd_mem < 0)
            {
                printf("Failed to open /dev/mem\r\n");
                printf("\n\n\tplease run as root/sudo\n\n");
                exit(-1);
            }

            uint8_t *mmap_gpio = (uint8_t *)mmap(0, men_offset, PROT_READ | PROT_WRITE, MAP_SHARED, fd_mem, men_reg);
            for (int i = 0; i < pinctrl_desc->npins; i++)
            {
                _pins[pinctrl_desc->pins[i].pin.number].pinctrl_desc = &(pinctrl_desc->pins[i]);
                _pins[pinctrl_desc->pins[i].pin.number].mem_bank_base = mmap_gpio + ((pinctrl_desc->pins[i].pin.number) / 32 * sunxi_pinctrl_hw_info[pinctrl_desc->hw_type].bank_mem_size);
                _pins[pinctrl_desc->pins[i].pin.number].reg_info = &sunxi_pinctrl_hw_info[pinctrl_desc->hw_type];
            }
        }
    }
    closedir(dir_soc);
    if (count_scan == 0)
        return false;

    return true;
}

void sunxi_pin_set_mode(int gpio_num, int mode)
{
    sunxi_init();
    unsigned int val = 0;
    unsigned int bank = gpio_num >> 5;
    unsigned int index = gpio_num - (bank << 5);
    int offset = ((index - ((index >> 3) << 3)) << 2);

    uint32_t *reg;
    reg = (uint32_t *)(_pins[gpio_num].mem_bank_base + _pins[gpio_num].reg_info->mux_regs_offset + ((index >> 3) << 2));
    val = *reg;

    switch (mode)
    {
    case INPUT:
        mode = 0;
        break;
    case OUTPUT:
        mode = 1;
        break;

    default:
        break;
    }

    val &= ~(7 << offset);
    val |= (mode << offset);
    *reg = val;
}
int sunxi_pin_get_mode(int gpio_num)
{
    sunxi_init();
    unsigned int val = 0;
    unsigned int bank = gpio_num >> 5;
    unsigned int index = gpio_num - (bank << 5);
    unsigned char mode = -1;

    int offset = ((index - ((index >> 3) << 3)) << 2);
    uint32_t *reg;
    if (_pins[gpio_num].mem_bank_base == NULL)
    {
        return 0xff;
    }
    reg = (uint32_t *)(_pins[gpio_num].mem_bank_base + _pins[gpio_num].reg_info->mux_regs_offset +((index >> 3) << 2));

    val = *reg;
    mode = (val >> offset) & 0xf;
    return mode;
}

const char *sunxi_pin_get_mode_name(int gpio_num)
{
    int mode = sunxi_pin_get_mode(gpio_num);

    if (_pins[gpio_num].pinctrl_desc == NULL)
    {
        return "Pin number not recorded";
    }
    struct sunxi_desc_function *functions = _pins[gpio_num].pinctrl_desc->functions;

    for (int i = 0; functions[i].name != NULL; i++)
    {
        if (functions[i].muxval == mode)
            return functions[i].name;
    }
    return "off";
}
const char *sunxi_pin_get_mode_name_by_num(int gpio_num, int mode_num)
{
    if (_pins[gpio_num].pinctrl_desc == NULL)
    {
        return "Pin number not recorded";
    }
    struct sunxi_desc_function *functions = _pins[gpio_num].pinctrl_desc->functions;
    for (int i = 0; functions[i].name != NULL; i++)
    {
        if (functions[i].muxval == mode_num)
            return functions[i].name;
    }
    return NULL;
}

int sunxi_gpio_read(int gpio_num)
{
    sunxi_init();
    int bank = gpio_num >> 5;
    int index = gpio_num - (bank << 5);
    uint32_t val;

    uint32_t *reg;
    reg = (uint32_t *)(_pins[gpio_num].mem_bank_base + _pins[gpio_num].reg_info->data_regs_offset);

    val = *reg;

    return (val & GPIO_BIT(index)) ? 1 : 0;
}
void sunxi_gpio_write(int gpio_num, int value)
{
    sunxi_init();
    unsigned int bank = gpio_num >> 5;
    unsigned int index = gpio_num - (bank << 5);
    uint32_t val;

    uint32_t *reg;
    reg = (uint32_t *)(_pins[gpio_num].mem_bank_base + _pins[gpio_num].reg_info->data_regs_offset);

    val = *reg;

    if (0 == value)
    {
        val &= ~(1 << index);
        *reg = val;
    }
    else
    {
        val |= (1 << index);
        *reg = val;
    }
}
void sunxi_gpio_set_PullUpDn(int gpio_num, int pud)
{
    sunxi_init();
    uint32_t val;
    unsigned int bank = gpio_num >> 5;
    unsigned int index = gpio_num - (bank << 5);
    unsigned int phyaddr = 0;
    unsigned int bit_value = -1, bit_enable = 0;
    unsigned int offset;

    unsigned int pullOffset = 0x1C;
#define H616_PULL_OFF 0
#define H616_PULL_UP 1
#define H616_PULL_DOWN 2
    switch (pud)
    {
    case PULL_OFF:
        bit_value = H616_PULL_OFF;
        break;
    case PULL_UP:
        sunxi_pin_set_mode(gpio_num, 0);
        bit_value = H616_PULL_UP;
        break;
    case PULL_DOWN:
        sunxi_pin_set_mode(gpio_num, 0);
        bit_value = H616_PULL_DOWN;
        break;
    default:
        printf("Unknow pull mode\n");
        return;
    }
    offset = ((index - ((index >> 4) << 4)) << 1);
    pullOffset = 0x1C;
    uint32_t *reg;
    reg = (uint32_t *)(_pins[gpio_num].mem_bank_base + _pins[gpio_num].reg_info->pull_regs_offset + ((index >> 4) << 2));

    val = *reg;

    /* clear bit */
    val &= ~(3 << offset);

    /* bit write enable*/
    val |= bit_enable;

    /* set bit */
    val |= (bit_value & 3) << offset;

    *reg = val;
}

void sunxi_print_who_has_function(char *name_buf, int len)
{
    printf("name_buf=%s\n", name_buf);
    struct dirent *entry;
    DIR *dir = opendir("/proc/device-tree/soc/");
    if (dir == NULL)
    {
        printf("error! can not open dir : /proc/device-tree/soc/\n");
        exit(-1);
    }

    // 遍历设备树中的pinctrl节点
    char count_scan = 0;
    while ((entry = readdir(dir)) != NULL)
    {
        if (strncmp(entry->d_name, "pinctrl@", 8) == 0)
        {
            char path_pinctrl[300];
            sprintf(path_pinctrl, "/proc/device-tree/soc/%s", entry->d_name);

            // 读取compatible值
            char buf[50] = "";
            dtb_get_compatible_str(path_pinctrl, buf);

            // 获取与compatible对应的引脚desc结构体
            const struct sunxi_pinctrl_desc *pinctrl_desc = compatible_to_pinctrl_desc(buf);

            for (int i = 0; i < pinctrl_desc->npins; i++)
            {
                struct sunxi_desc_function *functions = pinctrl_desc->pins[i].functions;
                for (int j = 0; functions[j].name; j++)
                {
                    if (strncmp(functions[j].name, name_buf, len) == 0)
                    {
                        printf("%s mode%d %s\n", pinctrl_desc->pins[i].pin.name, functions[j].muxval, functions[j].name);
                    }
                }
            }
        }
    }
    closedir(dir);
}
