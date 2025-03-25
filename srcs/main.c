#include "shell.h"

int	main(int ac, char **av, char **envp)
{
	char *line;
	char **token;
	int	status;
	char	*cwd = NULL;
	char	*path = "/bin/";
	char	*_path;
	(void)ac;
	(void)av;


	printf("%s\n", getcwd(cwd, BUFSIZ));
	while ((line = readline("👀minishel👀$")) != NULL)
	{
		if (ft_strncmp("exit", line, 4) == 0)
			break;
		else
		{
			token = ft_split(line, ' ');
			_path = ft_strjoin(path, token[0]);
			if (fork() == 0)
				execve(_path, token, envp);
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
