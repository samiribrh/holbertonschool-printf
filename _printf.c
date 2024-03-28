#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>

int _printf(const char *format, ...)
{
	va_list arg;
	int len = 0, i = 0, ispercent, isescape, lenstr;
	char crntchar, *crntstring;

	va_start(arg, format);
	while (format[i])
	{
		ispercent = format[i] == '%';
		isescape = format[i] == '\\';
		if (ispercent && format[i + 1] == 'c')
		{
			crntchar = (char)va_arg(arg, int);
			write(1, &crntchar, 1), i += 2, len++;
		}
		else if (ispercent && format[i + 1] == 's')
		{
			crntstring = va_arg(arg, char*);
			if (crntstring == NULL)
				write(1, "(null)", 6), i += 2, len += 6;
			else
			{
				for (lenstr = 0; crntstring[lenstr]; lenstr++)
					;
				write(1, crntstring, lenstr), i += 2, len += lenstr;
			}
		}
		else if (ispercent && format[i + 1] == '%')
		{
			crntchar = '%';
			write(1, &crntchar, 1), i += 2, len++;
		}
		else if (isescape && format[i + 1] == 'n')
		{
			crntchar = '\n';
			write(1, &crntchar, 1), i += 2, len++;
		}
		else if (isescape && format[i + 1] == '\\')
		{
			crntchar = '\\';
			write(1, &crntchar, 1), i += 2, len++;
		}
		else
			write(1, &format[i], 1), i++, len++;
	}
    va_end(arg);
    return len;
}
