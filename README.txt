TODO:
- Boot
    - Chain loader -> boot kernel at 0x0
    - Replace screen with python script
- Exceptions/Interrupts
    - Pass CurrentEL to basic handler and apply operations from there
    - Change EL from EL3 to EL2 and EL2 to EL1
    - Better callbacks for timers
- Threads
    - Use better way of allocating space for thread
    - Attach scheduler to ARM Timer instead of System Timer
    - Improve scheduler -> CFS pick thread with smalled vrruntime (add priorities)
    - Thread exit/join

- Virtual Memory
- Graphics
- Locks
- Process forking + IPC

- Other
    - Add reg dump for debug
    - String utils
    - Get mini uart to work
    - Make a "shared" directory for boot and main

Things I learned:
- Byte addressing -> Each address points to one byte :: 2^32 bits -> 4GB
- VC RAM is 0x40000000 and downwards (size determined in config.txt)
- setting `kernel_old=1` loads kernel.img to address 0x0. Also causes boot at EL3
- ARM Timer is dynamic (e.g. lower-power mode affects it). System Timer is more accurate.
- GPU uses system timers 0 and 2
- Use scr_el3 to enable irq/fiq/serror for el3
- esr_eln (exception syndrome) only updated for SError. GIC is for IRQ/FIQ.
- DAIF masks are automatically set to prevent further interrupts. Therefore must reset daif to
allow nested interrupts.
- Threads have their own space allocated for stacks (can still access data from other threads)
- Thread switch summary:
    - Timer interrupt happens
    - Store ALL registers and ELR_ELn onto thread stack
    - Determine next thread to switch to (scheduler)
    - Store all callee-saved registered into thread stack
    - Restore callee-saved registed of new stack (including sp and pc)
    - Timer handler exits -> restores all registers and ELR_ELn
- Virtual memory:
    - Each process has copy of all page tables
    - ttbr0_el1 stores address of PGD
    - During context switch, PGD of next process loaded into ttbr_el0
    - MMU uses PGD and virtual address to calculate physical address
    - Virtual address bits: (only uses 48)
        - [39-47] Index in PGD points to PUD
        - [30-38] Index in PUD points to PMD
        - [21-29] Index in PMD points to PTE (sometimes points to physical 2MB section)
        - [12-20] Index in PTE contains physical memory address
        - [0-11]  Contains offset within the page (12 bits -> 4KB)
        - Math: 
            - 9 bits per level, 8 byte addresses 
                -> 9 + 3 bits per page table
                -> page table size = 1 page
            - 64-bit addresspace, 2^12 page size -> 2^52 addressable pages
            - Only using RAM and section mapping (2MB) for now
                -> 4GB/2MB = 2000 = 4 * 2^9
                -> 4 entries in PUD
                -> 1 entry in PGD
        - Index in PT is a descriptor (only bits [12-47] used for address of next PT/Block)
            - Reason for only needed [12-47] bits is because first 12 bits are 0 (aligned to page)
              and last bits aren't used for translation
    - Kernel vs User virtual memory
    - EL0 PGD stored in ttbr0_el0, for addresses starting with x0000
    - EL1 PGD stored in ttbr0_el1, for addresses starting with xffff; can't be accessed from EL0 without SError


Memory:
0x00000000      +-------------------+
                |   Boot Kernel Img |
0x00001000(4KB) +-------------------+
                |   Kernel Image    |
                |-------------------|
                |                   |
0x00400000(4MB) +-------------------+
                |                   |
                |   Kernel Memory   |
                |                   |
0xfe000000(~4GB)+-------------------+
                | Device Registers  |
0x100000000(4GB)+-------------------+

        
