#include "stdio.h"

#include "uart.h"

void print_char(char c)
{
    uart_write(c);
}

char read_char(void)
{
    return uart_read();
}

void print_string(const char *s)
{
    while (*s)
    {
        print_char(*s++);
    }
}

void print_int(int n)
{
    if (n == 0)
    {
        print_char('0');
    }
    int digits[10];
    int i = 0;
    while (n)
    {
        digits[i++] = n % 10;
        n /= 10;
    }
    --i;
    while (i >= 0)
    {
        print_char(digits[i--] + '0');
    }
}