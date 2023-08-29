/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfortin <kfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 10:20:55 by gmiyakaw          #+#    #+#             */
/*   Updated: 2023/08/05 10:27:47 by kfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	our_unset(t_cmd *cmd)
{
	int		i;
	int		j;
	char	*env_alias;

	i = 0;
	cmd->error = 0;
	while (cmd->args[++i])
	{
		j = 0;
		while (cmd->data->envp[j])
		{
			env_alias = get_alias(cmd->data->envp[j]);
			if (ft_strncmp(cmd->args[i], env_alias,
					ft_strlen(cmd->args[i])) == 0)
				cmd->data->envp = ft_rm_str(cmd->data->envp, j);
			env_alias = x_free(env_alias);
			j++;
			if (j > ft_arrlen(cmd->data->envp))
			{
				cmd->error++;
				break ;
			}
		}
	}
	return (cmd->error);
}
