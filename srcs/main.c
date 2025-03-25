#include "shell.h"
#include <sys/wait.h>

int	main(void)
{
	char *line;
	char **token;
	int	status;

	while ((line = readline("~minishell~ >$")) != NULL)
	{
		if (strcmp("exit", line) == 0)
			break;
		else if (strcmp("clear", line) == 0)
			rl_clear_history();
		else
		{
			add_history(line);
			token = ft_split(line, ' ');
			if (fork() == 0)
				execvp(token[0], token);
			wait(&status);
		}
		free(line);
	}
	free(line);
	return (EXIT_SUCCESS);
}
/*
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


int	main(int ac, char **av)
{
	(void)ac;
	int	status;

	if (fork() == 0)
		execvp(av[1], av + 1);
	wait(&status);
	return (0);
}
*/
