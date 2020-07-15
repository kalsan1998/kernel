#include "timer.h"

#include "stdio.h"
#include "utils.h"

#define SYSTEM_TIMER_BASE 0xfe003000
#define CS SYSTEM_TIMER_BASE
#define CLO SYSTEM_TIMER_BASE + 0x04 // Counter Lower 32 bits
#define CHI SYSTEM_TIMER_BASE + 0x08 // Counter Higher 32 bits
#define C0 SYSTEM_TIMER_BASE + 0x0c  // Compare 0
#define C1 SYSTEM_TIMER_BASE + 0x10  // Compare 1
#define C2 SYSTEM_TIMER_BASE + 0x14  // Compare 2
#define C3 SYSTEM_TIMER_BASE + 0x18  // Compare 3

// Currently just use C1

void start_timer(uint32_t micro)
{
    print_string("Setting timer for ");
    print_int(micro / 1000);
    print_string("ms\r\n");
    put32(C3, get32(CLO) + micro);
}

void handle_timer_irq(void)
{
    print_string("Timer!\r\n");
    put32(CS, 8); // Clears C1
}