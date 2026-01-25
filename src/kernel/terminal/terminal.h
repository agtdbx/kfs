#ifndef TERMINAL_H
# define TERMINAL_H

# define TERMINAL_ADDR (char *)0xb8000
# define TERMINAL_WIDTH 80
# define TERMINAL_HEIGHT 25
# define TAB_SIZE 4

# include "../define.h"

static const uint32_t	TERMINAL_SIZE = TERMINAL_WIDTH * TERMINAL_HEIGHT;
static const uint32_t	TERMINAL_MAX_X = TERMINAL_WIDTH - 1;
static const uint32_t	TERMINAL_MAX_Y = TERMINAL_HEIGHT - 1;

typedef struct s_position
{
	uint32_t	x;
	uint32_t	y;
}	t_position;

typedef struct s_terminal
{
	char		*address;
	char		buffer_char[TERMINAL_HEIGHT][TERMINAL_WIDTH + 1];
	char		buffer_color[TERMINAL_HEIGHT][TERMINAL_WIDTH + 1];
	char		current_color;
	char		topbar_color;
	uint8_t		id;
	t_position	cursor;
}	t_terminal;

// Init
t_terminal	terminal_init(const char base_color, const char topbar_color);

// Terminal functions
void	terminal_clear(t_terminal *terminal);
void	terminal_flush(t_terminal *terminal);
void	terminal_scroll_up(t_terminal *terminal);
void	terminal_update_topbar(t_terminal *terminal);

// Write functions
void	terminal_putchar(t_terminal *terminal, const char c);
void	terminal_putstring(t_terminal *terminal, const char *str);
void	terminal_write_putchar(t_terminal *terminal, const char c, const char color, bool insert);
void	terminal_write_putstring(t_terminal *terminal, const char *str, const char color, bool insert);
void	terminal_remove_char(t_terminal *terminal);
void	terminal_delete_char(t_terminal *terminal);

// Cursor functions
void	terminal_set_cursor(t_terminal *terminal, uint32_t x, uint32_t y);
void	terminal_update_cursor(t_terminal *terminal);
void	terminal_cursor_left(t_terminal *terminal);
void	terminal_cursor_right(t_terminal *terminal);
void	terminal_cursor_up(t_terminal *terminal);
void	terminal_cursor_down(t_terminal *terminal);
void	terminal_cursor_start(t_terminal *terminal);
void	terminal_cursor_end(t_terminal *terminal);
void	_update_cursor_pos(uint32_t x, uint32_t y);


#endif
