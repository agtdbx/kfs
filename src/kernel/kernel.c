#include "define.h"
#include "colors.h"
#include "libs/libstr.h"
#include "terminal/terminal.h"

void	kmain(void)
{
	const char *str = "42 kfs\n\nYou can tell you impressed :)";
	t_terminal	terminal = terminal_init(COLOR_LIGHT_GREY);

	terminal_clear(&terminal);

	// Write the string to video memory
	terminal_putstring(&terminal, str);

	// Infinite loop to keep the kernel running
	while (1) {}
}

