#include <uranos/console.h>

#include <uranos/vga.h>


/* This is the main console that is being used, we may use many consoles in the future */
static console_t* console;

char console_getc(void)
{
	return console->getc();
}

void console_putc(const char c)
{
	console->putc(c);
	return;
}

void console_puts(const char* str)
{
	while(str)
		console_putc(*str++);
	return;
}

void console_clear(void)
{
	console->clear();
	return;
}


int console_init(void)
{
	/* TODO: still ugly!!! */
	console = vga_get_console();
	console_clear();
	return 0;
}