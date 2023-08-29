/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02.02-execution_builtins.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfortin <kfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 16:00:58 by kfortin           #+#    #+#             */
/*   Updated: 2023/08/05 12:57:27 by kfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_is_built_ins_yes(t_data *data)
{
	const char	*str[7] = {"echo", "export", "cd", "pwd",
		"unset", "env", "exit"};

	data->count = 0;
	while (data->count < 7)
	{
		if (ft_strcmp(ft_str_min(data->cmd_list[data->pos_cmd_i].args[0]),
				str[data->count]) == 0)
			return (1);
		data->count++;
	}
	return (0);
}

char	*ft_str_min(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
			str[i] += 32;
		i++;
	}
	return (str);
}

int	ft_is_built_ins_all(t_data *data)
{
	const char	*str[7] = {"echo", "export", "cd", "pwd",
		"env", "exit", "unset"};
	int			(*built_tab[7])(t_cmd *);

	built_tab[0] = our_echo;
	built_tab[1] = our_export;
	built_tab[2] = our_cd;
	built_tab[3] = our_pwd;
	built_tab[4] = our_env;
	built_tab[5] = our_exit;
	built_tab[6] = our_unset;
	data->count = -1;
	while (++data->count < 7)
	{
		if (ft_strcmp(ft_str_min(data->cmd_list[data->pos_cmd_i].args[0]),
				"export") == 0
			&& data->cmd_list[data->pos_cmd_i].cmd_token_count == 1)
			return (ft_exec_export_no_arg(data));
		if (ft_strcmp(ft_str_min(data->cmd_list[data->pos_cmd_i].args[0]),
				str[data->count]) == 0)
			g_exit_v
				= (built_tab[data->count])(&data->cmd_list[data->pos_cmd_i]);
	}
	return (-1);
}

int	ft_exec_export_no_arg(t_data *data)
{
	export_no_arg(data);
	ft_close_all();
	if (data->cmd_count != 1)
	{
		data = free_data_struct(data);
		exit(0);
	}
	return (data->count);
}
