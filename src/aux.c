#include "aux.h"

#include "gpio.h"
#include "utils.h"

#define AUX_BASE 0xfe215000

#define AUX_ENABLES 0xfe215004
#define AUX_MU_IO_REG 0xfe215040
#define AUX_MU_IER_REG 0xfe215044
#define AUX_MU_IIR_REG 0xfe215048
#define AUX_MU_LCR_REG 0xfe21504c
#define AUX_MU_MCR_REG 0xfe215050
#define AUX_MU_LSR_REG 0xfe215054
#define AUX_MU_CNTL_REG 0xfe215060
#define AUX_MU_BAUD_REG 0xfe215068

void init_mini_uart(void)
{
    // Mini UART -> UART1
    set_gpfsel(14, 2); // set pin14 TXD1 (ALT5)
    set_gpfsel(15, 2); // set pin15 RXD1 (ALT5)

    // Clear pull up and pull down resistors
    set_gpio_pup_pdn_cntrl(14, 0);
    set_gpio_pup_pdn_cntrl(15, 0);

    // From: https://s-matyukevich.github.io/raspberry-pi-os/docs/lesson01/rpi-os.html
    put32(AUX_ENABLES, 1);     // enables mini UART
    put32(AUX_MU_IER_REG, 0);  // Disable receive and transmit interrupts
    put32(AUX_MU_CNTL_REG, 0); // Disable auto flow control and disable receiver and transmitter
    put32(AUX_MU_LCR_REG, 1);  // Enable 8 bit mode
    put32(AUX_MU_MCR_REG, 0);  // Set RTS line to be always high since we don't need it
    put32(AUX_MU_IIR_REG, 7);  // Clears FIFO and sets no interrupt pending
    // Serial port is capable of transferring max 115200 bits per second.
    // Mini UART calculates baud with:
    //      baudrate = system_clock_freq / (8 * ( baudrate_reg + 1 ))
    //  system_clock_freq = 500 MHz
    put32(AUX_MU_BAUD_REG, 270); // Set baud rate to 115200

    put32(AUX_MU_CNTL_REG, 2); // Enable transmitter
}

void mini_uart_write(char c)
{
    while (1)
    {
        if (get32(AUX_MU_LSR_REG) & 0x20)
            break;
    }
    put32(AUX_MU_IO_REG, c);
}
