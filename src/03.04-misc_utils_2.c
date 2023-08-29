/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03.04-mic_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfortin <kfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 12:30:39 by kfortin           #+#    #+#             */
/*   Updated: 2023/08/05 12:31:17 by kfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**cmd_rmv_empty(t_cmd *cmd)
{
	int	i;

	i = -1;
	while (cmd->args[++i])
	{
		if (ft_strcmp(cmd->args[i], "") == 0)
		{
			cmd->args = ft_rm_str(cmd->args, i);
			i = 0;
		}
	}
	return (cmd->args);
}
