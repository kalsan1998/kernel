#include "vector_table.S"
#include "exceptions.h"

.global init_vector_tables
init_vector_tables:
    ldr x0, =vector_table
    msr vbar_el3, x0
    msr vbar_el2, x0
    msr vbar_el1, x0
    ret

.global current_el
current_el:
    mrs x0, currentel	// Only bits 3 and 4 are relevant
	lsr x0, x0, #2		// Shift those bits right
	ret

.global exception_class_el1
exception_class_el1:
    mrs x0, esr_el1
    lsr x0, x0, #26     // Want bits [26,31]
    and x0, x0, #32
    ret
    
.global fault_status_code_el1
fault_status_code_el1:
    mrs x0, esr_el1
    and x0, x0, #63     // Bits [0,5]
    ret

.global instruction_link_el1
instruction_link_el1:
    mrs x0, elr_el1
    ret

.global fault_address_el1
fault_address_el1:
    mrs x0, far_el1     // 64bit
    ret

.global el3_to_el1
el3_to_el1:
    ldr x0, =SCTRL_VALUE // Everything disabled
    msr sctlr_el1, x0

    ldr x0, =HCR_VALUE
    msr hcr_el2, x0

    ldr x0, =SCR_VALUE
    msr scr_el3, x0

    ldr x0, =SPSR_VALUE
    msr spsr_el3, x0

	// Set a stack pointer for EL1
	mov x0, #0x400000 // 4MB
    msr sp_el1, x0 

    adr x0, el1_entry
    msr elr_el3, x0 // Address to return to after eret
    
    eret
