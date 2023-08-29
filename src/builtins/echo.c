/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfortin <kfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 11:09:42 by kfortin           #+#    #+#             */
/*   Updated: 2023/08/05 10:27:21 by kfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	our_echo(t_cmd *cmd)
{
	int	i;

	i = 1;
	if (cmd->args[i])
	{
		if (ft_if_flag(cmd, i) == 1 && cmd->flag_echo == 0)
		{
			cmd->flag_echo = 1;
			cmd->flag2_echo = 1;
			i++;
			while (cmd->args[i] && ft_if_flag(cmd, i) == 1
				&& cmd->flag_echo == 1)
				i++;
		}
		i = ft_put_space(cmd, i, cmd->flag2_echo);
	}
	else
	{
		ft_put_n(cmd->flag_echo);
		return (1);
	}
	ft_put_n(cmd->flag_echo);
	return (0);
}

void	ft_put_n(int flag)
{
	if (flag == 0)
		ft_printf("\n");
}

int	ft_put_space(t_cmd *cmd, int i, int flag2)
{
	while (cmd->args[i])
	{
		if (i > 1 && cmd->data->tok_ch[i].w_space_between == 1)
		{
			if (flag2 == 0)
			{
				ft_putchar_fd(' ', cmd->data->fd[cmd->data->pos_cmd_i][1]);
			}
		}
		ft_putstr_fd(cmd->args[i], cmd->data->fd[cmd->data->pos_cmd_i][1]);
		flag2 = 0;
		i++;
	}
	return (i);
}
