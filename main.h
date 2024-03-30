#ifndef MAIN_H_
#define MAIN_H_

int _printf(const char *format, ...);
void write_char(int *len, char c);
void write_str(int *len, char *str);

typedef struct typeconverter {
	char *ltr;
	void (*func)(int *len, va_list);
} ltr_func;
#endif
