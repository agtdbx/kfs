#ifndef KEYBOARD_H
# define KEYBOARD_H

# include "../define.h"
# include "keys.h"

# define PS2_STATUS		0x64
# define PS2_DATA		0x60
# define KEY_UP_MASK	0x80

typedef enum s_key_action
{
	KEY_PRESS,
	KEY_RELEASE
}	t_key_action;

typedef struct s_key_event
{
	t_key_action	type;
	t_key			key;
	uint8_t			scancode;
	char			ascii;
}	t_key_event;


typedef struct s_keyboard
{
	bool		caps_lock;
	bool		num_lock;
	bool		shiftL, shiftR;
	bool		ctrlL, ctrlR;
	bool		altL, altR;
	bool		super;
}	t_keyboard;


// Keyboard functions
t_keyboard	keyboard_init(void);

bool	keyboard_poll(t_keyboard *keyboard, t_key_event *key_event);

// char	scancode_to_char(uint8_t scancode);

#endif
