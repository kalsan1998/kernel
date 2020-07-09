.balign 0x800 // Each table has 16 entries, each entry is 128 bytes (16 instructions)

// Taken from
// https://developer.arm.com/documentation/100933/0100/AArch64-exception-vector-table?lang=en

vector_table:
curr_el_sp0_sync:        // The exception handler for a synchronous 
    bl handle_exception  // exception from the current EL using SP0.

.balign 0x80
curr_el_sp0_irq:         // The exception handler for an IRQ exception
    bl handle_exception  // from the current EL using SP0.

.balign 0x80
curr_el_sp0_fiq:         // The exception handler for an FIQ exception
    bl handle_exception  // from the current EL using SP0.

.balign 0x80
curr_el_sp0_serror:      // The exception handler for a System Error 
    bl handle_exception  // exception from the current EL using SP0.

.balign 0x80
curr_el_spx_sync:        // The exception handler for a synchrous 
    bl handle_exception  // exception from the current EL using the
                         // current SP.
.balign 0x80
curr_el_spx_irq:         // The exception handler for an IRQ exception from 
    bl handle_exception  // the current EL using the current SP.

.balign 0x80
curr_el_spx_fiq:         // The exception handler for an FIQ from 
    bl handle_exception  // the current EL using the current SP.

.balign 0x80
curr_el_spx_serror:      // The exception handler for a System Error 
    bl handle_exception  // exception from the current EL using the
                         // current SP.

.balign 0x80
lower_el_aarch64_sync:   // The exception handler for a synchronous 
    bl handle_exception  // exception from a lower EL (AArch64).

.balign 0x80
lower_el_aarch64_irq:    // The exception handler for an IRQ from a lower EL
    bl handle_exception  // (AArch64).

.balign 0x80
lower_el_aarch64_fiq:    // The exception handler for an FIQ from a lower EL
    bl handle_exception  // (AArch64).

.balign 0x80
lower_el_aarch64_serror: // The exception handler for a System Error 
    bl handle_exception  // exception from a lower EL(AArch64).

.balign 0x80
lower_el_aarch32_sync:   // The exception handler for a synchronous 
    bl handle_exception  // exception from a lower EL(AArch32).

.balign 0x80
lower_el_aarch32_irq:    // The exception handler for an IRQ exception 
    bl handle_exception  // from a lower EL (AArch32).

.balign 0x80
lower_el_aarch32_fiq:    // The exception handler for an FIQ exception from 
    bl handle_exception  // a lower EL (AArch32).

.balign 0x80
lower_el_aarch32_serror: // The exception handler for a System Error
    bl handle_exception  // exception from a lower EL(AArch32).