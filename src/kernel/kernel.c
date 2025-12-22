#include "define.h"
#include "colors.h"
// #include "libstr.h"

static uint strlen(const char *str)
{
	if (!str)
		return (0);

	uint	len = 0;

	while (str[len])
		len++;

	return (len);
}

static void	clear_terminal(void);
static void	write_char(uint x, uint y, char c, char color);
static void	write_string(uint x, uint y, const char *str, char color);

void	kmain(void)
{
	const char *str = "42 kfs";
	char *vidptr = (char*)0xb8000;  // Video memory address

	// Clear the screen
	clear_terminal();

	// Write the string to video memory
	write_string(0, 0, str, COLOR_LIGHT_GREY);

	// Infinite loop to keep the kernel running
	while (1) {}
}


static void	clear_terminal(void)
{
	uint	i = 0;
	uint	terminal_end = TERMINAL_WIDTH * TERMINAL_HEIGHT * 2;
	char	*terminal = TERMINAL_ADDR;

	while (i < terminal_end) {
		terminal[i] = ' ';
		terminal[i+1] = COLOR_LIGHT_GREY;
		i += 2;
	}
}


static void	write_char(uint x, uint y, char c, char color)
{
	uint	char_id = (x + y * TERMINAL_HEIGHT) * 2;
	char	*terminal = TERMINAL_ADDR;

	terminal[char_id] = c;
	terminal[char_id + 1] = color;
}


static void	write_string(uint x, uint y, const char *str, char color)
{
	uint	i = 0;
	uint	len = strlen(str);

	if (x >= TERMINAL_WIDTH || y >= TERMINAL_HEIGHT)
		return ;

	while (i < len)
	{
		write_char(x, y, str[i], color);
		i++;
		x++;
		if (x == TERMINAL_WIDTH)
		{
			x = 0;
			y++;
			if (y == TERMINAL_HEIGHT)
				return ;
		}
	}
}
