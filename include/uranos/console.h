#ifndef __URANOS_CONSOLE_HH
#define __URANOS_CONSOLE_HH

typedef struct {
	void (*putc)(char);
	char (*getc)(void);
  void (*clear)(void);
} console_t;

char console_getc(void);
void console_puts(const char* str);
void console_putc(const char c);
void console_clear(void);

int console_init(void);

#endif