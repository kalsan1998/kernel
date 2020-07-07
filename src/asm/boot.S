.section ".text.boot"
 
.globl _start
 
_start:
	mrs	x0, mpidr_el1		
	and	x0, x0,#0xFF		// Check processor id
	cbz	x0, 2f		// Hang for all non-primary CPU
	b	halt
 
    // set stack before our code
2: ldr     x5, =_start
    mov     sp, x5

    // clear bss
    ldr     x5, =__bss_start
    ldr     w6, =__bss_size
3:  cbz     w6, 4f
    str     xzr, [x5], #8
    sub     w6, w6, #1
    cbnz    w6, 3b
 
    // jump to C code, should not return
4:  bl      main
    b halt

halt:
	wfe
	b halt