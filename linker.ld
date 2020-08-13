SECTIONS
{
	. = 0x0000000000001000;
    .text.boot : {*(.text.boot) }
    . = ALIGN(0x1000);
    .text : { *(.text) }
    .rodata : { *(.rodata) }
    .data : { *(.data) }
	. = ALIGN(0x8);
	bss_start = .;
	.bss : { *(.bss*) } 
	bss_end = .;
	. = ALIGN(0x00001000);
	__pt_dir_start = .;

   /DISCARD/ : { *(.comment) *(.gnu*) *(.note*) *(.eh_frame*) }
}
