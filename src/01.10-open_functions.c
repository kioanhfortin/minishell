/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01.06_cmd_table3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmiyakaw <gmiyakaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 14:02:18 by gmiyakaw          #+#    #+#             */
/*   Updated: 2023/08/02 14:02:46 by gmiyakaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	open_append(t_cmd *cmd, int i)
{
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
	return (0);
}

int	open_heredoc(t_cmd *cmd, int i)
{
	if (cmd->fd_input > 0)
		close(cmd->fd_input);
	just_here_docking(cmd, i);
	if (cmd->fd_input < 0)
	{
		perror(OPN_ERR);
		return (1);
	}
	cmd->input_type = HEREDOC;
	return (0);
}

int	open_redir_in(t_cmd *cmd, int i)
{
	if (cmd->fd_input > 0)
		close(cmd->fd_input);
	cmd->fd_input = open(cmd->cmd_tokens[i + 1].arg, O_RDONLY, 0644);
	if (cmd->fd_input < 0)
	{
		perror(OPN_ERR);
		return (1);
	}
	cmd->input_type = REDIR_IN;
	return (0);
}

int	open_redir_out(t_cmd *cmd, int i)
{
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
	return (0);
}
