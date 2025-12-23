#include "define.h"
#include "colors.h"
#include "libs/libstr.h"
#include "terminal/terminal.h"

void	kmain(void)
{
	const char *str = "42 kfs\n\nYou can tell you impressed :)\n42";
	t_terminal	terminal = terminal_init(create_color(FG_WHITE, BG_BLACK));

	terminal_clear(&terminal);

	// Write the string to video memory
	terminal_putstring(&terminal, str);

	// Move cursor, then write enough to need a scroll
	ternimal_set_cursor(&terminal, 0, 24);
	terminal_putstring(&terminal, "test-abcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcde !");

	// Infinite loop to keep the kernel running
	while (1) {}
}

