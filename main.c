#include "includes/shell.h"

volatile sig_atomic_t sig = 0;

int main (int ac, char **av, char **envp)
{
	char *input;
	int status = 0;
	t_initenv	*initenv;

	(void)av;
	if(ac == 1)
	{
		init_sig();
		initenv = malloc(sizeof(t_initenv));
		initenv->copy_env = copy_env(envp);
		list_env(&initenv->env, envp);
		while((input = readline("minishell> ")))
		{
			if (ft_isempty(input))
			{
				free(input);
				continue ;
			}
			add_history(input);
			status = activate_shell(input, initenv);
			free(input);
		}
	}
	return (status);
}
