ENTRY(_start)
SECTIONS
{
	/* Instead of having kernel living in 1MiB, we put it to 3GiB+1MiB this time */
	. = 0xC0100000;
	_begin_link = .;
	/* Add symbols for memory regions */
	_begin_text = .;
	.text ALIGN (4K) : AT (ADDR (.text) - 0xC0000000)
	{
		*(.multiboot)
		*(.text)
	}
	_end_text = .;
	_begin_rodata = .;
	.rodata ALIGN (4K) : AT (ADDR (.rodata) - 0xC0000000)
	{
		*(.rodata)
		*(.rodata.*)
	}
	_end_rodata = .;
	_begin_data = .;
	.data ALIGN (4K) : AT (ADDR (.data) - 0xC0000000)
	{
		*(.data)
	}
	_end_data = .;
	_begin_bss = .;
	.bss ALIGN (4K) : AT (ADDR (.bss) - 0xC0000000)
	{
		*(COMMON)
		*(.bss)
		*(.early_stack)
	}
	_end_bss = .;
	_end_link = .;
}