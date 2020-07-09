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

.global fault_status_code_el3
fault_status_code_el3:
    mrs x0, esr_el3
    and x0, x0, #63     // Bits [0,5]
    ret

