/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfortin <kfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 14:27:59 by kfortin           #+#    #+#             */
/*   Updated: 2023/08/05 12:39:26 by kfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	our_exit(t_cmd *cmd)
{
	if (ft_tchek_arg_exit(cmd) == 1)
	{
		g_exit_v = ft_atoll(cmd->args[1]);
		if (g_exit_v > 255 || g_exit_v < 0)
			g_exit_v = g_exit_v % 256;
		ft_close_all();
		if (cmd->data)
			cmd->data = free_data_struct(cmd->data);
		exit(g_exit_v);
	}
	return (g_exit_v);
}

int	ft_tchek_arg_exit(t_cmd *cmd)
{
	long long	num;

	num = 0;
	if (cmd->cmd_token_count == 1)
	{
		ft_close_all();
		if (cmd->data)
			free_data_struct(cmd->data);
		exit(g_exit_v);
	}
	num = ft_atoll(cmd->args[1]);
	if (cmd->cmd_token_count > 1)
	{
		ft_int_num(cmd, num);
		if (cmd->cmd_token_count > 2)
		{
			ft_tk_count_2(cmd);
			return (0);
		}
	}
	return (1);
}

void	ft_int_num(t_cmd *cmd, long long num)
{
	if (ft_str_is_numeric(cmd->args[1]) == 0 || num > 9223372036854775807
		|| (num < -9223372036854775807 && ft_max_min_longlong(cmd) == 0)
		|| ft_min_longlong(cmd) == 1)
	{
		g_exit_v = 2;
		ft_putstr_fd("minishell: exit: numeric argument required\n",
			cmd->data->fd[cmd->data->pos_cmd_i][1]);
		ft_close_all();
		if (cmd->data)
			free_data_struct(cmd->data);
		exit(g_exit_v);
	}
}

void	ft_tk_count_2(t_cmd *cmd)
{
	char	*str;

	str = NULL;
	str = ft_tchek_if_quoted(cmd);
	if (str != NULL)
	{
		g_exit_v = atoi(str);
		free(str);
		ft_close_all();
		if (cmd->data)
			free_data_struct(cmd->data);
		exit(g_exit_v);
	}
	else
	{
		g_exit_v = 1;
		ft_putstr_fd("bash: exit: too many arguments\n",
			cmd->data->fd[cmd->data->pos_cmd_i][1]);
	}
}

int	ft_max_min_longlong(t_cmd *cmd)
{
	if (ft_strcmp(cmd->args[1], "-9223372036854775808") == 0)
		return (1);
	return (0);
}
