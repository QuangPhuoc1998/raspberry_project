#ifndef BSP_H
#define BSP_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

#define BCM2711_PERI_BASE        0xFE000000
#define GPIO_BASE                (BCM2711_PERI_BASE + 0x200000) /* GPIO controller */
#define PAGE_SIZE (4*1024)
#define BLOCK_SIZE (4*1024)

#endif // BSP_H
