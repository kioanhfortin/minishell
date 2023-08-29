/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02.01-execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfortin <kfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 14:16:40 by gmiyakaw          #+#    #+#             */
/*   Updated: 2023/08/05 17:12:39 by kfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_multi_pipe(t_data *data)
{
	int	status;
	int	k;

	data->pos_cmd_i = 0;
	k = 0;
	ft_init_fd(data);
	data->pid = ft_calloc(sizeof(int), data->cmd_count + 1);
	if (!data->pid)
		return ;
	while (data->pos_cmd_i < data->cmd_count)
	{
		ft_run_process(data);
		data->pos_cmd_i++;
	}
	while (k < data->cmd_count)
	{
		waitpid(data->pid[k], &status, 0);
		g_exit_v = WEXITSTATUS(g_exit_v);
		if (status != 0)
			g_exit_v = status - 255;
		k++;
	}
}

void	ft_run_process(t_data *data)
{
	if (data->cmd_count > 1)
		pipe(data->fd[data->pos_cmd_i]);
	data->pid[data->pos_cmd_i] = fork();
	if (data->pid[data->pos_cmd_i] < 0)
	{
		perror("fork error");
		return ;
	}
	if (data->pid[data->pos_cmd_i] == 0)
	{
		ft_fill_fds(data);
		if (data->cmd_list[data->pos_cmd_i].no_built == 0)
			data->cmd_list[data->pos_cmd_i].no_built = ft_is_built_ins(data);
		if (data->cmd_list[data->pos_cmd_i].no_built == -2)
		{
			ft_child_part_2(data);
			if (data->pos_cmd_i + 1 == data->cmd_count)
				return ;
		}
	}
	else
		ft_parent(data);
	dup2(data->back_up_out, STDOUT_FILENO);
	dup2(data->back_up_in, STDIN_FILENO);
}

void	ft_parent(t_data *data)
{
	if (data->cmd_list[data->pos_cmd_i].no_built == 0)
	{
		data->cmd_list[data->pos_cmd_i].no_built = ft_is_built_ins_parent(data);
		g_exit_v = 0;
	}
	if (data->pos_cmd_i < data->cmd_count - 1)
	{
		close(data->fd[data->pos_cmd_i][1]);
		dup2(data->fd[data->pos_cmd_i + 1][0], STDIN_FILENO);
	}
}

void	ft_child_part_2(t_data *data)
{
	if (ft_is_built_ins_yes(data) == 0)
	{
		if (data->cmd_list[data->pos_cmd_i].args[0] == NULL
			|| data->cmd_list[data->pos_cmd_i].cmd_path == NULL
			|| is_path_unset(data) == true)
		{
			ft_putstr_fd("minishell: command not found\n", 2);
			ft_close_all();
			if (data)
				free_data_struct(data);
			g_exit_v = 127;
			exit(g_exit_v);
		}
		else
		{
			ft_close_all();
			data->cmd_list[0].args = join_args(&data->cmd_list[0]);
			g_exit_v = execve(data->cmd_list[data->pos_cmd_i].cmd_path,
					data->cmd_list[data->pos_cmd_i].args, data->envp);
			exit(g_exit_v);
		}
	}
}
