#include "exceptions.h"

#include <stdint.h>

#include "stdio.h"

// Fault status codes
#define ADDR_SIZE_FAULT 0x00
#define TRANSLATION_FAULT_EL1 0x05
#define TRANSLATION_FAULT_EL2 0x06
#define TRANSLATION_FAULT_EL3 0x07
#define ACCESS_FLAG_FAULT_EL1 0x09
#define ACCESS_FLAG_FAULT_EL2 0x0a
#define ACCESS_FLAG_FAULT_EL3 0x0b
#define PERMISSION_FAULT_EL1 0x0d
#define PERMISSION_FAULT_EL2 0x0e
#define PERMISSION_FAULT_EL3 0x0f
#define SYNC_EXTERNAL_ABORT 0x10
#define SYNC_EXTERNAL_ABORT_ON_TRANSLATION_TABLE_WALK_EL1 0x15
#define SYNC_EXTERNAL_ABORT_ON_TRANSLATION_TABLE_WALK_EL2 0x16
#define SYNC_EXTERNAL_ABORT_ON_TRANSLATION_TABLE_WALK_EL3 0x17
#define SYNC_PARITY_ERR_ON_MEM_ACCESS 0x18
#define SYNC_PARITY_ERR_ON_MEM_ACCESS_ON_TRANSLATION_TABLE_WALK_EL1 0x1d
#define SYNC_PARITY_ERR_ON_MEM_ACCESS_ON_TRANSLATION_TABLE_WALK_EL2 0x1e
#define SYNC_PARITY_ERR_ON_MEM_ACCESS_ON_TRANSLATION_TABLE_WALK_EL3 0x1f
#define ALIGNMENT_FAULT 0x21
#define DEBUG_EVENT 0x22

// Exception classes
#define UNKNOWN_EC 0x00
#define ILLEGAL_EXECUTION_STATE 0x0e
#define INSTR_ABORT_LOWER_EL 0x20
#define INSTR_ABORT_SAME_EL 0x21
#define PC_ALIGNMENT_FAULT 0x22
#define DATA_ABORT_LOWER_EL 0x24
#define DATA_ABORT_SAME_EL 0x25
#define SP_ALIGNMENT_FAULT 0x26
#define FLOAT_POINT_64 0x2c
#define SERROR_INTERRUPT 0x2f

extern int exception_class_el1(void);
extern int fault_status_code_el1(void);
extern uint64_t fault_address_el1(void);
extern uint64_t instruction_link_el1(void);

void handle_exception(void)
{
    print_string("-- Handling Exception -- \r\n");
    print_current_exception_level();
    uint64_t fault_address = fault_address_el1();
    uint64_t instruction_address = instruction_link_el1();
    int exception_class = exception_class_el1();
    int fault_status = fault_status_code_el1();

    print_string("Instruction Address: ");
    print_hex(instruction_address, 8);
    print_string("\r\n");

    print_string("Fault Address: ");
    print_hex(fault_address, 8);
    print_string("\r\n");

    print_string("Exception Class: ");
    print_hex(exception_class, 2);
    print_string(" - ");
    switch (exception_class)
    {
    case UNKNOWN_EC:
        print_string("Unknown\r\n");
        break;
    case ILLEGAL_EXECUTION_STATE:
        print_string("Illegal Execution State\r\n");
        break;
    case INSTR_ABORT_LOWER_EL:
        print_string("Instruction Abort From Lower Level\r\n");
        break;
    case INSTR_ABORT_SAME_EL:
        print_string("Instruction Abort From Current Level\r\n");
        break;
    case PC_ALIGNMENT_FAULT:
        print_string("PC Alignment Fault\r\n");
        break;
    case SP_ALIGNMENT_FAULT:
        print_string("SP Alignment Fault\r\n");
        break;
    case SERROR_INTERRUPT:
        print_string("SError Interrupt\r\n");
        break;
    default:
        print_string("Not Handled\r\n");
    }

    print_string("Fault Status Code: ");
    print_hex(fault_status, 2);
    print_string(" - ");
    switch (fault_status)
    {
    case ADDR_SIZE_FAULT:
        print_string("Address Size Fault\r\n");
        break;
    case ALIGNMENT_FAULT:
        print_string("Alignment Fault\r\n");
        break;
    default:
        print_string("Not Handled\r\n");
    }
    print_string("--------\r\n");
}

void print_current_exception_level(void)
{
    int el = current_el();
    print_string("Current Exception Level: ");
    switch (el)
    {
    case 0:
        print_string("EL0 -- Applications\r\n");
        break;
    case 1:
        print_string("EL1 -- OS kernel functions (privileged)\r\n");
        break;
    case 2:
        print_string("EL2 -- Hypervisor\r\n");
        break;
    case 3:
        print_string("EL3 -- Secure monitor\r\n");
        break;
    default:
        print_string("EL");
        print_int(el);
        print_string("-- Unknown\r\n");
    }
}

void force_exception(void)
{
    print_string("Forcing exception\r\n");
    print_string("--------\r\n");
    // Unaligned access
    volatile int what = *((uint64_t *)0x03);
    // asm volatile("svc #0");
    // svc: EL0 -> EL1
    // hvc: EL1 -> EL2
    // smc: EL1/EL2 -> EL3
}
