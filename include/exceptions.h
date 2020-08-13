#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#define SCTRL_RES1 (3 << 28) | (3 << 22) | (1 << 20) | (1 << 11)
#define SCTRL_VALUE SCTRL_RES1

#define HCR_AARCH64_EL1 (1 << 31)
#define HCR_VALUE HCR_AARCH64_EL1

#define SCR_RES1 (3 << 4)
#define SCR_AARCH64_EL1 (1 << 10)
#define SCR_NS (1 << 0) // ELs lower than EL3 are in Non-secure state
#define SCR_VALUE (SCR_RES1 | SCR_AARCH64_EL1 | SCR_NS)

#define SPSR_SERROR_MASK (1 << 8)
#define SPSR_IRQ_MASK (1 << 7)
#define SPSR_FIQ_MASK (1 << 6)
#define SPSR_EL1h (5 << 0) // Use SP1
#define SPSR_VALUE (SPSR_SERROR_MASK | SPSR_IRQ_MASK | SPSR_FIQ_MASK | SPSR_EL1h)

#ifndef ASSEMBLER

#include "stdint.h"

extern int current_el(void);
extern void init_vector_tables(void);
extern void el3_to_el1(void);

void handle_execption(uint64_t lr);
void force_exception(void);

void print_current_exception_level(void);

#endif

#endif // EXCEPTIONS_H