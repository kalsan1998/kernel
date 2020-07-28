// #include "threads.h"

// #define THREAD_SPACE_START 0x004000000 // 4MB for
// #define MAX_THREADS 3
// #define THREAD_STACK_SIZE 0x1000 // 4KB
// #define RESERVED_THREAD_SPACE MAX_THREADS *THREAD_STACK_SIZE

// struct thread
// {
//     // Registers. Thread state is stored/restored here on preemption.
//     // According to ARM conventions: x0-x18 can be overwritten by called functions
//     uint64_t x19;
//     uint64_t x20;
//     uint64_t x21;
//     uint64_t x22;
//     uint64_t x23;
//     uint64_t x24;
//     uint64_t x25;
//     uint64_t x26;
//     uint64_t x27;
//     uint64_t x28;
//     uint64_t fp;
//     uint64_t pc;
//     uint64_t sp;

//     int state;
// };

// static struct thread threads[MAX_THREADS];
// static int curr = 0;

// void init_thread_scheduler(void)
// {
//     int i;
//     for (i = 0; i < MAX_THREADS; ++i)
//     {
//         threads[i].state = 0;
//     }
// }

// int new_thread(uint64_t entry, uint64_t arg)
// {
//     int id = reserve_new_thread_id();
//     if (id == -1)
//     {
//         return -1;
//     }
//     struct thread *switch_thread = &threads[id];
//     switch_thread->x19 = entry;
//     switch_thread->x20 = arg;
//     switch_thread->pc = 0; //return from fork// enable preemtpion (schedule tail)// move x20 to x0// blr x19
//     switch_thread->sp = 0; //stack size of thread
// }

// // switch thread:
// // store current thread registers on stack, load next threads registers from stack

// int reserve_new_thread_id(void)
// {
//     int i;
//     for (i = 0; i < MAX_THREADS; ++i)
//     {
//         if (threads[i].state == 0)
//         {
//             threads[i].state = 1;
//             return i;
//         }
//     }
//     return -1;
// }