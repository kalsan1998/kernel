#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>

void enable_timer_irq(void);
void start_timer(uint32_t micro);
void handle_timer_irq(void);

#endif // TIMER_H