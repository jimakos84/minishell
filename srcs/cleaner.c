/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:52:11 by tsomacha          #+#    #+#             */
/*   Updated: 2025/04/23 11:54:54 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

int	clear_commands(t_cmd *cmds);
int	clear_tokens(t_list *tokens);
int	clear_array(char **array);

int	clear_and_exit(t_shell *mini)
{
	clear_commands(mini->cmds);
	clear_tokens(mini->tokens);
	return (0);
}

int	clear_commands(t_cmd *cmds)
{
	t_cmd	*current;
	t_cmd	*cmd;

	current = cmds;
	while (current)
	{
		cmd = current;
		current = current->next;
		free(cmd->command);
	}
	return (0);
}

int	clear_tokens(t_list *tokens)
{
	t_list	*current;
	t_list	*token;

	current = tokens;
	while (current)
	{
		token = current;
		current = current->next;
		free(token);
	}
	return (0);
}

int	clear_array(char **array)
{
	int	i;

	i = 0;
	while (array && array[i])
	{
		if (array[i])
			free(array[i]);
		i++;
	}
	if (array)
		free(array);
	return (0);
}
