#ifndef KEYS_H
# define KEYS_H

# include "../define.h"

typedef enum e_key
{
	// Control / system
	K_NONE = 0,
	K_ESCAPE,
	K_TAB,
	K_ENTER,
	K_BACKSPACE,
	K_INSERT,	K_DELETE,
	K_HOME,		K_END,
	K_PAGE_UP,	K_PAGE_DOWN,

	// Modifiers
	K_CAPS_LOCK,
	K_NUM_LOCK,
	K_LSHIFT,	K_RSHIFT,
	K_LCTRL,	K_RCTRL,
	K_LALT,		K_RALT,
	K_SUPER,

	// Arrows
			K_UP,
	K_LEFT, K_RIGHT, K_DOWN,

	// Functions keys
	K_F1,	K_F2,	K_F3,	K_F4,
	K_F5,	K_F6,	K_F7,	K_F8,
	K_F9,	K_F10,	K_F11,	K_F12,

	// Letters
	K_A,	K_B,	K_C,	K_D,	K_E,	K_F,	K_G,
	K_H,	K_I,	K_J,	K_K,	K_L,	K_M,	K_N,
	K_O,	K_P,	K_Q,	K_R,	K_S,	K_T,	K_U,
	K_V,	K_W,	K_X,	K_Y,	K_Z,

	// Numbers
	K_0,	K_1,	K_2,	K_3,	K_4,
	K_5,	K_6,	K_7,	K_8,	K_9,

	// Ponctuations
	K_BACKTICK,		// `
	K_MINUS,		// -
	K_EQUAL,		// =
	K_LBRACKET,		// [
	K_RBRACKET,		// ]
	K_BACKSLASH,	// '\'
	K_SEMICOLON,	// ,
	K_APOSTROPHE,	// '
	K_COMMA,		// ,
	K_DOT,			// .
	K_SLASH,		// /
	K_SPACE,		// ^^

	// Keypad
	K_KP_0,	K_KP_1,	K_KP_2,	K_KP_3,	K_KP_4,
	K_KP_5,	K_KP_6,	K_KP_7,	K_KP_8,	K_KP_9,
	K_KP_ADD,
	K_KP_SUBSTRACT,
	K_KP_MULTIPLY,
	K_KP_DIVIDE,

	// Extended media/power
	K_PRINT_SCREEN,
	K_PAUSE,

	K_COUNT	// For get the number of key
}	t_key;

#endif
