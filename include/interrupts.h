#ifndef INTERRUPTS_H
#define INTERRUPTS_H

extern void enable_irq(void);
extern void disable_irq(void);

void enable_vc_interrupt(int interrupt_number);
void handle_irq(void);

#endif // INTERRUPTS_H