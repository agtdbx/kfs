#include "define.h"
#include "colors.h"
#include "libs/libstr.h"
#include "terminal/terminal.h"
#include "inputs/keyboard.h"

void	kmain(void)
{
	//Init keyboard
	t_keyboard	keyboard = keyboard_init();

	// Init terminal
	t_terminal	terminal = terminal_init(create_color(FG_WHITE, BG_BLACK));

	terminal_putstring(&terminal, "42");
	terminal_flush(&terminal);

	// Infinite loop to keep the kernel running
	t_key_event	key_event;
	while (1)
	{
		if (keyboard_poll(&keyboard, &key_event))
		{
			if (key_event.type == KEY_PRESS)
			{
				// Write characters
				if (key_event.ascii != '\0')
				{
					terminal_putchar(&terminal, key_event.ascii);
					terminal_flush(&terminal);
				}
				else if (key_event.key == K_ENTER)
				{
					terminal_putchar(&terminal, '\n');
					terminal_flush(&terminal);
				}
				else if (key_event.key == K_TAB)
				{
					terminal_putchar(&terminal, '\t');
					terminal_flush(&terminal);
				}

				// Remove characters
				else if (key_event.key == K_BACKSPACE)
				{
					terminal_remove_char(&terminal);
					terminal_flush(&terminal);
				}
				else if (key_event.key == K_DELETE)
				{
					terminal_delete_char(&terminal);
					terminal_flush(&terminal);
				}

				// Move cursor
				else if (key_event.key == K_LEFT)
					terminal_cursor_left(&terminal);
				else if (key_event.key == K_RIGHT)
					terminal_cursor_right(&terminal);
				else if (key_event.key == K_UP)
					terminal_cursor_up(&terminal);
				else if (key_event.key == K_DOWN)
					terminal_cursor_down(&terminal);
				else if (key_event.key == K_HOME)
					terminal_cursor_start(&terminal);
				else if (key_event.key == K_END)
					terminal_cursor_end(&terminal);
			}
		}
	}
}


