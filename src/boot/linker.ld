ENTRY (_start) /* label to load in booyloader */

/* define of sections */
SECTIONS
{
	/* text section begin at 0x100000 */
	/* section for executable, read-only */
	. = 0x100000;
	.text : {
		*(.multiboot)
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
		. += 0x1000; /* 4 Kb */
		_sys_stack_top = .;
	}
}
