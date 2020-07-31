#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>

void enable_timer_irq(void);
void start_timer1(uint32_t micro);
void set_timer3_loop_interval(uint32_t micro);
void handle_timer1_irq(void);
void handle_timer3_irq(void);

#endif // TIMER_H