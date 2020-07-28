#ifndef THREAD_H
#define THREADS_H

#include "stdint.h"

int new_thread(uint64_t entry, uint64_t arg);

#endif // THREADS_H