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
    put32(address, get32(address) | (1 << interrupt_number));
}

void handle_irq(void)
{
    print_string("-- Handling Interrupt -- \r\n");
    if (get32(IRQ0_PENDING0) & (1 << 1))
    {
        print_string("Timer1 Interrupt Type\r\n");
        handle_timer_irq();
    }
    else
    {
        print_string("Unknown Interrupt Type\r\n");
    }
}