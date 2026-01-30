#include "printk.h"

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
				terminal_putstring(terminal, va_arg(args, int *));
			// else if (str[i] == 'i') // Integer
			// else if (str[i] == 'u') // Unsigned integer
			// else if (str[i] == 'p') // Pointer
			// else if (str[i] == 'b') // Interger as bit
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

