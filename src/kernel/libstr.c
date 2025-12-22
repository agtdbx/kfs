#include "libstr.h"

uint strlen(const char *str)
{
	if (!str)
		return (0);

	uint	len = 0;

	while (str[len])
		len++;

	return (len);
}
