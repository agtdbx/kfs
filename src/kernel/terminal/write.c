#include "terminal.h"
#include "../libs/libstr.h"

static void	_putchar(t_terminal *terminal, const char c);

void	terminal_putchar(t_terminal *terminal, const char c)
{
	_putchar(terminal, c);
	_update_cursor_pos(terminal->last_char_pos.x, terminal->last_char_pos.y);
}


void	terminal_putstring(t_terminal *terminal, const char *str)
{
	uint32_t	len = strlen(str);

	for (uint32_t i = 0; i < len; i++)
		_putchar(terminal, str[i]);
	_update_cursor_pos(terminal->last_char_pos.x, terminal->last_char_pos.y);
}



static void	_putchar(t_terminal *terminal, const char c)
{
	const uint32_t	char_id = strlen(terminal->buffer_char);

	if (c == '\n') // New line case
	{
		// Write char
		terminal->buffer_char[char_id] = c;
		terminal->buffer_color[char_id] = terminal->current_color;

		// Update line length
		terminal->lines_length[terminal->last_char_pos.y]++;
		// Update last char pos
		terminal->last_char_pos.x = 0;
		terminal->last_char_pos.y++;
	}
	else if (c == '\t') // Tab case
	{
		uint32_t	nb_space = TAB_SIZE - (terminal->last_char_pos.x % TAB_SIZE);

		if (terminal->last_char_pos.x + nb_space > TERMINAL_WIDTH) // Security for avoid tab go onto other line
			return ;

		// Write chars
		for (uint32_t i = 0; i < nb_space; i++)
		{
			terminal->buffer_char[char_id + i] = c;
			terminal->buffer_color[char_id + i] = terminal->current_color;
		}

		// Update line length
		terminal->lines_length[terminal->last_char_pos.y] += nb_space;
		// Update last char pos
		terminal->last_char_pos.x += nb_space;
	}
	else // Generic case
	{
		// Write char
		terminal->buffer_char[char_id] = c;
		terminal->buffer_color[char_id] = terminal->current_color;

		// Update line length
		terminal->lines_length[terminal->last_char_pos.y]++;
		// Update last char pos
		terminal->last_char_pos.x++;
	}

	// Change line check
	if (terminal->last_char_pos.x == TERMINAL_WIDTH)
	{
		terminal->last_char_pos.x = 0;
		terminal->last_char_pos.y++;
	}
	// Scroll check
	if (terminal->last_char_pos.y == TERMINAL_HEIGHT)
	{
		terminal->last_char_pos.x = 0;
		terminal_scroll_up(terminal);
	}
}
