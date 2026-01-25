#include "libstr.h"

#include "../terminal/terminal.h"

uint32_t	strlen(const char *str)
{
	if (!str)
		return (0);

	uint32_t	len = 0;

	while (str[len])
		len++;

	return (len);
}



uint32_t	line_len(const char *line)
{
	if (!line)
		return (0);

	uint32_t	len = 0;

	while (len < TERMINAL_WIDTH && line[len] != '\n' && line[len] != '\0')
		len++;

	return (len);
}
