#ifndef COMMANDS_H
# define COMMANDS_H

# include "../define.h"
#include "../terminal/terminal.h"

// Parsing
void	parse_execute_command(t_terminal *terminal);

// Commands
void	command_echo(t_terminal *terminal, const char *command_buffer);
void	command_clear(t_terminal *terminal, const char *command_buffer);

#endif
