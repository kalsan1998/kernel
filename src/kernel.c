#include "exceptions.h"
#include "gpio.h"
#include "interrupts.h"
#include "stdio.h"
#include "threads.h"
#include "timer.h"
#include "uart.h"

void show_input(void)
{
    print_string("Input:\r\n");
    while (1)
    {
        char c = read_char();
        if (c == '\r')
        {
            print_string("\r\n");
        }
        else if (c == '~')
        {
            force_exception();
        }
        else if (c == '!')
        {
            start_timer(5000000);
        }
        else
        {
            print_char(c);
        }
    }
}

void blink_light(void)
{
    set_gpfsel(42, 1);
    volatile unsigned int timer = 0;
    while (1)
    {
        for (timer = 0; timer < 1000000; ++timer)
        {
        }
        print_string("On\n");
        set_gpset(42, 1);

        for (timer = 0; timer < 1000000; ++timer)
        {
        }
        print_string("Off\n");
        set_gpclr(42, 1);
    }
}

struct msg
{
    char *d;
};

struct msg test = {};

void thread_entry(struct msg *t)
// void thread_entry(uint64_t f)
{
    print_char(t->d[1]);

    while (1)
        ;
}

void el1_main(void)
{
    enable_timer_irq();
    enable_irq();
    print_current_exception_level();

    // int err = new_thread(&show_input, 0);
    // if (err != 0)
    // {
    //     print_string("Error starting thread 1\r\n");
    // }
    test.d = "hello";
    int err = new_thread((uint64_t)&thread_entry, (uint64_t)&test);
    if (err)
    {
        print_string("Error starting thread 2\r\n");
    }
}

int main(void)
{
    init_uart();
    read_char();
    init_vector_tables();
    init_threads();

    print_current_exception_level();
    if (current_el() != 1)
    {
        print_string("Jumping to EL1\r\n");
        print_string("---\r\n");
        el3_to_el1();
    }
    else
    {
        el1_main();
    }
    print_string("Should not be here!\r\n");
    return 0;
}