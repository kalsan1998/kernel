#ifndef MM_H
#define MM_H

#define PAGE_SIZE 0x1000      //4KB
#define SECTION_SIZE 0x200000 // 2MB

#define VA_START 0xffff000000000000    // TODO: change to 0xffff 00000... when implementing kernel vs user space
#define DEVICE_MEMORY_START 0xfe000000 // 4GB
// #define KERNEL_MEMORY_START 0x00400000 // 4MB
// #define KERNEL_MEMORY_START 0x1000
#define KERNEL_MEMORY_START 0x0000
#define PHYSICAL_MEM_SIZE 0x100000000 // 4GB

#ifndef ASSEMBLER
#include <stdint.h>

extern void memzero(uint64_t start, uint64_t size);

#endif

#endif // MM_H