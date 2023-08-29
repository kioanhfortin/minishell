/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02.04-single_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfortin <kfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 17:31:56 by kfortin           #+#    #+#             */
/*   Updated: 2023/08/05 17:53:01 by kfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_single_cmd(t_data *data)
{
	int	status;
	int	pid;

	pid = 0;
	ft_init_fd(data);
	if (ft_is_built_ins_yes(data) == 0)
	{
		if (data->cmd_list[0].args[0] == NULL
			|| data->cmd_list[0].cmd_path == NULL
			|| is_path_unset(data) == true)
		{
			ft_putstr_fd("bash: command not found\n", 2);
			g_exit_v = 127;
			ft_close_all();
		}
		else
			pid = ft_single_cmd_child(data, pid);
	}
	else
		ft_single_cmd_builtins(data);
	dup2(data->back_up_out, STDOUT_FILENO);
	dup2(data->back_up_in, STDIN_FILENO);
	waitpid(pid, &status, 0);
	g_exit_v = WEXITSTATUS(g_exit_v);
}

void	set_exit_code(t_data *data, int status)
{
	if (status != 0 && ft_is_built_ins_yes(data) == 0)
		g_exit_v = status % 256;
	else
		g_exit_v = 0;
	return ;
}

void	ft_single_cmd_builtins(t_data *data)
{
	int	error;

	error = 1;
	ft_fill_fds_single(data);
	error = ft_is_built_ins_all(data);
	if (error == 0)
		g_exit_v = 0;
}

int	ft_single_cmd_child(t_data *data, int pid)
{
	pid = fork();
	if (pid == 0)
	{
		ft_fill_fds_single(data);
		ft_close_all();
		data->cmd_list[0].args = join_args(&data->cmd_list[0]);
		g_exit_v = execve(data->cmd_list[0].cmd_path, data->cmd_list[0].args,
				data->envp);
		if (data)
			free_data_struct(data);
		exit(g_exit_v);
	}
	return (pid);
}

void	ft_fill_fds_single(t_data *data)
{
	data->back_up_out = dup(STDOUT_FILENO);
	data->back_up_in = dup(STDIN_FILENO);
	if (data->cmd_list[0].input_type == REDIR_IN
		|| data->cmd_list[0].input_type == HEREDOC)
	{
		data->fd[0][0] = data->cmd_list[0].fd_input;
		dup2(data->cmd_list[0].fd_input, STDIN_FILENO);
	}
	if (data->cmd_list[0].output_type == REDIR_OUT
		|| data->cmd_list[0].output_type == APPEND)
	{
		data->fd[0][1] = data->cmd_list[0].fd_output;
		dup2(data->cmd_list[0].fd_output, STDOUT_FILENO);
	}
}
