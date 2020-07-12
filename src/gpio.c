#include "gpio.h"

#include "utils.h"

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

uint32_t gpfsel_addr(int pin)
{
    if (pin <= 9)
    {
        return GPFSEL0;
    }
    else if (pin <= 19)
    {
        return GPFSEL1;
    }
    else if (pin <= 29)
    {
        return GPFSEL2;
    }
    else if (pin <= 39)
    {
        return GPFSEL3;
    }
    else if (pin <= 49)
    {
        return GPFSEL4;
    }
    else if (pin <= 57)
    {
        return GPFSEL5;
    }
    return 0;
}

uint32_t gpset_addr(int pin)
{
    if (pin <= 31)
    {
        return GPSET0;
    }
    else if (pin <= 57)
    {
        return GPSET1;
    }
    return 0;
}

uint32_t gpclr_addr(int pin)
{
    if (pin <= 31)
    {
        return GPCLR0;
    }
    else if (pin <= 57)
    {
        return GPCLR1;
    }
    return 0;
}

uint32_t gpio_pup_pdn_cntrl_reg_addr(int pin)
{
    if (pin <= 15)
    {
        return GPIO_PUP_PDN_CNTRL_REG0;
    }
    else if (pin <= 31)
    {
        return GPIO_PUP_PDN_CNTRL_REG1;
    }
    else if (pin <= 47)
    {
        return GPIO_PUP_PDN_CNTRL_REG2;
    }
    else if (pin <= 57)
    {
        return GPIO_PUP_PDN_CNTRL_REG3;
    }
    return 0;
}

void set_gpfsel(int pin, int mode)
{
    uint32_t addr = gpfsel_addr(pin);
    uint32_t sel = get32(addr);
    int shift = 3 * (pin % 10);
    sel &= ~(7 << shift);
    sel |= (mode << shift);
    put32(addr, sel);
}

void set_gpset(int pin, int val)
{
    uint32_t addr = gpset_addr(pin);
    uint32_t sel = get32(addr);
    int shift = (pin % 32);
    sel &= ~(1 << shift);
    sel |= (val << shift);
    put32(addr, sel);
}
void set_gpclr(int pin, int val)
{
    uint32_t addr = gpclr_addr(pin);
    uint32_t sel = get32(addr);
    int shift = (pin % 32);
    sel &= ~(1 << shift);
    sel |= (val << shift);
    put32(addr, sel);
}

void set_gpio_pup_pdn_cntrl(int pin, int val)
{
    uint32_t addr = gpio_pup_pdn_cntrl_reg_addr(pin);
    uint32_t sel = get32(addr);
    int shift = 2 * (pin % 16);
    sel &= ~(3 << shift);
    sel |= (val << shift);
    put32(addr, sel);
}
