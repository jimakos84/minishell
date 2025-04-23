/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:57:23 by tsomacha          #+#    #+#             */
/*   Updated: 2025/04/23 15:02:39 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

static char	*get_heredoc_delimeter(char *token);
static int	init_heredoc(char *delimeter);

t_cmd	*handle_heredoc(t_shell *mini, t_cmd *cmd, char *token)
{
	char	*delimeter;
	char	*str;
	char	*temp;
	char	*new_token;

	str = ft_strchr(token, '<');
	temp = ft_strnmdup(token, 0, str - token);
	new_token = ft_strtrim(temp, " \f\n\t\v\r");
	cmd->type = set_command_type(token);
	cmd->command = set_path_name(mini, new_token);
	cmd->filename = ft_strdup(CACHE);
	cmd->cmd = get_command(new_token);
	cmd->num_args = get_num_args(new_token);
	cmd->args = set_arg_array(cmd->num_args, new_token, cmd->command);
	cmd->next = NULL;
	delimeter = get_heredoc_delimeter(token);
	init_heredoc(delimeter);
	return (cmd);
}

static int	init_heredoc(char *delimeter)
{
	int		fd;
	char	*pmpt;

	pmpt = NULL;
	fd = open(CACHE, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd == -1)
	{
		perror("Failed to cached the input!");
		exit(1);
	}
	pmpt = readline(">");
	while (pmpt != NULL)
	{
		if (ft_strncmp(delimeter, pmpt, ft_strlen(delimeter)) == 0)
		{
			free(pmpt);
			break ;
		}
		write(fd, pmpt, ft_strlen(pmpt));
		write(fd, "\n", 2);
		free(pmpt);
		pmpt = readline(">");
	}
	close(fd);
	return (1);
}

static char	*get_heredoc_delimeter(char *token)
{
	int		i;
	char	*str;
	char	*dem;

	i = 0;
	str = ft_strchr(token, '<');
	while (str && str[i] && str[i] == '<')
		i++;
	while (str && str[i] && ft_isspace(str[i]))
		i++;
	dem = ft_strnmdup(str, i, ft_strlen(str));
	return (dem);
}
