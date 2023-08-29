/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02.06-execution_builtins_2.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfortin <kfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 09:44:08 by kfortin           #+#    #+#             */
/*   Updated: 2023/08/05 12:58:03 by kfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

long long	ft_is_built_ins(t_data *data)
{
	const char	*str[4] = {"echo", "env", "pwd", "cd"};
	int			(*built_tab[4])(t_cmd *);

	built_tab[0] = our_echo;
	built_tab[1] = our_env;
	built_tab[2] = our_pwd;
	built_tab[3] = our_cd;
	data->count = 0;
	while (data->count < 4)
	{
		if (ft_strcmp(ft_str_min(data->cmd_list[data->pos_cmd_i].args[0]), \
			"export") == 0 \
				&& data->cmd_list[data->pos_cmd_i].cmd_token_count == 1)
			return (ft_execute_export_no_arg(data));
		if (ft_strcmp(ft_str_min(data->cmd_list[data->pos_cmd_i].args[0]),
				str[data->count]) == 0)
		{
			g_exit_v
				= (built_tab[data->count])(&data->cmd_list[data->pos_cmd_i]);
			return (ft_close_exit(data));
		}
		data->count++;
	}
	return (-2);
}

long long	ft_close_exit(t_data *data)
{
	ft_close_all();
	if (data->cmd_count != 1)
	{
		data = free_data_struct(data);
		exit(g_exit_v);
	}
	return (g_exit_v);
}

long long	ft_execute_export_no_arg(t_data *data)
{
	g_exit_v = export_no_arg(data);
	ft_close_all();
	if (data->cmd_count != 1)
	{
		data = free_data_struct(data);
		exit(g_exit_v);
	}
	return (g_exit_v);
}

int	ft_is_built_ins_parent(t_data *data)
{
	const char	*str[2] = {"exit", "unset"};
	int			(*built_tab[2])(t_cmd *);

	built_tab[0] = our_exit;
	built_tab[1] = our_unset;
	data->count = 0;
	while (data->count < 2)
	{
		if (ft_strcmp(ft_str_min(data->cmd_list[data->pos_cmd_i].args[0]),
				str[data->count]) == 0)
		{
			if (ft_strcmp(ft_str_min(data->cmd_list[data->pos_cmd_i].args[0]),
					"export") == 0
				&& data->cmd_list[data->pos_cmd_i].cmd_token_count == 1)
				return (-1);
			g_exit_v
				= (built_tab[data->count])(&data->cmd_list[data->pos_cmd_i]);
			return (-3);
		}
		data->count++;
	}
	return (-1);
}
