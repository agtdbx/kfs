#include "terminal.h"
#include "../libs/libstr.h"

t_terminal	terminal_init(char base_color)
{
	t_terminal	terminal;

	// Set terminal address
	terminal.address = TERMINAL_ADDR;

	// Init buffers
	for (uint32_t i = 0; i < TERMINAL_SIZE; i++)
	{
		terminal.buffer_char[i] = '\0';
		terminal.buffer_color[i] = base_color;
	}

	// Init lines length
	for (uint32_t i = 0; i < TERMINAL_HEIGHT; i++)
		terminal.lines_length[i] = 0;

	// Set color
	terminal.current_color = base_color;

	// Init positions
	terminal.cursor.x = 0;
	terminal.cursor.y = 0;
	terminal.last_char_pos.x = 0;
	terminal.last_char_pos.y = 0;

	return (terminal);
}


void	terminal_clear(t_terminal *terminal)
{
	for (uint32_t i = 0; i < TERMINAL_SIZE; i++)
	{
		terminal->buffer_char[i] = '\0';
		terminal->buffer_color[i] = terminal->current_color;
	}
}


void	terminal_clear_screen(t_terminal *terminal)
{
	for (uint32_t i = 0; i < TERMINAL_SIZE; i++)
	{
		terminal->address[i * 2] = ' ';
		terminal->address[i * 2 + 1] = terminal->current_color;
	}
}


void	terminal_flush(t_terminal *terminal)
{
	uint32_t	char_id = 0;
	uint32_t	line_length = 0;
	uint32_t	char_addr = 0;
	char		char_tmp = ' ';

	// For each line
	for (uint32_t y = 0; y <= terminal->last_char_pos.y; y++)
	{
		// Get it's length.
		line_length = terminal->lines_length[y];

		for (uint32_t x = 0; x < line_length; x++)
		{
			// Compute char addr
			char_addr = (x + y * TERMINAL_WIDTH) * 2;

			// Get char to write
			char_tmp = terminal->buffer_char[char_id];

			// Case of non displayable char remplace it by space
			if (char_tmp < 32 || char_tmp > 127)
				char_tmp = ' ';

			// Write char and color data
			terminal->address[char_addr] = char_tmp;
			terminal->address[char_addr + 1] = terminal->buffer_color[char_id];

			// Go to next char
			char_id++;
		}
	}
}


void	terminal_scroll_up(t_terminal *terminal)
{
	uint32_t	char_id = 0;
	uint32_t	first_line_lenght = terminal->lines_length[0] + 1;
	uint32_t	buffer_length = strlen(terminal->buffer_char) - first_line_lenght;

	// TODO: PATCH

	// Clear screen
	terminal_clear_screen(terminal);

	// Move buffers
	for (uint32_t i = 0; i < first_line_lenght; i++)
	{
		terminal->buffer_char[i] = terminal->buffer_char[i + first_line_lenght];
		terminal->buffer_color[i] = terminal->buffer_color[i + first_line_lenght];
	}
	// Reset data
	for (uint32_t i = 0; i < first_line_lenght; i++)
	{
		terminal->buffer_char[buffer_length + i] = '\0';
		terminal->buffer_color[buffer_length + i] = terminal->current_color;
	}

	// Move lines size
	for (uint32_t i = 0; i < TERMINAL_HEIGHT - 1; i++)
		terminal->lines_length[i] = terminal->lines_length[i + 1];
	// Reset last line size
	terminal->lines_length[TERMINAL_HEIGHT - 1] = 0;

	// Update last char pos
	terminal->last_char_pos.y--;
}
