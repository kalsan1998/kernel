#ifndef UTILS_H
#define UTILS_H

#define PERIPHERAL_BASE = 0xfe000000

extern void branch_to_address(void *);

void put(unsigned int addr, int val);
unsigned int get(unsigned int addr);

int read32(void);
void write32(int);

#endif // UTILS_H
