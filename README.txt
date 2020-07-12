TODO:
- Boot
    - Chain loader -> boot kernel at 0x0
    - Replace screen with python script
- Exceptions
    - Show addresss of code
        - Implement EL2 to get IFAR and DFAR from FAR_EL2
    - Change EL (should be at EL1?)
    - Return to code from exception handler
        -   Need to store general purpose registers (x0-x30) onto stack then pop off after
    - Implement a timer
- Processes/Threads
- Locks
- Virtual Memory
- Graphics

- Other
    - Print hex codes. Useful for address debugging.
    - gpio macros for "ALT FUNCTION" codes
    - Get mini uart to work

Things I learned:
- setting `kernel_old=1` loads kernel.img to address 0x0. Also causes boot at EL3