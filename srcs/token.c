/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:37:44 by tsomacha          #+#    #+#             */
/*   Updated: 2025/04/23 16:44:32 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

t_list	*list_add_back(t_list *list, char *str);

int	extract_tokens(t_list **tokens, char *input)
{
	int		i;
	char	*line;
	char	**words;

	i = 0;
	line = ft_strtrim(input, " ");
	words = ft_split(line, '|');
	while (words && words[i])
	{
		*tokens = list_add_back(*tokens, ft_strtrim(words[i], " "));
		i++;
	}
	return (0);
}

t_list	*list_add_back(t_list *list, char *str)
{
	t_list	*node;
	t_list	*current;

	node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->next = NULL;
	node->token = ft_strdup(str);
	if (!list)
		return (node);
	current = list;
	while (current && current->next)
		current = current->next;
	current->next = node;
	return (list);
}

t_cmd	*list_add_command(t_cmd *cmds, t_cmd *node)
{
	t_cmd	*current;

	if (!node)
		return (cmds);
	if (!cmds)
		return (node);
	current = cmds;
	while (current && current->next)
		current = current->next;
	current->next = node;
	return (cmds);
}
