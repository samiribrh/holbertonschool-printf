#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>

/**
 * write_char - Writes the given char.
 * @len: Length of the char in _printf func.
 * @c: Char to be printed.
 *
 * Return: void.
*/
void write_char(int *len, char c)
{
	write(1, &c, 1);
	(*len)++;
}

/**
 * write_str - Writes the given string.
 * @len: Length of the chars in _printf func.
 * @str: String to be printed
 *
 * Return: void.
 */
void write_str(int *len, char *str)
{
	int lenstr;

	if (str == NULL)
	{
		write(1, "(null)", 6);
		*len += 6;
	}
	else
	{
		for (lenstr = 0; str[lenstr]; lenstr++)
			;
		write(1, str, lenstr);
		*len += lenstr;
	}
}

/**
 * write_int - Writes the given integer.
 * @len: Length of the chars in _printf func.
 * @num: Integer to be printed
 *
 * Return: void.
 */
void write_int(int *len, int num)
{
	int divisor = 1, temp = num;
	char digit;

	if (num < 0)
	{
		write_char(len, '-');
		temp = -num;
	}

	while (temp / divisor >= 10)
		divisor *= 10;

	while (divisor != 0)
	{
		digit = '0' + temp / divisor;
		write_char(len, digit);
		temp %= divisor;
		divisor /= 10;
	}
}

/**
 * _printf - Prints the given format with variables.
 * @format: Main format
 *
 * Return: Number of the chars printed.
 */
int _printf(const char *format, ...)
{
	va_list arg;
	int len = 0, i = 0;
	char crntchar, *crntstring;

	va_start(arg, format);
	while (format[i])
	{
		if (format[i] == '%')
			switch (format[i + 1])
			{
				case 'c':
					crntchar = (char)va_arg(arg, int);
					write_char(&len, crntchar), i += 2;
					break;
				case 's':
					crntstring = va_arg(arg, char*);
					write_str(&len, crntstring), i += 2;
					break;
				case 'd':
				case 'i':
					write_int(&len, va_arg(arg, int));
					i += 2;
					break;
				case '%':
					write_char(&len, '%'), i += 2;
					break;
				case '\0':
					continue;
				default:
					write_char(&len, format[i]), i++;
					break;
			}
		else
			write_char(&len, format[i]), i++;
	}
	va_end(arg);
	return (len);
}
