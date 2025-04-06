#include "../includes/shell.h"

static void	updatewd(t_shell *mini, char *newpwd, char *oldpwd)
{
	t_env	*env;

	env = mini->env;
	while (env)
	{
        if (ft_strncmp("PWD", env->name, 3) == 0)
		{
			free(env->value);
			env->value = ft_strdup(newpwd);
		}
		if (ft_strncmp("OLDPWD", env->name, 6) == 0)
		{
			free(env->value);
			env->value = ft_strdup(oldpwd);
		}
		env = env->next;
	}
}

int	builtin_cd(t_shell *mini)
{
	char	*home;
	char	*dir;
	char	*oldpwd;

	oldpwd = getcwd(NULL, 0);
	home = extract_env_value(mini, "HOME");
	dir = NULL;
	if (!home)
	{
		ft_putstr_fd("cd: HOME not set\n", 2);
		return (1);
	}
	if (!mini->tokensar[1])
		chdir(home);
	else
	{	
		if ((ft_strncmp("~", mini->tokensar[1], 1) == 0))
		{
			if (mini->tokensar[1] && !mini->tokensar[1][1])
				dir = home;
			else
			{
				dir = ft_strjoin(home, ft_strchr(mini->tokensar[1], '~') + 1);
			}
		}
		else
		{
			dir = ft_strjoin(getcwd(NULL, 0), "/");
			dir = ft_strjoin(dir, mini->tokensar[1]);
		}
		if (chdir(dir))
		{
			printf("cd: %s: No such file or directory\n", mini->tokensar[1]);
			return (1);
		}
	}
    printf("%s\n%s\n", getcwd(NULL,0), oldpwd);
	updatewd(mini, getcwd(NULL, 0), oldpwd);
	return (0);
}

/**
 * will work with the same way env command on bash
*/
int	builtin_env(t_shell *mini)
{
	t_env	*temp;

	temp = mini->env;
	if (!mini->tokensar[1])
	{
		while (temp)
		{
			printf("%s", temp->name);
			printf("=");
			printf("%s\n", temp->value);
			temp = temp->next;
		}
		return (0);
	}
	else
		return (1);
}

/**
 * to check if the command is in the built_in commands list, if yes then use the custome one
*/

int	check_builtin(t_shell *mini)
{
    if (mini->tokensar && mini->tokensar[0])
    {
	    if (ft_strncmp("cd", mini->tokensar[0], 2) == 0)
	    {   
	    	if (builtin_cd(mini))
	    		return (2);
		    else
			    return (1);
	    }
	    if (ft_strncmp("env", mini->tokensar[0], 3) == 0)
	    {
	    	if (builtin_env(mini))
		    	return (2);
		    else
	    		return (1);
	    }
	    else
		    return (0);
    }
	return (1);
}