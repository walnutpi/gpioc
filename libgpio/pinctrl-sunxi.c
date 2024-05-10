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

static const struct sunxi_pinctrl_desc *compatible_to_pinctrl_desc(char *str)
{
    if (strcmp(str, "allwinner,sun50i-h616-pinctrl") == 0)
        return &h616_pinctrl_data;
    else if (strcmp(str, "allwinner,sun50i-h616-r-pinctrl") == 0)
        return &sun50i_h616_r_pinctrl_data;
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
void dtb_get_reg_number(char *path_pinctrl, uint32_t *reg, uint32_t *offset)
{
    char file_path[100];
    sprintf(file_path, "%s/reg", path_pinctrl);

    int fd = open(file_path, O_RDONLY);

    uint8_t tmp[4];
    read(fd, tmp, 4);
    *reg = (tmp[0] << 24) + (tmp[1] << 16) + (tmp[2] << 8) + tmp[3];

    read(fd, tmp, 4);
    *offset = (tmp[0] << 24) + (tmp[1] << 16) + (tmp[2] << 8) + tmp[3];
    close(fd);
}

int sunxi_init()
{
    if (fd_mem > 0) // 代表已经初始化过了
        return true;

    struct dirent *entry;
    DIR *dir = opendir("/proc/device-tree/soc/");
    if (dir == NULL)
    {
        printf("error! can not open dir : /proc/device-tree/soc/\n");
        exit(-1);
    }
    // d1有一些不一样，待后续添加
    // 	pctl->variant = variant;
    // 	if (pctl->variant >= PINCTRL_SUN20I_D1) {
    // 		pctl->bank_mem_size = D1_BANK_MEM_SIZE;
    // 		pctl->pull_regs_offset = D1_PULL_REGS_OFFSET;
    // 		pctl->dlevel_field_width = D1_DLEVEL_FIELD_WIDTH;
    // 	} else {
    // 		pctl->bank_mem_size = BANK_MEM_SIZE;
    // 		pctl->pull_regs_offset = PULL_REGS_OFFSET;
    // 		pctl->dlevel_field_width = DLEVEL_FIELD_WIDTH;
    // 	}

    // 遍历设备树中的pinctrl节点
    char count_scan = 0;
    while ((entry = readdir(dir)) != NULL)
    {
        if (strncmp(entry->d_name, "pinctrl@", 8) == 0)
        {
            char path_pinctrl[100];
            sprintf(path_pinctrl, "/proc/device-tree/soc/%s", entry->d_name);

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
            dtb_get_reg_number(path_pinctrl, &men_reg, &men_offset);

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
                _pins[pinctrl_desc->pins[i].pin.number].mem_bank_base = mmap_gpio + ((pinctrl_desc->pins[i].pin.number) / 32 * BANK_MEM_SIZE);
            }
        }
    }
    closedir(dir);
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
    reg = (uint32_t *)(_pins[gpio_num].mem_bank_base + ((index >> 3) << 2));
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
    reg = (uint32_t *)(_pins[gpio_num].mem_bank_base + ((index >> 3) << 2));

    val = *reg;
    mode = (val >> offset) & 7;

    return mode;
}

const char *sunxi_pin_get_mode_name(int gpio_num)
{
    int mode = sunxi_pin_get_mode(gpio_num);
    if (mode == 7)
        return "OFF";
    struct sunxi_desc_function *functions = _pins[gpio_num].pinctrl_desc->functions;
    for (int i = 0; functions[i].name != NULL; i++)
    {
        if (functions[i].muxval == mode)
            return functions[i].name;
    }
    return "unkonw";
}
const char *sunxi_pin_get_mode_name_by_num(int gpio_num, int mode_num)
{
    if (mode_num == 7)
        return "OFF";
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
    reg = (uint32_t *)(_pins[gpio_num].mem_bank_base + 0x10);

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
    reg = (uint32_t *)(_pins[gpio_num].mem_bank_base + 0x10);

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
    reg = (uint32_t *)(_pins[gpio_num].mem_bank_base + 0x1C + ((index >> 4) << 2));

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
            char path_pinctrl[100];
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
