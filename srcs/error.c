#include "../includes/shell.h"

int syntax_error(char *msg)
{
	ft_putendl_fd(msg, 2);
	return (1);
}
