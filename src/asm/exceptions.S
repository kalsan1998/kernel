#include "vector_table.S"

.global init_vector_table_el3
init_vector_table_el3:
    ldr x0, =vector_table
    msr vbar_el3, x0
    ret

.global current_el
current_el:
    mrs x0, currentel
	and x0, x0, #12		// Only bits 3 and 4 are relevant
	lsr x0, x0, #2		// Shift those bits right
	ret

.global exception_class_el3
exception_class_el3:
    mrs x0, esr_el3
    lsr x0, x0, #26     // Want bits [26,31]
    and x0, x0, #32
    ret
    
.global fault_status_code_el3
fault_status_code_el3:
    mrs x0, esr_el3
    and x0, x0, #63     // Bits [0,5]
    ret

.global fault_address_el3
fault_address_el3:
    mrs x0, far_el3     // 64bit
    ret

.global instruction_fault_address
instruction_fault_address:
    mrs x0, far_el2
    and x0, x0, #0xffffffff // First 32 bits
    ret

.global data_fault_address
data_fault_address:
    mrs x0, far_el2
    lsr x0, x0, #32     // Last 32 bits
    ret