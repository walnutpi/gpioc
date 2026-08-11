/* Copyright (c) 2025, Canaan Bright Sight Co., Ltd
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 * CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include <stdint.h>
#include <stdio.h>

#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <unistd.h>

#include "hal_utils.h"

/**
 * @brief Map a memory region from /dev/mem
 *
 * @param map Pointer to the utils_memory_map structure
 * @param target The target address to map
 * @return Pointer to the mapped memory region, or NULL on failure
 * @note The mapped memory region is 4096 bytes in size.
 */
volatile uint32_t* utils_map_memory(struct utils_memory_map* map, uint32_t target)
{
    if (map == NULL)
        return NULL;

    if (map->base != NULL) {
        munmap(map->base, 4096);
        map->base = NULL;
    }
    if (map->fd >= 0) {
        close(map->fd);
        map->fd = -1;
    }

    map->fd = open("/dev/mem", O_RDWR | O_SYNC);
    if (map->fd < 0) {
        printf("open /dev/mem failed\n");
        return NULL;
    }

    map->base = mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_SHARED, map->fd, (target & ~(4096 - 1)));
    if (map->base == MAP_FAILED) {
        printf("mmap /dev/mem failed\n");
        close(map->fd);
        map->fd = -1;
        return NULL;
    }

    return (volatile uint32_t*)((uintptr_t)map->base + (target & (4096 - 1)));
}

/**
 * @brief Unmap the memory region and close the file descriptor
 *
 * @param map Pointer to the utils_memory_map structure
 */
void utils_unmap_memory(struct utils_memory_map* map)
{
    if (map->base != NULL) {
        munmap(map->base, 4096);
        map->base = NULL;
    }
    if (map->fd >= 0) {
        close(map->fd);
        map->fd = -1;
    }
}

/**
 * @brief Reboot the CPU by writing to a specific memory address
 *
 * @return 0 on success, -1 on failure
 * @note This function will not return; it will trigger a hardware reboot.
 */
int utils_reboot(void)
{
    volatile uint32_t*      memory_address = NULL;
    struct utils_memory_map map            = {
                   .base = NULL,
                   .fd   = -1,
    };

    if (NULL == (memory_address = utils_map_memory(&map, 0x91102060UL))) {
        printf("utils_map_memory failed\n");
        return -1;
    }
    *memory_address |= (1 << 0) | (1 << 16);

    /* wait for reboot */
    /* the reboot will be triggered by the hardware */
    /* this function will not return */

    while (1) { }

    /* should not reach here */
    printf("utils_cpu_reboot failed\n");
    utils_unmap_memory(&map);

    return 0;
}

int utils_reboot_to_bootloader(void)
{
    volatile uint32_t*      memory_address = NULL;
    struct utils_memory_map map            = {
                   .base = NULL,
                   .fd   = -1,
    };
    if (NULL == (memory_address = utils_map_memory(&map, 0x80230000UL))) {
        printf("utils_map_memory failed\n");
        return -1;
    }
    *memory_address = 0x5aa5a55a;
    utils_unmap_memory(&map);

    return utils_reboot();
}

/*
 * @brief Read the chip ID from a specific memory address
 *
 * @param chip_id Pointer to an array of 32 bytes to store the chip ID
 * @return 0 on success, -1 on failure
 * @note The chip ID is read from the memory address 0x91213000 + 0x300.
 */
int utils_read_chipid(uint8_t chip_id[32])
{
    if (chip_id == NULL) {
        return -1;
    }

    volatile uint32_t*      memory_address = NULL;
    struct utils_memory_map map            = {
                   .base = NULL,
                   .fd   = -1,
    };

    if (NULL == (memory_address = utils_map_memory(&map, 0x91213300UL))) {
        printf("utils_map_memory failed\n");
        return -1;
    }

    volatile uint8_t* mem = (volatile uint8_t*)memory_address;

    for (size_t i = 0; i < 32; i++) {
        chip_id[i] = mem[i];
    }

    utils_unmap_memory(&map);

    return 0;
}
