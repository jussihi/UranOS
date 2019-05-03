#include <uranos/vga.h>

#include <stdint.h>

#define VGA_START 0xC03FF000
#define VGA_END   0xC0407000
#define VGA_WIDTH  80
#define VGA_HEIGHT 25

static int x;
static int y;

static uint16_t vga_create_char(char _c)
{
  uint16_t c = (uint16_t)_c;
  return c | (0x0F) << 8;
}

static void vga_putc(char c)
{
    return;
}

/* Do we even need this? We get the input from the keyboard driver... */
static char vga_getc(void)
{
    return 'a';
}

static void vga_clear(void)
{
	for(y  = 0; y < VGA_HEIGHT; y++)
	{
		for(x = 0; x < VGA_WIDTH; x++)
		{
			*(uint16_t*)(VGA_START + (y * 2 * VGA_WIDTH + x * 2)) = vga_create_char(' ');
		}
	}
	x = 0;
	y = 0;
}

console_t vga_console = {
    .putc = vga_putc,
    .getc = vga_getc,
    .clear = vga_clear
};

console_t* vga_get_console(void)
{
	return &vga_console;
}
