#include <uranos/kernel.h>
#include <uranos/console.h>
#include <uranos/string.h>		/* strlen */

#include <stdarg.h>

int kprintf(const char* str, ...)
{
	if(!str)
	{
		return -1;
	}

	/* Start variable array, get length of the input */
	unsigned len = strlen(str);
	va_list ap;
	va_start(ap, str);

	/* Go through the input */
	for(int i = 0; i < len; i++)
	{
		if(str[i] == '%')
		{
			switch(str[i+1])
			{
				case 'd':
				{
					int d = va_arg(ap, int);
					char buf[16] = {0};
					//itoa(d, buf, 10);
					//terminal->puts(buf);
					break;
				}
				case 'x':
				{
					int d = va_arg(ap, int);
					char buf[16] = {0};
					//itoa(d, buf, 16);
					//terminal->puts(buf);
					break;
				}
				case 's':
				{
					char* s = va_arg(ap, char*);
					if(s)
						s = NULL;
						//terminal->puts(s);
					else
						s = NULL;
						//terminal->puts("null");
					break;
				}
				default:
				{
					break;
				}
			}
			i++;
		}
		/* If the input is not a format */
		else
		{
			int a = 1;
			// terminal_putc(str[i]);
		}
	}
	va_end(ap);
	// TODO: fix len to actually mean outputted length
	return len;
}