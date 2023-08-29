/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02.05-execution_utilis.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfortin <kfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 21:01:35 by kfortin           #+#    #+#             */
/*   Updated: 2023/08/05 12:17:21 by kfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_init_fd(t_data *data)
{
	int	i;

	i = 0;
	data->fd = ft_calloc(sizeof(int *), data->cmd_count);
	if (!data->fd)
		return (-1);
	while (i < data->cmd_count)
	{
		data->fd[i] = ft_calloc(sizeof(int), 2);
		i++;
	}
	return (0);
}

void	ft_close_all(void)
{
	int	i;

	i = 3;
	while (i < 200)
	{
		close(i);
		i++;
	}
}

void	ft_fill_fds(t_data *data)
{
	dup2(data->back_up_out, STDOUT_FILENO);
	dup2(data->back_up_in, STDIN_FILENO);
	ft_all_fd_in(data);
	ft_all_fd_out(data);
}

void	ft_all_fd_in(t_data *data)
{
	if (data->pos_cmd_i > 0 && (data->cmd_list[data->pos_cmd_i
				- 1].output_type == REDIR_OUT || data->cmd_list[data->pos_cmd_i
				- 1].output_type == APPEND))
		dup2(data->fd[data->pos_cmd_i][0], data->cmd_list[data->pos_cmd_i
			- 1].fd_output);
	if (data->cmd_list[data->pos_cmd_i].input_type == REDIR_IN
		|| data->cmd_list[data->pos_cmd_i].input_type == HEREDOC)
	{
		data->fd[data->pos_cmd_i][0]
			= data->cmd_list[data->pos_cmd_i].fd_input;
		dup2(data->cmd_list[data->pos_cmd_i].fd_input, STDIN_FILENO);
	}
	else
	{
		if (data->pos_cmd_i == 0)
		{
			data->fd[data->pos_cmd_i][0] = 0;
			dup2(data->fd[data->pos_cmd_i][0], STDIN_FILENO);
		}
		else
			dup2(data->fd[data->pos_cmd_i - 1][0], STDIN_FILENO);
	}
}

void	ft_all_fd_out(t_data *data)
{
	if (data->cmd_list[data->pos_cmd_i].output_type == REDIR_OUT
		|| data->cmd_list[data->pos_cmd_i].output_type == APPEND)
	{
		data->fd[data->pos_cmd_i][1]
			= data->cmd_list[data->pos_cmd_i].fd_output;
		dup2(data->cmd_list[data->pos_cmd_i].fd_output, STDOUT_FILENO);
	}
	else
	{
		if (data->pos_cmd_i == data->cmd_count - 1)
		{
			data->fd[data->pos_cmd_i][1] = 1;
			dup2(data->fd[data->pos_cmd_i][1], STDOUT_FILENO);
		}
		else
			dup2(data->fd[data->pos_cmd_i][1], STDOUT_FILENO);
	}
}
