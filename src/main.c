
#include "aux.h"
#include "common.h"
#include "gpio.h"
#include "uart.h"

void print_string(char *c)
{
    while (*c)
    {
        uart_write(*c++);
    }
}

void mirror_input(void)
{
    char c = uart_read();
    if (c == '\r')
    {
        print_string("\r\n");
    }
    else
    {
        uart_write(c);
    }
}

void blink_light(void)
{
    volatile unsigned int timer = 0;
    for (timer = 0; timer < 500000; ++timer)
    {
    }
    set_gpset(42, 1);

    for (timer = 0; timer < 500000; ++timer)
    {
    }
    set_gpclr(42, 1);
}

int main(void)
{
    volatile unsigned int i = 0;

    init_uart();
    set_gpfsel(42, 1);
    set_gpset(42, 1); // ACT light on

    print_string("Input:\r\n");
    while (1)
    {
        mirror_input();
    }
    return 0;
}
