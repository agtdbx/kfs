#ifndef TERMINAL_H
# define TERMINAL_H

# define TERMINAL_ADDR (char *)0xb8000
# define TERMINAL_WIDTH 80
# define TERMINAL_HEIGHT 25
# define TAB_SIZE 4

# include "../define.h"

static const uint32_t	TERMINAL_SIZE = TERMINAL_WIDTH * TERMINAL_HEIGHT;

typedef struct s_position
{
	uint32_t	x;
	uint32_t	y;
}	t_position;

typedef struct s_terminal
{
	char		*address;
	char		buffer_char[TERMINAL_WIDTH * TERMINAL_HEIGHT];
	char		buffer_color[TERMINAL_WIDTH * TERMINAL_HEIGHT];
	char		current_color;
	uint32_t	lines_length[TERMINAL_HEIGHT];
	t_position	cursor;
	t_position	last_char_pos;
}	t_terminal;

// Init
t_terminal	terminal_init(char base_color);

// Terminal functions
void	terminal_clear(t_terminal *terminal);
void	terminal_clear_screen(t_terminal *terminal);
void	terminal_flush(t_terminal *terminal);
void	terminal_scroll_up(t_terminal *terminal);

// Write functions
void	terminal_putchar(t_terminal *terminal, const char c);
void	terminal_putstring(t_terminal *terminal, const char *str);

// Cursor functions
void	ternimal_set_cursor(t_terminal *terminal, uint32_t x, uint32_t y);
void	_update_cursor_pos(uint32_t x, uint32_t y);


#endif
