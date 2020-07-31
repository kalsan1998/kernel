#ifndef THREAD_H
#define THREADS_H

#include "stdint.h"

void init_threads(void);
int new_thread(uint64_t entry, uint64_t arg);
void enable_preempt(void);
void disable_preempt(void);

void timer_tick(void);

#endif // THREADS_H