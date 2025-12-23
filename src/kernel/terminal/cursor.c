#include "terminal.h"
#include "../libs/libasm.h"

void	ternimal_set_cursor(t_terminal *terminal, uint x, uint y)
{
	if (x >= TERMINAL_WIDTH || y >= TERMINAL_HEIGHT)
		return ;

	terminal->cursor_x = x;
	terminal->cursor_y = y;

	_update_cursor_pos(x, y);
}


void	_update_cursor_pos(uint x, uint y)
{
	uint pos = x + y * TERMINAL_WIDTH;

	outb(0x3D4, 0x0F);
	outb(0x3D5, (pos & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, ((pos >> 8) & 0xFF));
}
