#ifndef AUX_H
#define AUX_H

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

// Doesn't work yet :(
// Seems like 2 bits are getting messed up.
void init_mini_uart(void);
void mini_uart_write(char c);

#endif // AUX_H
