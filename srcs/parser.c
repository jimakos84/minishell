#include "../includes/shell.h"

void expand(t_shell *mini, t_list *list);
int get_num_args(char *token);
void get_args(char **args, char *token, int size);
char *get_command(char *token);
char *set_path_name(char *token, t_shell *mini);
char **set_arg_array(int num_args, char *token, char *cmdpath);

int parse_and_expand(t_shell *mini)
{
	char	*cmd;

	expand(mini, mini->tokens);
	cmd = mini->cmds->cmd;
	if(!mini->cmds->command || builtin_cmd(cmd))
	{
		if (check_builtin(mini) == 2)
			return (2);
		else
			return (1);
	}
	return (0);
}

void expand(t_shell *mini, t_list *list)
{
	t_list *current = list;
	t_cmd *cmd;
	
	while (current)
	{
		cmd = malloc(sizeof(t_cmd));
		cmd->cmd = get_command(current->token);
		cmd->command = set_path_name(current->token, mini);
		cmd->num_args = get_num_args(current->token);
		cmd->args = set_arg_array(cmd->num_args, current->token, cmd->command);
		cmd->next = NULL;
		mini->cmds = list_add_command(mini->cmds, cmd);
		mini->num_cmds++;
		current = current->next;
	}
}

char **set_arg_array(int num_args, char *token, char *cmdpath)
{
	char **args = malloc(sizeof(char*) * (num_args + 1));
	if(!args)
		return (NULL);
	args[0] = cmdpath;
	if(num_args > 1)
		get_args(args, token, num_args);
	args[num_args] = NULL;
	return (args);
}

char *set_path_name(char *token, t_shell *mini)
{
	char	**path_dirs;
	char	*command;
	char	*path;
	int		i;
	
	i = 0;
	command = ft_substr(token, 0, ft_strchr(token, 32) - token);
	path_dirs = ft_split(extract_env_value(mini->initenv, "PATH"), ':');
	if (!path_dirs)
		return (NULL);
	while (path_dirs && path_dirs[i])
	{
		path = ft_strjoin(path_dirs[i], "/");
		path = ft_strjoin(path, command);
		if (!path)
			return (NULL);
		if (access(path, X_OK) == 0)
			return (path);
		i++; 
	}
	if (access(path, X_OK) == -1)
	{	
		if (builtin_cmd(command))
			return (NULL);
		else
			printf("%s: command not found\n", command);
	}
	return (NULL);
}

char *get_command(char *token)
{
	int i = 0, j = 0;
	char *command;
	while(token && token[i])
	{
		if(token[i] == ' ')
		{
			command = malloc(sizeof(char)*(i + 1));
			if(!command)
				return (NULL);
			while(token && token[j] && j < i)
			{
				command[j] = token[j];
				j++;
			}
			command[j] = '\0';
			return (command);
		}
		i++;
	}
	if(token[i] == '\0')
		return (token);
	return (NULL);
}

void get_args(char **args, char *token, int size)
{
	int i = 0, k = 0, start = 0, step = 1;
	while(token && token[i] && token[i] != ' ')
		i++;
	while(step < size)
	{
		while(token && token[i] && token[i] == ' ')
			i++;
		start = i;
		while(token && token[i] && token[i] != ' ')
			i++;
		args[step] = malloc(sizeof(char) * (i - start + 1));
		k = 0;
		while(token && token[k + start] && (k + start) < i)
		{
			args[step][k] = token[k + start];
			k++;
		}
		args[step][k] = '\0';
		step++;
	}
}

int get_num_args(char *token)
{
	int i = 0, count = 1, flag = 0;
	while(token && token[i])
	{
		if(token[i] == ' ' && !flag)
		{
			count++;
			flag = 1;
		}
		else if(token[i] != ' ' && flag)
			flag = 0;
		i++;
	}
	return (count);
}

