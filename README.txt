TODO:
- Boot
    - Chain loader -> boot kernel at 0x0
    - Replace screen with python script
- Exceptions
    - Change EL from EL3 to EL2 and EL2 to EL1
- Processes/Threads
- Locks
- Virtual Memory
- Graphics

- Other
    - Add reg dump for debug
    - String utils
    - Get mini uart to work

Things I learned:
- setting `kernel_old=1` loads kernel.img to address 0x0. Also causes boot at EL3
- ARM Timer is dynamic (e.g. lower-power mode affects it). System Timer is more accurate.
- GPU uses system timers 0 and 2
- Use scr_el3 to enable irq/fiq/serror for el3
- esr_eln (exception syndrome) only updated for SError. GIC is for IRQ/FIQ.
- DAIF masks are automatically set to prevent further interrupts. Therefore need must reset daif
allow nested interrupts.