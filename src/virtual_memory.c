#include "virtual_memory.h"

#include <stdint.h>

#include "mm.h"
#include "stdio.h"
#include "utils.h"

#define PAGE_TABLE_ENTRY_COUNT 512 // 2 ^ 9

#define PGD_COUNT 1
#define PUD_COUNT 1
#define PMD_COUNT 4
#define PMD_ADDRESS_RANGE 0x40000000

// don't need PTE for now, using section mapping
#define PGD_START_OFFSET 0
#define PUD_START_OFFSET (PGD_START_OFFSET + (PGD_COUNT * PAGE_SIZE))
#define PMD_START_OFFSET (PUD_START_OFFSET + (PUD_COUNT * PAGE_SIZE))
#define PT_DIR_SIZE ((PGD_COUNT + PUD_COUNT + PMD_COUNT) * PAGE_SIZE)

#define PT_PAGE 0b11  // 4k granule
#define PT_BLOCK 0b01 // 2M granule
// accessibility
#define PT_KERNEL (0 << 6) // privileged, supervisor EL1 access only
#define PT_USER (1 << 6)   // unprivileged, EL0 access allowed
#define PT_RW (0 << 7)     // read-write
#define PT_RO (1 << 7)     // read-only
#define PT_AF (1 << 10)    // accessed flag
#define PT_NX (1UL << 54)  // no execute
// shareability
#define PT_OSH (2 << 8) // outter shareable
#define PT_ISH (3 << 8) // inner shareable
// defined in MAIR register
#define PT_MEM (0 << 2) // normal memory
#define PT_DEV (1 << 2) // device MMIO
#define PT_NC (2 << 2)  // non-cachable

#define TTBR_CNP 1

extern volatile uint64_t __pt_dir_start[];
volatile uint64_t pt_dir_start = (uint64_t)&__pt_dir_start[0];

void init_page_tables()
{
    memzero(pt_dir_start, PT_DIR_SIZE);
    uint64_t section_size = SECTION_SIZE; // avoid overflow
    uint64_t pgd_paddr = pt_dir_start + PGD_START_OFFSET;
    uint64_t pud_paddr = pt_dir_start + PUD_START_OFFSET;
    uint64_t pmd_paddr = pt_dir_start + PMD_START_OFFSET;

    put64(pgd_paddr, pud_paddr | PT_PAGE); // we have area in it mapped by pages
                                           // PT_AF |     // accessed flag
                                           // PT_KERNEL | // privileged
                                           // PT_ISH |    // inner shareable
                                           // PT_MEM;     // normal memory

    int pud_idx = PAGE_TABLE_ENTRY_COUNT * PGD_COUNT;
    int i;
    for (i = 0; i < PMD_COUNT; ++i)
    {
        put64(pud_paddr + (i * 8), (pmd_paddr + (i * PAGE_SIZE)) | PT_PAGE); // we have area in it mapped by pages
                                                                             //  PT_AF |     // accessed flag
                                                                             //  PT_KERNEL | // privileged
                                                                             //  PT_ISH |    // inner shareable
                                                                             //  PT_MEM;     // normal memory
        int j;
        for (j = 0; j < PAGE_TABLE_ENTRY_COUNT; ++j)
        {
            uint64_t paddr = KERNEL_MEMORY_START + (i * PAGE_TABLE_ENTRY_COUNT * section_size) + (j * section_size);
            put64(pmd_paddr + (i * PAGE_SIZE) + (j * 8), paddr | MMU_SECTION_FLAGS);
        }
    }
    // Overwrite device addresses
    int j;
    for (j = 0; j < PAGE_TABLE_ENTRY_COUNT; ++j)
    {
        uint64_t paddr = KERNEL_MEMORY_START + (3 * PAGE_TABLE_ENTRY_COUNT * section_size) + (j * section_size);
        put64(pmd_paddr + ((PMD_COUNT - 1) * PAGE_SIZE) + (j * 8), paddr | MMU_SECTION_FLAGS);
    }
}

void print_page_tables(void)
{
    print_hex(pt_dir_start, 16);
    print_string("\r\n");
    asm volatile("adrp x0, pt_dir_start");
    register uint64_t val asm("x0");
    print_string("pt_dir_start: ");
    print_hex(val, 16);
    print_string("\r\n");

    print_string("--PGD--\r\n");
    uint64_t start = 0x7000;
    uint64_t pointer = get64(start);
    print_hex(start, 16);
    print_string(":\r\n");
    print_hex(pointer, 16);
    print_string("\r\n");
    print_string("\r\n");
    start = pointer & ~(0b11);

    print_string("--PUD--\r\n");
    uint64_t pmd[4];
    int i = 0;
    for (i = 0; i < 4; ++i)
    {
        pointer = get64(start);
        print_hex(start, 16);
        print_string(":\r\n");
        print_hex(pointer, 16);

        print_string("\r\n");
        print_string("\r\n");
        pmd[i] = pointer & ~0b11;
        start += 0x0008;
    }

    int j = 0;
    for (j = 0; j < 4; ++j)
    {
        print_string("------\r\n");
        print_string("--PMD");
        print_int(j);
        print_string("--\r\n");
        print_string("------\r\n");
        start = pmd[j];
        for (i = 0; i < 512; ++i)
        {
            print_int(i);
            print_string("\r\n");
            pointer = get64(start);
            print_hex(start, 16);
            print_string(":\r\n");
            print_hex(get64(start), 16);

            print_string("\r\n");
            print_string("\r\n");
            start += 0x0008;
        }
    }
}