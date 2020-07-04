#include "utils.h"

#include "uart.h"

int read_int(void)
{
    int i = 0;
    i = uart_read() << 24;
    i |= uart_read() << 16;
    i |= uart_read() << 8;
    i |= uart_read();
    return i;
}

void write_int(int number)
{
    uart_write((char)((number >> 24) & 0xFF));
    uart_write((char)((number >> 16) & 0xFF));
    uart_write((char)((number >> 8) & 0xFF));
    uart_write((char)(number & 0xFF));
}

void print_string(char *c)
{
    while (*c)
    {
        uart_write(*c++);
    }
}