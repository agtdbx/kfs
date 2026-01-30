#include "printk.h"

static const char	*NUMBER_BASE = "0123456789abcdef";

static void	print_number(t_terminal *terminal, int32_t number, int32_t base);
static void	print_unsigned_number(t_terminal *terminal, uint32_t number, uint32_t base);

void	printk(t_terminal *terminal, const char *str, ...)
{
	if (!terminal || !str) // Safety check
		return ;

	va_list	args;
	int		i = 0;

	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%' && str[i + 1] != '\0')
		{
			i++;
			if (str[i] == 'c') // Char
				terminal_putchar(terminal, va_arg(args, int));
			else if (str[i] == 's') // String
				terminal_putstring(terminal, (char *)va_arg(args, int *));
			else if (str[i] == 'i') // Integer
				print_number(terminal, va_arg(args, int), 10);
			else if (str[i] == 'u') // Unsigned integer
				print_number(terminal, va_arg(args, unsigned int), 10);
			else if (str[i] == 'h') // Integer in base 16
				print_number(terminal, va_arg(args, int), 16);
			else if (str[i] == 'o') // Integer in base 8
				print_number(terminal, va_arg(args, int), 8);
			else if (str[i] == 'b') // Interger in base 2
				print_number(terminal, va_arg(args, int), 2);
			else
			{
				terminal_putchar(terminal, '%');
				terminal_putchar(terminal, str[i]);
			}
		}
		else
			terminal_putchar(terminal, str[i]);
		i++;
	}
	va_end(args);
}


static void	print_number(t_terminal *terminal, int32_t number, int32_t base)
{
	// Check base size
	if (base < 2)
		base = 2;
	if (base > 16)
		base = 16;

	// Safety check of min int32
	if (number == -2147483648)
	{
		terminal_putstring(terminal, "-2147483648");
		return ;
	}

	// Print - if number is negative
	if (number < 0)
	{
		terminal_putchar(terminal, '-');
		number *= -1;
	}

	// If number is greater than base, print previous char before
	if (number >= base)
		print_number(terminal, number / base, base);

	terminal_putchar(terminal, NUMBER_BASE[number % base]);
}


static void	print_unsigned_number(t_terminal *terminal, uint32_t number, uint32_t base)
{
	if (base > 16)
		base = 16;

	if (number >= base)
		print_unsigned_number(terminal, number / base, base);

	terminal_putchar(terminal, NUMBER_BASE[number % base]);
}
