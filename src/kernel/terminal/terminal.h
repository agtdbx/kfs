#ifndef TERMINAL_H
# define TERMINAL_H

# include "../define.h"

typedef struct s_terminal
{
	char	*addr;
	uint	cursor_x;
	uint	cursor_y;
	char	current_color;
}	t_terminal;

// Init
t_terminal	terminal_init(char base_color);

// Terminal functions
void	terminal_clear(t_terminal *terminal);
void	terminal_scroll_up(t_terminal *terminal);

// Write functions
void	terminal_putchar(t_terminal *terminal, char c);
void	terminal_putstring(t_terminal *terminal, char *str);

#endif
