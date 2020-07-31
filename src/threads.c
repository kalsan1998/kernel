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
    uint64_t base;
    int preempt_enabled;
    int timer_count;
};

// TODO: Store pointers to address instead.
struct thread threads[MAX_THREADS];
int curr = 0;

void enable_preempt(void)
{
    threads[curr].preempt_enabled = 1;
}
void disable_preempt(void)
{
    threads[curr].preempt_enabled = 0;
}

void init_threads(void)
{
    int i;
    for (i = 0; i < MAX_THREADS; ++i)
    {
        threads[i].id = -1;
        threads[i].base = THREAD_SPACE_START + (i * THREAD_STACK_SIZE);
        threads[i].timer_count = 0;
        threads[i].preempt_enabled = 1;
    }
    threads[curr].id = curr;
}

int new_thread(uint64_t entry, uint64_t arg)
{
    int id = reserve_thread();
    if (id == -1)
    {
        return -1;
    }
    struct thread *new_thread = &threads[id];
    new_thread->timer_count = 1;
    new_thread->preempt_enabled = 0;
    new_thread->x19 = entry;
    new_thread->x20 = arg;
    new_thread->pc = (uint64_t)new_thread_start;
    new_thread->sp = new_thread->base + THREAD_STACK_SIZE;
    return 0;
}

void switch_thread(int id)
{
    print_string("Attempting thread switch (");
    print_int(curr);
    print_string(" to ");
    print_int(id);
    print_string(")\r\n");
    if (id == curr)
    {
        return;
    }
    int old_curr = curr;
    curr = id;
    context_switch(&threads[old_curr], &threads[curr]);

    print_string("switch_thread() - Shold not get here.");
}

int reserve_thread(void)
{
    int i;
    for (i = 0; i < MAX_THREADS; ++i)
    {
        if (threads[i].id == -1)
        {
            threads[i].id = i;
            return i;
        }
    }
    return -1;
}

void schedule_next_thread()
{
    while (1)
    {
        int next_thread_id = -1;
        int max_count = 0;
        int i;
        for (i = 0; i < MAX_THREADS; ++i)
        {
            if (threads[i].id != -1 && threads[i].timer_count > max_count)
            {
                max_count = threads[i].timer_count;
                next_thread_id = i;
            }
        }
        if (next_thread_id != -1)
        {
            switch_thread(next_thread_id);
            return;
        }
        for (i = 0; i < MAX_THREADS; ++i)
        {
            if (threads[i].id != -1)
            {
                threads[i].timer_count++;
            }
        }
    }
}

void timer_tick(void)
{
    struct thread current_thread = threads[curr];
    print_int(current_thread.timer_count);
    print_string(" -- ");
    print_int(current_thread.preempt_enabled);
    if (--current_thread.timer_count <= 0 && current_thread.preempt_enabled == 1)
    {
        disable_preempt();
        enable_irq();
        schedule_next_thread();
        // When we come back to this thread then returns here.
        disable_irq();
        enable_preempt();
    }
}