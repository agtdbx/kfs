#include "terminal.h"
#include "../libs/libstr.h"

static void	_putchar(t_terminal *terminal, const char c);

void	terminal_putchar(t_terminal *terminal, const char c)
{
	_putchar(terminal, c);
	_update_cursor_pos(terminal->cursor_x, terminal->cursor_y);
}


void	terminal_putstring(t_terminal *terminal, const char *str)
{
	uint	len = strlen(str);

	for (uint i = 0; i < len; i++)
		_putchar(terminal, str[i]);
	_update_cursor_pos(terminal->cursor_x, terminal->cursor_y);
}



static void	_putchar(t_terminal *terminal, const char c)
{
	uint	char_id = (terminal->cursor_x + terminal->cursor_y * TERMINAL_WIDTH) * 2;

	if (c == '\b')
	{
		if (terminal->cursor_x == 0)
			return ;

		terminal->cursor_x--;
		char_id = (terminal->cursor_x + terminal->cursor_y * TERMINAL_WIDTH) * 2;
		terminal->addr[char_id] = ' ';
		terminal->addr[char_id + 1] = terminal->current_color;
	}
	else if (c == '\t')
	{
		int nb_space = 4 - (terminal->cursor_x % 4);

		for (int i = 0; i < nb_space; i++)
		{
			terminal->addr[char_id] = ' ';
			terminal->addr[char_id + 1] = terminal->current_color;
			terminal->cursor_x++;
			if (terminal->cursor_x == TERMINAL_WIDTH)
				break;
			char_id = (terminal->cursor_x + terminal->cursor_y * TERMINAL_WIDTH) * 2;
		}
	}
	else if (c == '\n')
	{
		terminal->addr[char_id] = ' ';
		terminal->addr[char_id + 1] = terminal->current_color;
	}
	else
	{
		terminal->addr[char_id] = c;
		terminal->addr[char_id + 1] = terminal->current_color;
		terminal->cursor_x++;
	}

	if (terminal->cursor_x == TERMINAL_WIDTH || c == '\n')
	{
		terminal->cursor_x = 0;
		terminal->cursor_y++;
	}
	if (terminal->cursor_y == TERMINAL_HEIGHT)
	{
		terminal->cursor_y--;
		terminal_scroll_up(terminal);
	}
}
