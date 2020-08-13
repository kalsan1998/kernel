#include "exceptions.h"
#include "gpio.h"
#include "interrupts.h"
#include "mm.h"
#include "stdio.h"
#include "threads.h"
#include "timer.h"
#include "uart.h"
#include "virtual_memory.h"

void thread_entry(const int id)
{
    print_string("Inside thread ");
    print_int(id);
    print_string("\r\n");
    while (1)
    {
        print_int(id);
    }
}

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
            start_timer1(5000000);
        }
        else if (c == '@')
        {
            int err = new_thread(&thread_entry, 1);
            if (err != 0)
            {
                print_string("Error starting thread 1\r\n");
            }
            err = new_thread(&thread_entry, 2);
            if (err != 0)
            {
                print_string("Error starting thread 2\r\n");
            }
            err = new_thread(&thread_entry, 3);
            if (err != 0)
            {
                print_string("Error starting thread 3\r\n");
            }
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

void el1_main(void)
{
    enable_timer_irq();
    enable_irq();
    //init_threads();
    print_current_exception_level();
    print_hex(test_el1_translation(0xffff000000001234), 16);
    print_hex(test_el1_translation(0xffff0000fe205000), 16);
    //set_timer3_loop_interval(100000); //100ms
    show_input();
    while (1)
        ;
}

int main(void)
{
    init_uart();
    read_char();
    init_vector_tables();
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