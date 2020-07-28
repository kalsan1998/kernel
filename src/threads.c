#include "threads.h"

#include "stdio.h"

#define THREAD_SPACE_START 0x004000000 // give 4MB for kernel img
#define MAX_THREADS 3
#define THREAD_STACK_SIZE 0x1000 // 4KB
#define RESERVED_THREAD_SPACE MAX_THREADS *THREAD_STACK_SIZE

extern void new_thread_start(void);

struct thread
{
    // Registers. Thread state is stored/restored here on preemption.
    // According to ARM conventions: x0-x18 can be overwritten by called functions
    uint64_t x19;
    uint64_t x20;
    uint64_t x21;
    uint64_t x22;
    uint64_t x23;
    uint64_t x24;
    uint64_t x25;
    uint64_t x26;
    uint64_t x27;
    uint64_t x28;
    uint64_t fp; // x29
    uint64_t pc; // x30
    uint64_t sp;

    int id;
    int state;
    uint64_t base;
};

struct thread threads[MAX_THREADS];
int curr = -1;

void init_threads(void)
{
    int i;
    for (i = 0; i < MAX_THREADS; ++i)
    {
        threads[i].state = 0;
        threads[i].base = THREAD_SPACE_START + (i * THREAD_STACK_SIZE);
    }
}

int new_thread(uint64_t entry, uint64_t arg)
{
    int id = reserve_thread();
    if (id == -1)
    {
        return -1;
    }
    struct thread *new_thread = &threads[id];
    new_thread->x19 = entry;
    new_thread->x20 = arg;
    new_thread->pc = (uint64_t)new_thread_start;
    new_thread->sp = new_thread->base + THREAD_STACK_SIZE;

    switch_thread(id);
    return 0;
}

void switch_thread(int id)
{
    if (id == curr)
    {
        return;
    }
    int old_curr = curr;
    curr = id;
    context_switch(&threads[old_curr], &threads[curr]);

    print_string("switch_thread() - Shold not get here.");
}

// switch thread:
// store current thread registers on stack, load next threads registers from stack

int reserve_thread(void)
{
    int i;
    for (i = 0; i < MAX_THREADS; ++i)
    {
        if (threads[i].state == 0)
        {
            threads[i].state = 1;
            threads[i].id = i;
            return i;
        }
    }
    return -1;
}