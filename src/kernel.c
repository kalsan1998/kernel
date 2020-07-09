#include "exceptions.h"
#include "gpio.h"
#include "stdio.h"
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
    // Cortex-A72 Technical Reference Manual Pg.63
    switch (el)
    {
    case 0:
        print_string("EL0: Applications\r\n");
        break;
    case 1:
        print_string("EL1: OS kernel functions (privileged)\r\n");
        break;
    case 2:
        print_string("EL2: Hypervisor\r\n");
        break;
    case 3:
        print_string("EL3: Secure monitor\r\n");
        break;
    default:
        print_string("EL?: Invalid\r\n");
    }
}

int main(void)
{
    init_vector_table_el3();
    init_uart();
    read_char();
    print_current_exception_level();
    print_string("--------\r\n");
    show_input();
    return 0;
}