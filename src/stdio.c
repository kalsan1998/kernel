#include "stdio.h"

#include "uart.h"

#define TO_HEX(i) (i <= 9 ? '0' + i : 'A' - 10 + i)

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

void print_int(int64_t n)
{
    if (n < 0)
    {
        print_char('-');
        n *= -1;
    }
    if (n == 0)
    {
        print_char('0');
    }
    int digits[20];
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

void print_hex(uint64_t n, int nybbles)
{
    print_string("0x");
    int i = nybbles;
    while (--i >= 0)
    {
        int nybble = (n >> (i * 4)) & 0xf;
        print_char(TO_HEX(nybble));
    }
}
