#include "common.h"

void put(unsigned int addr, int val)
{
    *((volatile unsigned int *)addr) = val;
}

volatile unsigned int get(unsigned int addr)
{
    return *((volatile unsigned int *)addr);
}