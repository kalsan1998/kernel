#ifndef THREAD_H
#define THREADS_H

#include "stdint.h"

void init_threads(void);
int new_thread(uint64_t entry, uint64_t arg);

#endif // THREADS_H