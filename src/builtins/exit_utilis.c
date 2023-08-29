/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utilis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfortin <kfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 12:57:05 by kfortin           #+#    #+#             */
/*   Updated: 2023/08/05 12:39:06 by kfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_check_max_min(t_cmd *cmd)
{
	if (ft_is_int(cmd->args[1]) == 0)
	{
		g_exit_v = 2;
		ft_putstr_fd("bash: exit: numeric argument required\n",
			cmd->data->fd[cmd->data->pos_cmd_i][1]);
		ft_close_all();
		if (cmd->data)
			free_data_struct(cmd->data);
		exit(g_exit_v);
	}
	else
	{
		g_exit_v = 255;
		ft_close_all();
		if (cmd->data)
			free_data_struct(cmd->data);
		exit(g_exit_v);
	}
}

int	ft_is_int(char *str)
{
	long long	num;

	num = ft_atoll(str);
	if (num >= -9223372036854775807 && num <= 9223372036854775807)
	{
		return (1);
	}
	return (0);
}

long long	ft_atoll(const char *str)
{
	int			i;
	long long	n;
	int			sign;

	i = 0;
	n = 0;
	sign = 1;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		i++;
	if (str[i] == '-')
		sign *= -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		n = (n * 10 + str[i++]) - '0';
	return (n * sign);
}

char	*ft_tchek_if_quoted(t_cmd *cmd)
{
	int		i;
	char	*str;

	i = 0;
	str = NULL;
	while (i < cmd->cmd_token_count)
	{
		if ((ft_str_is_numeric(cmd->args[i]) == 1))
		{
			if (i == 1)
				str = ft_strdup(cmd->args[i]);
			else
				str = ft_strjoin(str, cmd->args[i]);
		}
		i++;
	}
	return (str);
}

int	ft_str_is_numeric(char *str)
{
	int	i;
	int	multi_sign;

	i = 0;
	multi_sign = 0;
	while (str[i])
	{
		if (str[i] == '-' || str[i] == '+')
			multi_sign += 1;
		if (!((str[i] >= '0' && str[i] <= '9') || str[i] == '-'
				|| str[i] == '+'))
		{
			return (0);
		}
		i++;
	}
	if (multi_sign > 1)
		return (0);
	return (1);
}
