#include "utils.h"

#include "uart.h"

void put(unsigned int addr, int val)
{
    *((volatile unsigned int *)addr) = val;
}

unsigned int get(unsigned int addr)
{
    return *((volatile unsigned int *)addr);
}

int read32(void)
{
    int i = 0;
    i = uart_read() << 24;
    i |= uart_read() << 16;
    i |= uart_read() << 8;
    i |= uart_read();
    return i;
}

void write32(int number)
{
    uart_write((char)((number >> 24) & 0xFF));
    uart_write((char)((number >> 16) & 0xFF));
    uart_write((char)((number >> 8) & 0xFF));
    uart_write((char)(number & 0xFF));
}
