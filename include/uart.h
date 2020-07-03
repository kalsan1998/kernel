#ifndef UART_H
#define UART_H

#define UART0_BASE 0xfe201000

#define UART0_DR 0xfe201000
#define UART0_FR 0xfe201018
#define UART0_IBRD 0xfe201024
#define UART0_FBRD 0xfe201028
#define UART0_LCRH 0xfe20102c
#define UART0_CR 0xfe201030

void init_uart(void);
void uart_write(char c);

#endif // UART_H