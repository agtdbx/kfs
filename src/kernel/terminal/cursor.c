#include "terminal.h"
#include "../libs/io.h"
#include "../libs/libstr.h"

void	terminal_set_cursor(t_terminal *terminal, uint32_t x, uint32_t y)
{
	if (x >= TERMINAL_WIDTH || y >= TERMINAL_HEIGHT)
		return ;

	terminal->cursor.x = x;
	terminal->cursor.y = y;

	_update_cursor_pos(x, y);
}


void	terminal_cursor_left(t_terminal *terminal)
{
	if (terminal->cursor.x == 0 && terminal->cursor.y == 0)
		return ;

	terminal->cursor.x--;

	if (terminal->cursor.x < 0)
	{
		terminal->cursor.y--;
		terminal->cursor.x = strlen(terminal->buffer_char[terminal->cursor.y]);
	}

	_update_cursor_pos(terminal->cursor.x, terminal->cursor.y);
}


void	terminal_cursor_right(t_terminal *terminal)
{
	if (terminal->cursor.x == TERMINAL_WIDTH - 1 && terminal->cursor.y == TERMINAL_HEIGHT - 1)
		return ;

	terminal->cursor.x++;
	uint32_t line_length = strlen(terminal->buffer_char[terminal->cursor.y]);

	if (terminal->cursor.x > line_length)
	{
		terminal->cursor.y++;
		terminal->cursor.x = 0;
	}

	_update_cursor_pos(terminal->cursor.x, terminal->cursor.y);
}


void	terminal_cursor_up(t_terminal *terminal)
{
	if (terminal->cursor.y == 0)
		return ;

	terminal->cursor.y--;
	uint32_t line_length = strlen(terminal->buffer_char[terminal->cursor.y]);

	if (terminal->cursor.x > line_length)
		terminal->cursor.x = line_length;

	_update_cursor_pos(terminal->cursor.x, terminal->cursor.y);
}


void	terminal_cursor_down(t_terminal *terminal)
{
	if (terminal->cursor.y == TERMINAL_HEIGHT - 1)
		return ;

	terminal->cursor.y++;
	uint32_t line_length = strlen(terminal->buffer_char[terminal->cursor.y]);

	if (terminal->cursor.x > line_length)
		terminal->cursor.x = line_length;

	_update_cursor_pos(terminal->cursor.x, terminal->cursor.y);
}


void	_update_cursor_pos(uint32_t x, uint32_t y)
{
	uint32_t pos = x + y * TERMINAL_WIDTH;

	outb(0x3D4, 0x0F);
	outb(0x3D5, (pos & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, ((pos >> 8) & 0xFF));
}
