#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>

#define PERIPHERAL_BASE = 0xfe000000

extern void branch_to_address(void *);

void put32(uint32_t addr, uint32_t val);
uint32_t get32(uint32_t addr);

int read32(void);
void write32(int);

#endif // UTILS_H
