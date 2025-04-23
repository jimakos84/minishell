/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 13:06:04 by tsomacha          #+#    #+#             */
/*   Updated: 2025/04/23 13:06:31 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

int	syntax_error(char *input, char *msg, int code)
{
	free(input);
	ft_putendl_fd(msg, 2);
	return (code);
}
