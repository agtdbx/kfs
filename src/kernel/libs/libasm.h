#ifndef LIBASM_H
# define LIBASM_H

# include "../define.h"

void	outb(uint16_t port, uint8_t val);
uint8_t	inb(uint16_t port);

#endif
