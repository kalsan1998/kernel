#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

extern int current_el(void);
extern void init_vector_tables(void);
extern void el3_to_el1(void);

void handle_execption(void);
void force_exception(void);

void print_current_exception_level(void);

#endif // EXCEPTIONS_H