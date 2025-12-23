#include "terminal.h"

t_terminal	terminal_init(char base_color)
{
	t_terminal	terminal;

	terminal.addr = TERMINAL_ADDR;
	terminal.cursor_x = 0;
	terminal.cursor_y = 0;
	terminal.current_color = base_color;

	return (terminal);
}


void	terminal_clear(t_terminal *terminal)
{
	uint	i = 0;
	uint	terminal_size = TERMINAL_WIDTH * TERMINAL_HEIGHT * 2;

	while (i < terminal_size) {
		terminal->addr[i] = ' ';
		terminal->addr[i+1] = terminal->current_color;
		i += 2;
	}
}


void	terminal_scroll_up(t_terminal *terminal)
{
	uint	i = 0;
	uint	next_shift = TERMINAL_WIDTH * 2;
	uint	terminal_last_line = TERMINAL_WIDTH * (TERMINAL_HEIGHT - 1) * 2;
	uint	terminal_size = TERMINAL_WIDTH * (TERMINAL_HEIGHT) * 2;

	while (i < terminal_last_line) {
		terminal->addr[i] = terminal->addr[i + next_shift];
		terminal->addr[i+1] = terminal->addr[i+1 + next_shift];
		i += 2;
	}
	while (i < terminal_size) {
		terminal->addr[i] = ' ';
		terminal->addr[i+1] = terminal->current_color;
		i += 2;
	}
}

