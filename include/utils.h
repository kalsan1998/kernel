#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>

#define PERIPHERAL_BASE = 0xfe000000

extern void branch_to_address(void *);

uint32_t get32(uint32_t addr);
void put32(uint32_t addr, uint32_t val);
uint64_t get64(uint64_t addr);
void put64(uint64_t addr, uint64_t val);

int read32(void);
void write32(int);

#endif // UTILS_H
