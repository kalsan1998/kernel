.macro	save_registers
	stp	x0, x1, [sp, #-16]!
	stp	x2, x3, [sp, #-16]!
	stp	x4, x5, [sp, #-16]!
	stp	x6, x7, [sp, #-16]!
	stp	x8, x9, [sp, #-16]!
	stp	x10, x11, [sp, #-16]!
	stp	x12, x13, [sp, #-16]!
	stp	x14, x15, [sp, #-16]!
	stp	x16, x17, [sp, #-16]!
	stp	x18, x19, [sp, #-16]!
	stp	x20, x21, [sp, #-16]!
	stp	x22, x23, [sp, #-16]!
	stp	x24, x25, [sp, #-16]!
	stp	x26, x27, [sp, #-16]!
	stp	x28, x29, [sp, #-16]!
	str	x30, [sp, #-16]!
.endm

.macro	load_registers
	ldr	x30, [sp], #16 
	ldp	x28, x29, [sp], #16
	ldp	x26, x27, [sp], #16
	ldp	x24, x25, [sp], #16
	ldp	x22, x23, [sp], #16
	ldp	x20, x21, [sp], #16
	ldp	x18, x19, [sp], #16
	ldp	x16, x17, [sp], #16
	ldp	x14, x15, [sp], #16
	ldp	x12, x13, [sp], #16
	ldp	x10, x12, [sp], #16
	ldp	x8, x9, [sp], #16
	ldp	x6, x7, [sp], #16
	ldp	x4, x5, [sp], #16
	ldp	x2, x3, [sp], #16
	ldp	x0, x1, [sp], #16
.endm

.balign 0x800 // Each table has 16 entries, each entry is 128 bytes (16 instructions)

// Taken from
// https://developer.arm.com/documentation/100933/0100/AArch64-exception-vector-table?lang=en

vector_table:
curr_el_sp0_sync:        // The exception handler for a synchronous 
    b begin_exception    // exception from the current EL using SP0.

.balign 0x80
curr_el_sp0_irq:         // The exception handler for an IRQ exception
    b begin_exception    // from the current EL using SP0.

.balign 0x80
curr_el_sp0_fiq:         // The exception handler for an FIQ exception
    b begin_exception    // from the current EL using SP0.

.balign 0x80
curr_el_sp0_serror:      // The exception handler for a System Error 
    b begin_exception    // exception from the current EL using SP0.

.balign 0x80
curr_el_spx_sync:        // The exception handler for a synchrous 
    b begin_exception    // exception from the current EL using the
                         // current SP.
.balign 0x80
curr_el_spx_irq:         // The exception handler for an IRQ exception from 
    b  begin_irq         // the current EL using the current SP.

.balign 0x80
curr_el_spx_fiq:         // The exception handler for an FIQ from 
    b begin_exception    // the current EL using the current SP.

.balign 0x80
curr_el_spx_serror:      // The exception handler for a System Error 
    b begin_exception    // exception from the current EL using the
                         // current SP.

.balign 0x80
lower_el_aarch64_sync:   // The exception handler for a synchronous 
    b begin_exception    // exception from a lower EL (AArch64).

.balign 0x80
lower_el_aarch64_irq:    // The exception handler for an IRQ from a lower EL
    b begin_exception    // (AArch64).

.balign 0x80
lower_el_aarch64_fiq:    // The exception handler for an FIQ from a lower EL
    b begin_exception    // (AArch64).

.balign 0x80
lower_el_aarch64_serror: // The exception handler for a System Error 
    b begin_exception    // exception from a lower EL(AArch64).

.balign 0x80
lower_el_aarch32_sync:   // The exception handler for a synchronous 
    b begin_exception    // exception from a lower EL(AArch32).

.balign 0x80
lower_el_aarch32_irq:    // The exception handler for an IRQ exception 
    b begin_exception    // from a lower EL (AArch32).

.balign 0x80
lower_el_aarch32_fiq:    // The exception handler for an FIQ exception from 
    b begin_exception    // a lower EL (AArch32).

.balign 0x80
lower_el_aarch32_serror: // The exception handler for a System Error
    b begin_exception    // exception from a lower EL(AArch32).

begin_exception:
    save_registers
    bl handle_exception
	mrs x0, elr_el1
	add x0, x0, #4
	msr elr_el1, x0
    load_registers
    eret

begin_irq:
    save_registers
    bl handle_irq
    load_registers
    eret
