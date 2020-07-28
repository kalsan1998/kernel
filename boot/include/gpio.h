#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>

uint32_t gpfsel_addr(int pin);
uint32_t gpset_addr(int pin);
uint32_t gpclr_addr(int pin);
uint32_t gpio_pup_pdn_cntrl_reg_addr(int pin);

// Mode = [0,7]
void set_gpfsel(int pin, int mode);
void set_gpset(int pin, int val);
void set_gpclr(int pin, int val);
void set_gpio_pup_pdn_cntrl(int pin, int val);

#endif // GPIO_H