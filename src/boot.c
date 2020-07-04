
#include "common.h"
#include "gpio.h"
#include "uart.h"
#include "utils.h"

#define KERNEL_BASE_ADDRESS 0x0

void copy_new_kernel_and_jump(void)
{
    unsigned char *kernel = (unsigned char *)KERNEL_BASE_ADDRESS;
    init_uart();
    int size = read_int();
    write_int(size);
    int sum = 0;
    set_gpclr(42, 1);
    for (int i = 0; i < size; ++i)
    {
        char c = uart_read();
        uart_write(c);
        sum += c;
        *kernel++ = c;
    }
    set_gpset(42, 1);
    write_int(sum);

    branch_to_address((void *)KERNEL_BASE_ADDRESS);
}

int main(void)
{
    set_gpfsel(42, 1);
    set_gpset(42, 1);
    copy_new_kernel_and_jump();

    // Should not get here.
    while (1)
        ;
    return 0;
}
