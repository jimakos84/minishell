#include "../includes/shell.h"

t_list *list_add_back(t_list *list, char *str);

int extract_tokens(t_list **tokens, char *input)
{
	int i = 0;
	
	/**
	 * first trying to extract a token bas on space/(' ')/ASCII INT 32 character
	*/
	char *line = ft_strtrim(input, " ");
	char **words = ft_split(line, '|');
	while(words && words[i])
	{
		*tokens = list_add_back(*tokens, ft_strtrim(words[i], " "));
		i++;
	}
	return (0);
}

t_list *list_add_back(t_list *list, char *str)
{
	t_list *node = malloc(sizeof(t_list)), *current;
	if(!node)
		return (NULL);
	node->next = NULL;
	node->token = ft_strdup(str);
	if(!list)
		return (node);
	current = list;
	while(current && current->next)
		current = current->next;
	current->next = node;
	return (list);
}

t_cmd *list_add_command(t_cmd *cmds, t_cmd *node)
{
	t_cmd *current;
	if(!node)
		return (cmds);
	if(!cmds)
		return (node);
	current = cmds;
	while(current && current->next)
		current = current->next;
	current->next = node;
	return (cmds);
}

int	tokenize(t_shell *mini, char *input)
{
	char	buffer[1024];
	int		buf_i;
	int		token_i;
	int		i;
	char	quote;

	buf_i = 0;
	token_i = 0;
	i = 0;
	mini->tokensar = malloc(1024 * sizeof(char *));
	if (!mini->tokensar)
		return (1);
	if (mini->trim)
		free(mini->trim);
	mini->trim = ft_strtrim(input, " \t\n\r\v");
	if (quotes_checker(mini->trim, ft_strlen(mini->trim)))
	{
		ft_putstr_fd("Error: Unmatched quotes\n", 2);
		free(mini->tokensar);
		return (1);
	}
	while (mini->trim[i])
	{
		if (mini->trim[i] == '\'' || mini->trim[i] == '"')
		{
			quote = mini->trim[i];
			i++;
			while (mini->trim[i] && mini->trim[i] != quote)
			{
				if (mini->trim[i] == '\\' && quote == '"')
				{
					i++;
					if (mini->trim[i])
						buffer[buf_i++] = mini->trim[i];
				}
				else
					buffer[buf_i++] = mini->trim[i];
				i++;
			}
			i++;
		}
		else if (ft_isspace(mini->trim[i]))
		{
			if (buf_i > 0)
			{
				buffer[buf_i] = '\0';
				mini->tokensar[token_i++] = ft_strdup(buffer);
				buf_i = 0;
			}
			i++;
		}
		else if (mini->trim[i] == '\\')
		{
			i++;
			if (mini->trim[i])
				buffer[buf_i++] = mini->trim[i];
			i++;
		}
		else
		{
			buffer[buf_i++] = mini->trim[i];
			i++;
		}
	}
	if (buf_i > 0)
	{
		buffer[buf_i] = '\0';
		mini->tokensar[token_i++] = ft_strdup(buffer);
	}
	mini->tokensar[token_i] = NULL;
	return (0);
}