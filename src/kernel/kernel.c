#include "define.h"
#include "colors.h"
#include "libs/libstr.h"
#include "terminal/terminal.h"
#include "inputs/keyboard.h"
#include "printk/printk.h"

void	kmain(void)
{
	//Init keyboard
	t_keyboard	keyboard = keyboard_init();

	// Init terminal
	t_terminal	terminal1 = terminal_init(create_color(FG_WHITE, BG_BLACK), create_color(FG_WHITE, BG_DARK_GRAY));
	t_terminal	terminal2 = terminal_init(create_color(FG_WHITE, BG_BLACK), create_color(FG_WHITE, BG_DARK_GRAY));
	t_terminal	*active_terminal = &terminal1;
	uint8_t		active_terminal_id = 0;

	printk(active_terminal, "%i\n", 42);

	for (int i = 0; i < 300; i++)
	{
		if ((i % 80) == 79)
			terminal_putchar(active_terminal, 'a');
		else
			terminal_putchar(active_terminal, '#');
	}

	terminal_update_topbar(active_terminal);
	terminal_flush(active_terminal);

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
					terminal_putchar(active_terminal, key_event.ascii);
				else if (key_event.key == K_ENTER)
					terminal_putchar(active_terminal, '\n');
				else if (key_event.key == K_TAB)
				{
					if (keyboard.Lctrl)
					{
						if (active_terminal_id == 0)
						{
							active_terminal_id = 1;
							active_terminal = &terminal2;
						}
						else
						{
							active_terminal_id = 0;
							active_terminal = &terminal1;
						}
						terminal_update_cursor(active_terminal);
					}
					else
					{
						terminal_putchar(active_terminal, '\t');
					}
				}

				// Remove characters
				else if (key_event.key == K_BACKSPACE)
					terminal_remove_char(active_terminal);
				else if (key_event.key == K_DELETE)
				{
					if (keyboard.Lctrl)
						terminal_clear(active_terminal);
					else
						terminal_delete_char(active_terminal);
				}

				// Move cursor
				else if (key_event.key == K_LEFT)
					terminal_cursor_left(active_terminal);
				else if (key_event.key == K_RIGHT)
					terminal_cursor_right(active_terminal);
				else if (key_event.key == K_UP)
					terminal_cursor_up(active_terminal);
				else if (key_event.key == K_DOWN)
					terminal_cursor_down(active_terminal);
				else if (key_event.key == K_HOME)
				{
					if (keyboard.Lctrl)
						active_terminal->cursor.y = 1;
					terminal_cursor_start(active_terminal);
				}
				else if (key_event.key == K_END)
				{
					if (keyboard.Lctrl)
					{
						for (uint32_t y = active_terminal->cursor.y; y < TERMINAL_MAX_Y; y++)
							terminal_cursor_down(active_terminal);
					}
					terminal_cursor_end(active_terminal);
				}

				terminal_update_topbar(active_terminal);
				terminal_flush(active_terminal);
			}
		}
	}
}


