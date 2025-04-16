#include "../includes/shell.h"

int ft_isspace(int c);
static char *set_filename(char *token);
static char *set_arg_string(char *token);
static char *get_arg_string(char *token);


t_cmd *handel_output(t_shell *mini, char *token)
{
	/**
	 * example of the command format
	 * echo "the string need to write in to the file" > file.txt
	*/
	char *arg_str = set_arg_string(token);
	t_cmd *cmd = malloc(sizeof(t_cmd));
	if(!cmd)
		return (NULL);
	cmd->type = OPRD_CMD;
	cmd->command = set_path_name(mini, arg_str);
	cmd->filename = set_filename(token);
	cmd->num_args = get_num_args(arg_str);
	cmd->args = set_arg_array(cmd->num_args, arg_str, cmd->command);
	cmd->next = NULL;
	free(arg_str);
	return (cmd);
}

static char *set_filename(char *token)
{
	int i = 1, start = 0;
	char *str = ft_strchr(token, '>'), c, *res;
	while(str && str[i] && ft_isspace(str[i]))
		i++;
	start = i;
	if(str[i] == '\'' || str[i] == '"')
	{
		c = str[i];
		i++;
		while(str && str[i] && str[i] != c)
			i++;
		i++;
	}
	else
	{
		while(str && str[i] && !ft_isspace(str[i]))
			i++;
	}
	res = ft_strnmdup(str, start, i);
	return (res);
}

static char *set_arg_string(char *token)
{
	char *s1 = ft_strchr(token, '>');
	char *s2 = ft_strnmdup(token, 0, s1 - token);
	char *s3 = ft_strtrim(s2, " \f\n\t\v\r");
	char *s4 = get_arg_string(s1);
	char *s5 = ft_strjoin(s3, s4);
	free(s2);
	free(s3);
	free(s4);
	return (s5);
}

static char *get_arg_string(char *token)
{
	int i = 0;
	char *res = NULL;
	while(token && token[i] && ft_isspace(token[i]))
		i++;
	while(token && token[i] && !ft_isspace(token[i]))
		i++;
	while(token && token[i] && ft_isspace(token[i]))
		i++;
	while(token && token[i] && !ft_isspace(token[i]))
		i++;
	if(!token[i])
		return (NULL);
	res = ft_strnmdup(token, i, ft_strlen(token));
	return (res);
}


