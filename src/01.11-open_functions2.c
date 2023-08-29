/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01.11-open_functions2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmiyakaw <gmiyakaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 14:13:54 by gmiyakaw          #+#    #+#             */
/*   Updated: 2023/08/02 14:19:48 by gmiyakaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	set_cmd_fds(t_cmd *cmd)
{
	if (open_inputs(cmd) != 0)
		return (1);
	if (open_outputs(cmd) != 0)
		return (2);
	else
		return (0);
}

int	open_inputs(t_cmd *cmd)
{
	int	i;

	i = -1;
	while (++i < cmd->cmd_token_count)
	{
		if (cmd->cmd_tokens[i].type == REDIR_IN)
		{
			if (open_redir_in(cmd, i) != 0)
				return (1);
		}
		if (cmd->cmd_tokens[i].type == HEREDOC)
		{
			if (open_heredoc(cmd, i) != 0)
				return (2);
		}
	}
	return (0);
}

int	open_outputs(t_cmd *cmd)
{
	int	i;

	i = -1;
	while (++i < cmd->cmd_token_count)
	{
		if (cmd->cmd_tokens[i].type == REDIR_OUT)
		{
			if (open_redir_out(cmd, i) != 0)
				return (1);
		}
		if (cmd->cmd_tokens[i].type == APPEND)
		{
			if (open_append(cmd, i) != 0)
				return (2);
		}
	}
	return (0);
}

/*
											OLDER VERSIONS OF SET CMD FDS. AUG 2
	if (cmd->fd_input > 0)
		close(cmd->fd_input);
	cmd->fd_input = open(cmd->cmd_tokens[i + 1].arg, O_RDONLY, 0644);
	if (cmd->fd_input < 0)
	{
		perror(OPN_ERR);
		return (1);
	}
	cmd->input_type = REDIR_IN;

	if (cmd->fd_output > 0)
		close(cmd->fd_output);
	cmd->fd_output = open(cmd->cmd_tokens[i + 1].arg, \
		O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (cmd->fd_output < 0)
	{
		perror(OPN_ERR);
		return (1);
	}
	cmd->output_type = REDIR_OUT;

	if (cmd->fd_input > 0)
		close(cmd->fd_input);
	just_here_docking(cmd, i);
	if (cmd->fd_input < 0)
	{
		perror(OPN_ERR);
		return (1);
	}
	cmd->input_type = HEREDOC;
	
	if (cmd->fd_output > 0)
		close (cmd->fd_output);
	cmd->fd_output = open(cmd->cmd_tokens[i + 1].arg, \
		O_RDWR | O_APPEND | O_CREAT, 0666);
	if (cmd->fd_output < 0)
	{
		perror(OPN_ERR);
		return (1);
	}
			cmd->output_type = APPEND;
*/

// int	set_cmd_fds(t_cmd *cmd)
// {
// 	int	i;

// 	i = -1;
// 	while (++i < cmd->cmd_token_count)
// 	{
// 		if (cmd->cmd_tokens[i].type == REDIR_IN)
// 		{
// 			if (open_redir_in(cmd, i) != 0)
// 				return (1);
// 		}
// 		if (cmd->cmd_tokens[i].type == REDIR_OUT)
// 		{
// 			if (open_redir_out(cmd, i) != 0)
// 				return (2);
// 		}
// 		if (cmd->cmd_tokens[i].type == HEREDOC)
// 		{
// 			if (open_heredoc(cmd, i) != 0)
// 				return (3);
// 		}
// 		if (cmd->cmd_tokens[i].type == APPEND)
// 		{
// 			if (open_append(cmd, i) != 0)
// 				return (4);
// 		}
// 	}
// 	return (0);
// }
