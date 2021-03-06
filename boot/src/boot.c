
#include "gpio.h"
#include "uart.h"
#include "utils.h"

#define KERNEL_BASE_ADDRESS 0x1000 // 4KB

void copy_new_kernel_and_jump(void)
{
    unsigned char *kernel = (unsigned char *)KERNEL_BASE_ADDRESS;

    int size = read32();
    write32(size);
    set_gpclr(42, 1);

    int sum = 0;
    int i = 0;
    for (i = 0; i < size; ++i)
    {
        char c = uart_read();
        uart_write(c);
        sum += c;
        *kernel++ = c;
    }
    set_gpset(42, 1);
    write32(sum);
    uart_read();
    branch_to_address((void *)KERNEL_BASE_ADDRESS);
}

int main(void)
{
    init_uart();
    set_gpfsel(42, 1);
    set_gpset(42, 1);
    copy_new_kernel_and_jump();

    // Should not get here.
    while (1)
        ;
    return 0;
}
