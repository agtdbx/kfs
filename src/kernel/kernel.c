#include "define.h"
#include "colors.h"
#include "libs/libstr.h"
#include "terminal/terminal.h"
#include "inputs/keyboard.h"

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
	uint8_t	scancode = 0;
	while (1) {
		if (keyboard_poll(&scancode))
		{
			if ((scancode & KEY_UP_MASK) != KEY_UP_MASK)
				terminal_putchar(&terminal, scancode_to_char(scancode));
		}
	}
}

