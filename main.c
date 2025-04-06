#include "includes/shell.h"

volatile sig_atomic_t sig = 0;

int main (int ac, char **av, char **envp)
{
	char *input;
	int status = 0;

	(void)av;
	if(ac == 1)
	{
		init_sig();
		while((input = readline("minishell> ")))
		{
			add_history(input);
			status = activate_shell(input, envp);
			free(input);
		}
	}
	return (status);
}
