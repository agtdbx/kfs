#include "terminal.h"
#include "../libs/libstr.h"

static void	_putchar(t_terminal *terminal, const char c, const char color, bool insert);
static void	_move_chars_right(t_terminal *terminal, uint32_t pos_x, int32_t pos_y);
static void	_move_chars_left(t_terminal *terminal, uint32_t pos_x, int32_t pos_y);



void	terminal_putchar(t_terminal *terminal, const char c)
{
	_putchar(terminal, c, terminal->current_color, false);
	_update_cursor_pos(terminal->cursor.x, terminal->cursor.y);
}


void	terminal_putstring(t_terminal *terminal, const char *str)
{
	uint32_t	len = strlen(str);

	for (uint32_t i = 0; i < len; i++)
		_putchar(terminal, str[i], terminal->current_color, false);
	_update_cursor_pos(terminal->cursor.x, terminal->cursor.y);
}


void	terminal_write_putchar(t_terminal *terminal, const char c, const char color, bool insert)
{
	_putchar(terminal, c, color, insert);
	_update_cursor_pos(terminal->cursor.x, terminal->cursor.y);
}


void	terminal_write_putstring(t_terminal *terminal, const char *str, const char color, bool insert)
{
	uint32_t	len = strlen(str);

	for (uint32_t i = 0; i < len; i++)
		_putchar(terminal, str[i], color, insert);
	_update_cursor_pos(terminal->cursor.x, terminal->cursor.y);
}


void	terminal_remove_char(t_terminal *terminal)
{
	if (terminal->cursor.x == 0 && terminal->cursor.y == 0)
		return ;

	terminal->cursor.x--;
	if (terminal->cursor.x < 0)
	{
		terminal->cursor.y--;
		terminal->cursor.x = line_len(terminal->buffer_char[terminal->cursor.y]);
	}

	_move_chars_left(terminal, terminal->cursor.x, terminal->cursor.y);
	_update_cursor_pos(terminal->cursor.x, terminal->cursor.y);
}


void	terminal_delete_char(t_terminal *terminal)
{
	_move_chars_left(terminal, terminal->cursor.x, terminal->cursor.y);
	_update_cursor_pos(terminal->cursor.x, terminal->cursor.y);
}


static void	_putchar(t_terminal *terminal, const char c, const char color, bool insert)
{
	// If not insert, move all char before
	if (!insert)
		_move_chars_right(terminal, terminal->cursor.x, terminal->cursor.y);
		// TODO: Newline

	if (c == '\n') // New line case
	{
		// Write char and it's color
		terminal->buffer_char[terminal->cursor.y][terminal->cursor.x] = c;
		terminal->buffer_color[terminal->cursor.y][terminal->cursor.x] = color;

		// Update cursor pos
		terminal->cursor.x = 0;
		terminal->cursor.y++;
	}
	else if (c == '\t') // Tab case
	{
		uint32_t	nb_space = 4 - (terminal->cursor.x % 4);

		for (uint32_t i = 0; i < nb_space; i++)
			_putchar(terminal, ' ', color, insert);
	}
	else // Classic case
	{
		// Write char and it's color
		terminal->buffer_char[terminal->cursor.y][terminal->cursor.x] = c;
		terminal->buffer_color[terminal->cursor.y][terminal->cursor.x] = color;

		// Update cursor pos
		terminal->cursor.x++;
	}

	// Update cursor pos when end lines
	if (terminal->cursor.x == TERMINAL_WIDTH)
	{
		terminal->cursor.x = 0;
		terminal->cursor.y++;
	}
	if (terminal->cursor.y == TERMINAL_HEIGHT)
	{
		terminal->cursor.x = 0;
		terminal->cursor.y--;
		terminal_scroll_up(terminal);
	}
}


static void	_move_chars_right(t_terminal *terminal, uint32_t pos_x, int32_t pos_y)
{
	if (pos_x < 0 || pos_x >= TERMINAL_WIDTH || pos_y < 0 || pos_y >= TERMINAL_HEIGHT)
		return ;

	char	tmp_char = terminal->buffer_char[pos_y][TERMINAL_WIDTH - 1];
	char	tmp_color = terminal->buffer_color[pos_y][TERMINAL_WIDTH - 1];

	// Put an empty char on cursor pos by moving all chars to right
	for (uint32_t x = TERMINAL_WIDTH - 1; x > pos_x; x--)
	{
		terminal->buffer_char[pos_y][x] = terminal->buffer_char[pos_y][x - 1];
		terminal->buffer_color[pos_y][x] = terminal->buffer_color[pos_y][x - 1];
	}

	terminal->buffer_char[pos_y][pos_x] = '\0';
	terminal->buffer_color[pos_y][pos_x] = terminal->current_color;

	pos_y++;
	while (pos_y < TERMINAL_HEIGHT && tmp_char != '\0' && tmp_char != '\n')
	{
		char	tmp_char2 = terminal->buffer_char[pos_y][TERMINAL_WIDTH - 1];
		char	tmp_color2 = terminal->buffer_color[pos_y][TERMINAL_WIDTH - 1];

		// Move to right all the line
		for (uint32_t x = TERMINAL_WIDTH - 1; x > 0; x--)
		{
			terminal->buffer_char[pos_y][x] = terminal->buffer_char[pos_y][x - 1];
			terminal->buffer_color[pos_y][x] = terminal->buffer_color[pos_y][x - 1];
		}

		// Put the remain char on the other line
		terminal->buffer_char[pos_y][0] = tmp_char;
		terminal->buffer_color[pos_y][0] = tmp_color;

		// Update remain char
		tmp_char = tmp_char2;
		tmp_color = tmp_color2;

		// Update y
		pos_y++;
	}

	if (pos_y == TERMINAL_HEIGHT && tmp_char != '\0' && tmp_char != '\n')
	{
		// Put the remain char on the new line
		terminal_scroll_up(terminal);
		terminal->buffer_char[TERMINAL_HEIGHT - 1][0] = tmp_char;
		terminal->buffer_color[TERMINAL_HEIGHT - 1][0] = tmp_color;
		if (terminal->cursor.y > 0)
			terminal->cursor.y--;
	}
}


static void	_move_chars_left(t_terminal *terminal, uint32_t pos_x, int32_t pos_y)
{
	if (pos_x < 0 || pos_x >= TERMINAL_WIDTH || pos_y < 0 || pos_y >= TERMINAL_HEIGHT)
		return ;

	// Replace char on cursor pos by moving all chars to left
	for (uint32_t x = pos_x; x < TERMINAL_WIDTH; x++)
	{
		terminal->buffer_char[pos_y][x] = terminal->buffer_char[pos_y][x + 1];
		terminal->buffer_color[pos_y][x] = terminal->buffer_color[pos_y][x + 1];
	}
}
