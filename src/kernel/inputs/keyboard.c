#include "keyboard.h"
#include "../libs/libasm.h"

static char keymap_us[128] = {
	[0x01] = 0, // ESC (non-printable here)
	[0x02] = '1', [0x03] = '2', [0x04] = '3', [0x05] = '4', [0x06] = '5',
	[0x07] = '6', [0x08] = '7', [0x09] = '8', [0x0A] = '9', [0x0B] = '0',
	[0x0C] = '-', [0x0D] = '=',
	[0x0E] = 8, // Backspace
	[0x0F] = '\t', // Tab
	[0x10] = 'q', [0x11] = 'w', [0x12] = 'e', [0x13] = 'r', [0x14] = 't',
	[0x15] = 'y', [0x16] = 'u', [0x17] = 'i', [0x18] = 'o', [0x19] = 'p',
	[0x1A] = '[', [0x1B] = ']',
	[0x1C] = '\n', // Enter
	[0x1E] = 'a', [0x1F] = 's', [0x20] = 'd', [0x21] = 'f', [0x22] = 'g',
	[0x23] = 'h', [0x24] = 'j', [0x25] = 'k', [0x26] = 'l',
	[0x27] = ';', [0x28] = '\'', [0x29] = '`',
	[0x2C] = 'z', [0x2D] = 'x', [0x2E] = 'c', [0x2F] = 'v', [0x30] = 'b',
	[0x31] = 'n', [0x32] = 'm',
	[0x33] = ',', [0x34] = '.', [0x35] = '/',
	[0x39] = ' ', // Space

	// Keypad (when NumLock on and no E0)
	[0x4F] = '1', [0x50] = '2', [0x51] = '3',
	[0x4B] = '4', [0x4C] = '5', [0x4D] = '6',
	[0x47] = '7', [0x48] = '8', [0x49] = '9',
	[0x52] = '0', [0x53] = '.', // keypad '.' (decimal)
};


t_keyboard	keyboard_init(void)
{
	t_keyboard	keyboard;

	// TODO: PATCH MEMORY PROBLEM
	keyboard.caps_lock = false;
	// keyboard.num_lock = false;
	keyboard.shiftL = false;
	keyboard.shiftR = false;
	keyboard.ctrlL = false;
	keyboard.ctrlR = false;
	keyboard.altL = false;
	keyboard.altR = false;
	keyboard.super = false;

	return (keyboard);
}



bool	keyboard_poll(t_keyboard *keyboard, t_key_event *key_event)
{
	uint8_t status = inb(PS2_STATUS); // Read keyboard status

	// Check if there is data
	if (!(status & 0x01))
		return (false); // If no data, return false

	// If data, read the data
	key_event->scancode = inb(PS2_DATA);

	// Check the type of the event
	if ((key_event->scancode & KEY_UP_MASK) == KEY_UP_MASK)
		key_event->type = KEY_RELEASE;
	else
		key_event->type = KEY_PRESS;

	// Compute the key from the scancode
	key_event->key = K_F;

	// Compute the ascii of the key
	key_event->ascii = 'f';

	// Update the keyboard state

	return true; // Return true to tell that there is a key event
}


// char	scancode_to_char(uint8_t scancode)
// {
// 	if (scancode > 0x53)
// 		return (' ');
// 	return keymap_us[scancode];
// }
