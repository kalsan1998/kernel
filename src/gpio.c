#include "gpio.h"

#include "common.h"

unsigned int gpfsel_addr(int pin)
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

unsigned int gpset_addr(int pin)
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

unsigned int gpclr_addr(int pin)
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

unsigned int gpio_pup_pdn_cntrl_reg_addr(int pin)
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
    unsigned int addr = gpfsel_addr(pin);
    unsigned int sel = get(addr);
    int shift = 3 * (pin % 10);
    sel &= ~(7 << shift);
    sel |= (mode << shift);
    put(addr, sel);
}

void set_gpset(int pin, int val)
{
    unsigned int addr = gpset_addr(pin);
    unsigned int sel = get(addr);
    int shift = (pin % 32);
    sel &= ~(1 << shift);
    sel |= (val << shift);
    put(addr, sel);
}
void set_gpclr(int pin, int val)
{
    unsigned int addr = gpclr_addr(pin);
    unsigned int sel = get(addr);
    int shift = (pin % 32);
    sel &= ~(1 << shift);
    sel |= (val << shift);
    put(addr, sel);
}

void set_gpio_pup_pdn_cntrl(int pin, int val)
{
    unsigned int addr = gpio_pup_pdn_cntrl_reg_addr(pin);
    unsigned int sel = get(addr);
    int shift = 2 * (pin % 16);
    sel &= ~(3 << shift);
    sel |= (val << shift);
    put(addr, sel);
}
