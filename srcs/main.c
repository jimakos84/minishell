#include "shell.h"

int main(void) //int ac, char **av
{
	char *line;

	line = readline("~minishell~>$");
	printf("%s\n", line);
	return (EXIT_SUCCESS);
}
