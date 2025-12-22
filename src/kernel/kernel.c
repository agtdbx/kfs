# define TERMINAL_ADDR 0xb8000
# define TERMINAL_WIDTH 80
# define TERMINAL_HEIGHT 25

# define COLOR_LIGHT_GREY 0x07

typedef unsigned int uint;

static void	write_char(uint x, uint y, char c, char color);

void	kmain(void)
{
	const char *str = "42 kfs";
	char *vidptr = (char*)0xb8000;  // Video memory address
	uint i = 0;
	uint j = 0;

	// Clear the screen
	while (j < 80 * 25 * 2) {
		vidptr[j] = ' ';
		vidptr[j+1] = 0x07; // Attribute-byte: light grey on black screen
		j += 2;
	}

	// Write the string to video memory
	j = 0;
	while (str[j] != '\0') {
		vidptr[i] = str[j];
		vidptr[i+1] = 0x07;
		++j;
		i += 2;
	}

	// Infinite loop to keep the kernel running
	while (1) {}
}


static void	write_char(uint x, uint y, char c, char color)
{
	uint	char_id = x + y * TERMINAL_HEIGHT * 2;
	char	*terminal = TERMINAL_ADDR;

	terminal[char_id] = c;
	terminal[char_id + 1] = color;
}


// static void	write_char(uint x, uint y, char c, char color)
