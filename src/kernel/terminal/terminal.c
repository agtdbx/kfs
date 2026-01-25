#include "terminal.h"
#include "../libs/libstr.h"

t_terminal	terminal_init(char base_color)
{
	t_terminal	terminal;

	// Set terminal address
	terminal.address = TERMINAL_ADDR;

	// Init buffers
	for (uint32_t y = 0; y < TERMINAL_HEIGHT; y++)
	{
		for (uint32_t x = 0; x < TERMINAL_WIDTH + 1; x++)
		{
			terminal.buffer_char[y][x] = '\0';
			terminal.buffer_color[y][x] = base_color;
		}
	}

	// Set color
	terminal.current_color = base_color;

	// Init positions
	terminal.cursor.x = 0;
	terminal.cursor.y = 0;

	return (terminal);
}


void	terminal_clear(t_terminal *terminal)
{
	for (uint32_t y = 0; y < TERMINAL_HEIGHT; y++)
	{
		for (uint32_t x = 0; x < TERMINAL_WIDTH; x++)
		{
			terminal->buffer_char[y][x] = '\0';
			terminal->buffer_color[y][x] = terminal->current_color;
		}
	}
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
	for (uint32_t y = 0; y < TERMINAL_HEIGHT - 1; y++)
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
