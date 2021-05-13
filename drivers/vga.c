#include <uranos/vga.h>
#include <uranos/arch.h>
#include <uranos/string.h>

#include <stdint.h>


#define VGA_START 0xC03FF000
#define VGA_END   0xC0407000
#define VGA_WIDTH  80
#define VGA_HEIGHT 25

//    0xB8000


static int x;
static int y;

static void vga_update_cursor(void)
{
	uint16_t pos = y * VGA_WIDTH + x;
 
	outb(0x3D4, 0x0F);
	outb(0x3D5, (uint8_t) (pos & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));
	return;
}

static uint16_t vga_create_char(char _c)
{
  uint16_t c = (uint16_t)_c;
  return c | (0x0F) << 8;
}

static void vga_newline(void)
{
	// Scrolling down
	if(y == (VGA_HEIGHT-1))
	{
		memmove((void*)VGA_START, (void*)(VGA_START + (2 * VGA_WIDTH)), ((VGA_WIDTH * VGA_HEIGHT) - (VGA_WIDTH)) * 2);
		for(int i = 0; i < VGA_WIDTH; i++)
		{
			*(uint16_t*)(VGA_START + (y * 2 * VGA_WIDTH + i * 2)) = vga_create_char(' ');
		}
		x = 0;
		vga_update_cursor();
		return;
	}
	y++;
	x = 0;
	vga_update_cursor();
	return;
}

static void vga_putc(char c)
{
	if(c == '\n')
	{
		vga_newline();
		return;
	}

	*(uint16_t*)(VGA_START + (y * 2 * VGA_WIDTH + x * 2)) = vga_create_char(c);
	x++;
	if(x == VGA_WIDTH)
	{
		vga_newline();
	}
	vga_update_cursor();
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
	vga_update_cursor();
	return;
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
