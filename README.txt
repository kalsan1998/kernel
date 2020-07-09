TODO:
- Boot
    - Chain loader -> boot kernel at 0x0
    - Replace screen with python script
- Interrupts
    - Change EL (should be at EL1?)
    - Return to code from exception handler
    - Implement a timer
- Processes/Threads
- Locks
- Virtual Memory
- Graphics

- Other
    - gpio macros for "ALT FUNCTION" codes
    - get mini uart to work

Things I learned:
- setting `kernel_old=1` loads kernel.img to address 0x0. Also causes boot at EL3