#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

extern int current_el(void);
extern void init_vector_table_el3(void);

void handle_execption(void);
int force_exception(void);

#endif // EXCEPTIONS_H