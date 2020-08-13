#include "mm.h"
#include "virtual_memory.h"

.section ".text.boot"
 
.globl _start
 
_start:
    ldr     x5, =_start
    mov     sp, x5

    // clear bss
    ldr x0, =bss_start
    ldr x1, =bss_end
    sub x1, x1, x0
    bl memzero

    bl main
    b halt

halt:
	wfe
	b halt

.globl el1_entry
el1_entry:
	adr	x0, bss_start
	adr	x1, bss_end
	sub	x1, x1, x0
	bl 	memzero

	bl 	init_page_tables

//	mov	x0, #VA_START			
//	add	sp, x0, #LOW_MEMORY

	adrp	x0, __pt_dir_start				
	msr	ttbr1_el1, x0
	msr	ttbr0_el1, x0

	ldr	x0, =(TCR_VALUE)		
	msr	tcr_el1, x0

	ldr	x0, =(MAIR_VALUE)
	msr	mair_el1, x0
    ISB

	ldr	x2, =el1_main
    mrs x0, sctlr_el1
	orr	x0, x0, #1	// turn on			
	msr	sctlr_el1, x0
    ISB

    br x2
