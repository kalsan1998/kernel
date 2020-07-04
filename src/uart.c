#include "uart.h"

#include "common.h"
#include "gpio.h"

void init_uart(void)
{
    // UART0
    set_gpfsel(14, 4); // set pin14 TXD0 (ALT0)
    set_gpfsel(15, 4); // set pin15 RXD0 (ALT0)

    // Clear pull up and pull down resistors
    set_gpio_pup_pdn_cntrl(14, 0);
    set_gpio_pup_pdn_cntrl(15, 0);

    // Set FEN bit to 0 to flush tansmit.
    put(UART0_LCRH, 0);
    // Disable UART before changing control registers.
    put(UART0_CR, 0);

    // - The UART_IBRD Register is the integer part of the baud rate divisor value.
    // - The UART_FBRD Register is the fractional part of the baud rate divisor value.
    // - The baud rate divisor is calculated as follows:
    //    BAUDDIV = (FUARTCLK/(16 * Baud rate)) where FUARTCLK is the UART reference clock frequency.
    //      FUARTCLK = 48MHz
    //      Baud rate = 115200 bps
    // - NOTE: The contents of the IBRD and FBRD registers are not updated until transmission or
    // reception of the current character is complete
    put(UART0_IBRD, 26);
    put(UART0_FBRD, 3);

    // Word length is set to 8 and enables FIFO buffer.
    put(UART0_LCRH, (3 << 5) | (1 << 4));
    // Enable Rx and Tx and UART.
    put(UART0_CR, (1 << 9) | (1 << 8) | 1);
}

void uart_write(char c)
{
    while (get(UART0_FR) & (1 << 5))
    {
        // Transmit FIFO is full.
    }
    put(UART0_DR, c);
}

char uart_read(void)
{
    while (get(UART0_FR) & (1 << 4))
    {
        // Receive FIFO is empty.
    }
    return get(UART0_DR);
}