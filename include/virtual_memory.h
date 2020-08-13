#ifndef VIRTUAL_MEMORY_H
#define VIRTUAL_MEMORY_H

// MMU flags
#define MM_TYPE_PAGE 0x3
#define MM_TYPE_BLOCK 0x1
#define MM_ACCESS (0x1 << 10)
#define MT_DEVICE_nGnRnE 0x0
#define MT_NORMAL_NC 0x1
#define MT_DEVICE_nGnRnE_FLAGS 0x00
#define MT_NORMAL_NC_FLAGS 0x44
#define MAIR_VALUE 0x44 //(MT_DEVICE_nGnRnE_FLAGS << (8 * MT_DEVICE_nGnRnE)) | (MT_NORMAL_NC_FLAGS << (8 * MT_NORMAL_NC))

#define MMU_SECTION_FLAGS (MM_TYPE_BLOCK | (MT_NORMAL_NC << 2) | MM_ACCESS)
#define MMU_DEVICE_FLAGS (MM_TYPE_BLOCK | (MT_DEVICE_nGnRnE << 2) | MM_ACCESS)

#define TCR_T0SZ (64 - 48) // Use last 16 bits for ttbr0 vs ttbr1
#define TCR_T1SZ ((64 - 48) << 16)
#define TCR_TG0_4K (0 << 14) // smallest granule: 0 = 4kb
// #define TCR_TG1_4K (2 << 30)
#define TCR_TG1_4K (0 << 30)
#define TCR_VALUE (TCR_T0SZ | TCR_T1SZ | TCR_TG0_4K | TCR_TG1_4K)

#ifndef ASSEMBLER

#include <stdint.h>
extern uint64_t test_el1_translation(uint64_t vaddr);

void init_page_tables(void);
void print_page_tables(void);

#endif // ASSEMBLER
#endif // VIRTUAL_MEMORY_H