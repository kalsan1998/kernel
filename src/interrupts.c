#include "interrupts.h"

extern void enable_irq(void);
extern void disable_irq(void);

void enable_interrupt_controller()
{
    put32(0xfe00b210, get32(0xfe00b210) | 8);
}

void init_interrupts(void)
{
    enable_interrupt_controller();
    enable_irq();
}