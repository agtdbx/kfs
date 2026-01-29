#include "terminal.h"
#include "../libs/libstr.h"

static	uint8_t	terminal_count = 0;

t_terminal	terminal_init(const char base_color, const char topbar_color)
{
	t_terminal	terminal;

	// Set terminal address
	terminal.address = TERMINAL_ADDR;

	// Init buffers
	for (uint32_t x = 0; x < TERMINAL_WIDTH + 1; x++)
	{
		terminal.buffer_char[0][x] = '\0';
		terminal.buffer_color[0][x] = topbar_color;
	}
	for (uint32_t y = 1; y < TERMINAL_HEIGHT; y++)
	{
		for (uint32_t x = 0; x < TERMINAL_WIDTH + 1; x++)
		{
			terminal.buffer_char[y][x] = '\0';
			terminal.buffer_color[y][x] = base_color;
		}
	}

	// Set colors
	terminal.current_color = base_color;
	terminal.topbar_color = topbar_color;

	// Set terminal id
	terminal.id = terminal_count;
	terminal_count++;

	// Init positions
	terminal.cursor.x = 0;
	terminal.cursor.y = 1;

	terminal_update_topbar(&terminal);

	return (terminal);
}


void	terminal_clear(t_terminal *terminal)
{
	for (uint32_t y = 1; y < TERMINAL_HEIGHT; y++)
	{
		for (uint32_t x = 0; x < TERMINAL_WIDTH; x++)
		{
			terminal->buffer_char[y][x] = '\0';
			terminal->buffer_color[y][x] = terminal->current_color;
		}
	}
	terminal->cursor.x = 0;
	terminal->cursor.y = 1;
	_update_cursor_pos(terminal->cursor.x, terminal->cursor.y);
}


void	terminal_flush(t_terminal *terminal)
{
	uint32_t	char_addr = 0;
	char		char_tmp = ' ';

	for (uint32_t y = 0; y < TERMINAL_HEIGHT; y++)
	{
		for (uint32_t x = 0; x < TERMINAL_WIDTH; x++)
		{
			// Compute char addr
			char_addr = (x + y * TERMINAL_WIDTH) * 2;

			// Get char to write
			char_tmp = terminal->buffer_char[y][x];

			// Case of non displayable char remplace it by space
			if (char_tmp < 32 || char_tmp > 127)
				char_tmp = ' ';

			// Write char and color data
			terminal->address[char_addr] = char_tmp;
			terminal->address[char_addr + 1] = terminal->buffer_color[y][x];
		}
	}
}


void	terminal_scroll_up(t_terminal *terminal)
{
	for (uint32_t y = 1; y < TERMINAL_HEIGHT - 1; y++)
	{
		for (uint32_t x = 0; x < TERMINAL_WIDTH; x++)
		{
			terminal->buffer_char[y][x] = terminal->buffer_char[y + 1][x];
			terminal->buffer_color[y][x] = terminal->buffer_color[y + 1][x];
		}
	}
	for (uint32_t x = 0; x < TERMINAL_WIDTH; x++)
	{
		terminal->buffer_char[TERMINAL_HEIGHT - 1][x] = '\0';
		terminal->buffer_color[TERMINAL_HEIGHT - 1][x] = terminal->current_color;
	}
}


void	terminal_update_topbar(t_terminal *terminal)
{
	// Write terminal id
	terminal->buffer_char[0][0] = 'I';
	terminal->buffer_char[0][1] = 'd';
	terminal->buffer_char[0][2] = ':';
	terminal->buffer_char[0][3] = '0' + ((terminal->id / 10) % 10);
	terminal->buffer_char[0][4] = '0' + (terminal->id % 10);

	// Write cursor position
	terminal->buffer_char[0][10] = 'C';
	terminal->buffer_char[0][11] = 'u';
	terminal->buffer_char[0][12] = 'r';
	terminal->buffer_char[0][13] = 's';
	terminal->buffer_char[0][14] = 'o';
	terminal->buffer_char[0][15] = 'r';
	terminal->buffer_char[0][16] = ':';
	terminal->buffer_char[0][17] = '(';
	terminal->buffer_char[0][18] = '0' + ((terminal->cursor.x / 10) % 10);
	terminal->buffer_char[0][19] = '0' + (terminal->cursor.x % 10);
	terminal->buffer_char[0][20] = ',';
	terminal->buffer_char[0][21] = '0' + ((terminal->cursor.y / 10) % 10);
	terminal->buffer_char[0][22] = '0'+ (terminal->cursor.y % 10);
	terminal->buffer_char[0][23] = ')';
}
