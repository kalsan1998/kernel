#ifndef UART_H
#define UART_H

void init_uart(void);
void uart_write(char c);
char uart_read(void);

#endif // UART_H