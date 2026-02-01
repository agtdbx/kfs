ENTRY (_start) /* label to load in booyloader */

/* define of sections */
SECTIONS
{
	/* multiboot section begin at 0x100 */
	/* section for boot, read-only */
	. = 0x100;
	.multiboot : {
		*(.multiboot)
	}

	/* put gdt section at 0x800 */
	. = 0x800;
	.gdt : {
		KEEP(*(.gdt))
	}

	/* text section begin at 0x100000 */
	/* section for executable, read-only */
	. = 0x100000;
	.text : {
		*(.text)
	}

	/* data section begin at 0x500000 */
	/* section for initialized data (variables), read-write */
	. = 0x500000;
	.data : {
		*(.data)
	}

	/* section begin at 0x600000 */
	/* section for uninitialized data (row memory), read-write */
	. = 0x600000;
	.bss : {
		*(.bss)
		/* Create the stack */
		_sys_stack = .;
		. += 0x4000; /* 16 Kb */
		_sys_stack_top = .;
	}
}
