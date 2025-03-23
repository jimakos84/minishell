#include "shell.h"

int	main(void)
{
	char *line;
	char *token;
	char *delimiter = "&$ |";

	while ((line = readline("~minishell~ >$")) != NULL)
	{
		if (strcmp("exit", line) == 0)
			break;
		else if (strcmp("clear", line) == 0)
			rl_clear_history();
		else
		{
			add_history(line);
			/***
			 * strtok() is used as split() (tokenize) a string into smaller parts,
			 * based on delimiter characters (like commas, spaces, etc.) provieded.
			 * char *strtok(char *str, const char *delim)
			 */
			token = strtok(line, delimiter);
			while (token != NULL)
			{
				printf("%s\n", token);
				token = strtok(NULL, delimiter);
			}
			free(token);
		}
		free(line);
	}
	free(line);
	return (EXIT_SUCCESS);
}

/**
 *prgram logic
 *while (valid_input_line_from_fd)
 {
	adding_input_line_history
	while(contain_valid_token)
	{
		extract_command();
		fork()
			execve(command);
		wait(&status);
	}
 }
 return (EXIT_SUCCESS);
 */
