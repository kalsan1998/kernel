
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

int main(void)
{
    volatile unsigned int i = 0;
    volatile unsigned int timer = 0;

    init_uart();
    set_gpfsel(42, 1);
    volatile int count = 0;
    while (1)
    {
        for (timer = 0; timer < 500000; ++timer)
        {
        }
        set_gpset(42, 1);

        print_string("Wow.\r\n");

        for (timer = 0; timer < 500000; ++timer)
        {
        }
        set_gpclr(42, 1);
    }
    return 0;
}
