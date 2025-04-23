/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:22:27 by tsomacha          #+#    #+#             */
/*   Updated: 2025/04/23 14:38:30 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

static void	init_mini_shell(t_shell *mini, t_initenv *env);

int	activate_shell(char *input, t_initenv *env)
{
	int		status;
	t_shell	*mini;

	status = 0;
	mini = malloc(sizeof(t_shell));
	if (!mini)
		return (1);
	init_mini_shell(mini, env);
	status = input_validate(&input);
	if (status)
		return (status);
	status = extract_tokens(&mini->tokens, input);
	if (status)
		return (status);
	status = parse_and_expand(mini);
	if (status)
		return (status);
	status = execute(mini);
	if (status)
		return (status);
	status = clear_and_exit(mini);
	if (status)
		return (status);
	return (status);
}

static void	init_mini_shell(t_shell *mini, t_initenv *env)
{
	mini->num_cmds = 0;
	mini->tokens = NULL;
	mini->cmds = NULL;
	mini->initenv = env;
	mini->trim = NULL;
	mini->status = 0;
}
