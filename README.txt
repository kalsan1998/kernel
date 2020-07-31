TODO:
- Boot
    - Chain loader -> boot kernel at 0x0
    - Replace screen with python script
- Exceptions
    - Pass CurrentEL to basic handler and apply operations from there
    - Change EL from EL3 to EL2 and EL2 to EL1
- Processes/Threads
    - Threads
        - Use better way of allocating space for thread
        - Priority for threads
        - Threads have trouble passing string literals as arguments. Something weird happens with
          read-only memory. Pointers still work.
        - Attach scheduler to ARM Timer instead of System Timer
- Locks
- Virtual Memory
- Graphics

- Other
    - Add reg dump for debug
    - String utils
    - Get mini uart to work
    - Add callbacks for timer

Things I learned:
- Byte addressing -> Each address points to one byte :: 2^32 bits -> 4GB
- VC RAM is 0x40000000 and downwards (size determined in config.txt)
- setting `kernel_old=1` loads kernel.img to address 0x0. Also causes boot at EL3
- ARM Timer is dynamic (e.g. lower-power mode affects it). System Timer is more accurate.
- GPU uses system timers 0 and 2
- Use scr_el3 to enable irq/fiq/serror for el3
- esr_eln (exception syndrome) only updated for SError. GIC is for IRQ/FIQ.
- DAIF masks are automatically set to prevent further interrupts. Therefore need must reset daif
allow nested interrupts.
- Threads have their own space allocated for stacks.


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
0xfe000000(4GB) +-------------------+
                | Device Registers  |
                +-------------------+

