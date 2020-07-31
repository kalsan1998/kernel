#include "interrupts.h"

#include "stdio.h"
#include "timer.h"
#include "utils.h"

#define ARMC_BASE 0xfe00b000

// IRQ0 -> IRQ for Core 0
// Suffix 0/1 -> VideoCore Interrupt
// Suffix 2 -> ARMC Interrupt
#define IRQ0_PENDING0 ARMC_BASE + 0x200
#define IRQ0_PENDING1 ARMC_BASE + 0x204
#define IRQ0_PENDING2 ARMC_BASE + 0x208

// Write 1 enables. Reading returns state.
#define IRQ0_SET_EN_0 ARMC_BASE + 0x210
#define IRQ0_SET_EN_1 ARMC_BASE + 0x214
#define IRQ0_SET_EN_2 ARMC_BASE + 0x218

// Write 1 clears
#define IRQ0_CLR_EN_0 ARMC_BASE + 0x220
#define IRQ0_CLR_EN_1 ARMC_BASE + 0x224
#define IRQ0_CLR_EN_2 ARMC_BASE + 0x228

void enable_vc_interrupt(int interrupt_number)
{
    uint32_t address = 0;
    if (interrupt_number <= 31)
    {
        address = IRQ0_SET_EN_0;
    }
    else
    {
        address = IRQ0_SET_EN_1;
    }
    put32(address, get32(address) | (1 << (interrupt_number % 32)));
}

void handle_irq(void)
{
    int handled = 0;
    if (get32(IRQ0_PENDING0) & (1 << 1))
    {
        handle_timer1_irq();
        handled = 1;
    }
    if (get32(IRQ0_PENDING0) & (1 << 3))
    {
        handle_timer3_irq();
        handled = 1;
    }
    if (handled == 0)
    {
        print_string("Unknown Interrupt Type\r\n");
    }
}