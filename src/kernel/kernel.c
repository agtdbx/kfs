#include "define.h"
#include "colors.h"
#include "libs/libstr.h"
#include "terminal/terminal.h"
#include "inputs/keyboard.h"

void	kmain(void)
{
	const char *str = "42 kfs\n\nYou can tell you impressed :)\n42";
	t_terminal	terminal = terminal_init(create_color(FG_WHITE, BG_BLACK));
	t_keyboard	keyboard = keyboard_init();
	t_key_event	key_event;

	terminal_clear(&terminal);

	// // Write the string to video memory
	terminal_putstring(&terminal, str);

	// Infinite loop to keep the kernel running
	while (1) {
		if (keyboard_poll(&keyboard, &key_event))
		{
			if (key_event.type == KEY_PRESS && key_event.ascii != '\0')
				terminal_putchar(&terminal, key_event.ascii);
		}
	}
}

