/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utilis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfortin <kfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 16:37:37 by kfortin           #+#    #+#             */
/*   Updated: 2023/08/05 10:22:17 by kfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_if_flag(t_cmd *cmd, int i)
{
	int	j;

	j = 2;
	if (cmd->args[i][0] == '-' && cmd->args[i][1] == 'n')
	{
		while (cmd->args[i][j])
		{
			if (cmd->args[i][j] != 'n')
				return (0);
			j++;
		}
		return (1);
	}
	return (0);
}
