#include "exceptions.h"

#include "stdio.h"

void handle_exception(void)
{
    print_string("Handling exception\r\n");
    int fault_status = fault_status_code_el3();
    print_string("Fault Status Code: ");
    print_int(fault_status);
    print_string(" - ");
    switch (fault_status)
    {
    case ALIGNMENT_FAULT:
        print_string("Alignment Fault\r\n");
        break;
    default:
        print_string("Unknown\r\n");
    }
    print_string("--------\r\n");
    while (1)
    {
    }
}

int force_exception(void)
{
    print_string("Forcing exception\r\n");
    print_string("--------\r\n");
    // Unaligned access
    volatile int what = *((unsigned int *)0x03);
    return what;
}