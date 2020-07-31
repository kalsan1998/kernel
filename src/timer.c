#include "timer.h"

#include "interrupts.h"
#include "stdio.h"
#include "threads.h"
#include "utils.h"

#define SYSTEM_TIMER_BASE 0xfe003000
#define CS SYSTEM_TIMER_BASE
#define CLO SYSTEM_TIMER_BASE + 0x04 // Counter Lower 32 bits
#define CHI SYSTEM_TIMER_BASE + 0x08 // Counter Higher 32 bits
#define C0 SYSTEM_TIMER_BASE + 0x0c  // Compare 0
#define C1 SYSTEM_TIMER_BASE + 0x10  // Compare 1
#define C2 SYSTEM_TIMER_BASE + 0x14  // Compare 2
#define C3 SYSTEM_TIMER_BASE + 0x18  // Compare 3

// https://www.raspberrypi.org/forums/viewtopic.php?f=72&t=17855
// Timer 0 is used for the GPU RTOS (threadx) as the timer tick (100 interrupts / second).
// Timer 2 is used for lightweight timers than can call callbacks with microsecond (*) resolution.

// Currently just use C1
void enable_timer_irq(void)
{
    // From Table 100 (pg 108), Timer1 is VideoCore interrupt 1
    enable_vc_interrupt(1);
    enable_vc_interrupt(3);
}

void start_timer1(uint32_t micro)
{
    print_string("Setting timer for ");
    print_int(micro / 1000);
    print_string("ms\r\n");
    put32(C1, get32(CLO) + micro);
}

void handle_timer1_irq(void)
{
    print_string("Timer!\r\n");
    put32(CS, (1 << 1)); // Clears C1 (IRQ0_PENDING is cleared)
}

uint32_t interval;
// Timer3 is for loops
void set_timer3_loop_interval(uint32_t micro)
{
    interval = micro;
    put32(C3, get32(CLO) + micro);
}

void handle_timer3_irq(void)
{
    put32(CS, (1 << 3));
    put32(C3, get32(CLO) + interval);
    timer_tick();
}