#ifndef KEYBOARD_H
# define KEYBOARD_H

# include "../define.h"

# define PS2_STATUS		0x64
# define PS2_DATA		0x60
# define KEY_UP_MASK	0x80


uint8_t	keyboard_poll(uint8_t* sc);
char	scancode_to_char(uint8_t scancode);

#endif
