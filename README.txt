TODO:
- Boot
    - Chain loader -> boot kernel at 0x0
    - Replace screen with python script
- Exceptions
    - Change EL from EL3 to EL2 and EL2 to EL1
    - Return to code from exception handler
        -   Need to store general purpose registers (x0-x30) onto stack then pop off after
    - Implement a timer
- Processes/Threads
- Locks
- Virtual Memory
- Graphics

- Other
    - Get mini uart to work

Things I learned:
- setting `kernel_old=1` loads kernel.img to address 0x0. Also causes boot at EL3
- ARM Timer is dynamic (e.g. lower-power mode affects it). System Timer is more accurate.
