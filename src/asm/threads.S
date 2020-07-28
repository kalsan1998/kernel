
.global context_switch
context_switch:
    // x0 is curr thread struct addr
    // x1 is next thread struct addr

    mov x3, sp

	stp	x19, x20, [x0], #16		// store callee-saved registers
	stp	x21, x22, [x0], #16
	stp	x23, x24, [x0], #16
	stp	x25, x26, [x0], #16
	stp	x27, x28, [x0], #16
	stp	x29, x30, [x0], #16
	str	x3, [x0]

    ldp	x19, x20, [x1], #16		// restore callee-saved registers
	ldp	x21, x22, [x1], #16
	ldp	x23, x24, [x1], #16
	ldp	x25, x26, [x1], #16
	ldp	x27, x28, [x1], #16
	ldp	x29, x30, [x1], #16
	ldr	x3, [x1]

    mov sp, x3
    ret // returns to x30


.global new_thread_start
new_thread_start:
    mov x0, x20
    blr x19
