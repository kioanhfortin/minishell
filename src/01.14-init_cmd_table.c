/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01.14-init_cmd_table.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfortin <kfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 20:39:36 by kfortin           #+#    #+#             */
/*   Updated: 2023/08/04 20:42:29 by kfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	init_cmds(t_data *data)
{
	int	i;

	data->cmd_list = x_calloc(sizeof(t_cmd) * data->cmd_count);
	if (!data->cmd_list)
	{
		perror(MLLC_ERR);
		return (1);
	}
	i = -1;
	while (++i < data->cmd_count)
		ft_init_cmd_var(data, i);
	return (0);
}

void	ft_init_cmd_var(t_data *data, int i)
{
	data->cmd_list[i].args = NULL;
	data->cmd_list[i].cmd_path = NULL;
	data->cmd_list[i].cmd_token_count = 0;
	data->cmd_list[i].fd_input = -1;
	data->cmd_list[i].fd_output = -1;
	data->cmd_list[i].input_type = WORD;
	data->cmd_list[i].output_type = WORD;
	data->cmd_list[i].data = data;
	data->cmd_list[i].no_built = 0;
	data->cmd_list[i].flag_echo = 0;
	data->cmd_list[i].flag2_echo = 0;
	data->cmd_list[i].error = 0;
	data->cmd_list[i].i = 0;
	data->cmd_list[i].j = 0;
}
