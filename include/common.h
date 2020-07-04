#ifndef COMMON_H
#define COMMON_H

#define PERIPHERAL_BASE = 0xfe000000

void put(unsigned int addr, int val);
unsigned int get(unsigned int addr);

#endif // COMMON_H