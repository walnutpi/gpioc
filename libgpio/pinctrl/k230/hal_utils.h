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
#pragma once

#include <stdint.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

/** cpu time *****************************************************************/
#define CPU_TICKS_PER_SECOND (27 * 1000 * 1000)

static __inline __attribute__((__always_inline__)) uint64_t utils_cpu_ticks(void)
{
    uint64_t tick;
    __asm__ __volatile__("rdtime %0" : "=r"(tick));
    return tick;
}

static __inline __attribute__((__always_inline__)) uint64_t utils_cpu_ticks_ms(void)
{
    uint64_t time;
    __asm__ __volatile__("rdtime %0" : "=r"(time));
    return (time / (CPU_TICKS_PER_SECOND / 1000));
}

static __inline __attribute__((__always_inline__)) uint64_t utils_cpu_ticks_us(void)
{
    uint64_t time;
    __asm__ __volatile__("rdtime %0" : "=r"(time));
    return (time / (CPU_TICKS_PER_SECOND / 1000000));
}

static __inline __attribute__((__always_inline__)) uint64_t utils_cpu_ticks_ns(void)
{
    uint64_t time;
    __asm__ __volatile__("rdtime %0" : "=r"(time));
    return (time * 1000000000ULL) / CPU_TICKS_PER_SECOND;
}

/** memory map **************************************************************/
struct utils_memory_map {
    int   fd; /**< file descriptor */
    void* base; /**< base address of mapped memory */
};

volatile uint32_t* utils_map_memory(struct utils_memory_map* map, uint32_t target);

void utils_unmap_memory(struct utils_memory_map* map);

int utils_reboot(void);
int utils_reboot_to_bootloader(void);

int utils_read_chipid(uint8_t chip_id[32]);

#ifdef __cplusplus
}
#endif
