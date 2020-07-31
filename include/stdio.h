#ifndef STDIO_H
#define STDIO_H

#include <stdint.h>

void print_char(char c);
char read_char(void);

void print_string(const char *s);
void print_int(int64_t n);

void print_hex(uint64_t n, int nybbles);

#endif // STDIO_H