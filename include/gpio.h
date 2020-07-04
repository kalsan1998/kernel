#ifndef GPIO_H
#define GPIO_H

#define GPIO_BASE 0xfe200000

#define GPFSEL0 0xfe200000
#define GPFSEL1 0xfe200004
#define GPFSEL2 0xfe200008
#define GPFSEL3 0xfe20000c
#define GPFSEL4 0xfe200010
#define GPFSEL5 0xfe200014

#define GPSET0 0xfe20001c
#define GPSET1 0xfe200020

#define GPCLR0 0xfe200028
#define GPCLR1 0xfe20002c

#define GPIO_PUP_PDN_CNTRL_REG0 0xfe2000e4
#define GPIO_PUP_PDN_CNTRL_REG1 0xfe2000e8
#define GPIO_PUP_PDN_CNTRL_REG2 0xfe2000ec
#define GPIO_PUP_PDN_CNTRL_REG3 0xfe2000f0

unsigned int gpfsel_addr(int pin);
unsigned int gpset_addr(int pin);
unsigned int gpclr_addr(int pin);
unsigned int gpio_pup_pdn_cntrl_reg_addr(int pin);

// Mode = [0,7]
void set_gpfsel(int pin, int mode);
void set_gpset(int pin, int val);
void set_gpclr(int pin, int val);
void set_gpio_pup_pdn_cntrl(int pin, int val);

#endif // GPIO_H