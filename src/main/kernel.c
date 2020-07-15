#include "exceptions.h"
#include "gpio.h"
#include "interrupts.h"
#include "stdio.h"
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

void print_current_exception_level(void)
{
    int el = current_el();
    print_string("Current Exception Level: ");
    switch (el)
    {
    case 0:
        print_string("EL0 -- Applications\r\n");
        break;
    case 1:
        print_string("EL1 -- OS kernel functions (privileged)\r\n");
        break;
    case 2:
        print_string("EL2 -- Hypervisor\r\n");
        break;
    case 3:
        print_string("EL3 -- Secure monitor\r\n");
        break;
    default:
        print_string("EL");
        print_int(el);
        print_string("-- Unknown\r\n");
    }
}

void el1_main(void)
{
    init_interrupts();
    print_current_exception_level();
    show_input();
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