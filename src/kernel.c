#include "common.h"
#include "gpio.h"
#include "uart.h"
#include "utils.h"

void show_input(void)
{
    print_string("Input:\n");
    while (1)
    {
        char c = uart_read();
        if (c == '\r' || c == '\n')
        {
            print_string("\r\n");
        }
        else
        {
            uart_write(c);
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

int main(void)
{
    init_uart();
    show_input();
    return 0;
}