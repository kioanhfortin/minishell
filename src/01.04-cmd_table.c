/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01.04-cmd_table.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfortin <kfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 11:05:45 by gmiyakaw          #+#    #+#             */
/*   Updated: 2023/08/05 14:50:53 by kfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	make_cmd_tokens(t_data *data, t_token *tok_ch)
{
	int	start;
	int	end;
	int	i;

	i = 0;
	start = 0;
	end = -1;
	while (++end < (data->token_count))
	{
		if (tok_ch[end].type == PIPE)
		{
			end--;
			data->cmd_list[i].cmd_tokens = clone_tok_ch(data, start, end,
					&data->cmd_list[i].cmd_token_count);
			i++;
			end += 2;
			start = end;
		}
		if (end == (data->token_count - 1))
			data->cmd_list[i].cmd_tokens = clone_tok_ch(data, start, end,
					&data->cmd_list[i].cmd_token_count);
	}
	return (0);
}

int	parse_cmds(t_cmd *cmd_list, int cmd_count, char **paths)
{
	int	i;

	i = -1;
	while (++i < cmd_count)
	{
		if (set_cmd_fds(&cmd_list[i]) != 0)
			return (1);
		if (set_cmd_args(&cmd_list[i]) != 0)
			return (2);
		cmd_list[i].cmd_path = cmd_pathfinder(&cmd_list[i], paths);
		if (is_path_a_variable(&cmd_list[i]) == true)
			return (3);
	}
	return (0);
}

/*
because access only shows if that address exists and has 
permission to execute we need this check to verify that path 
is indeed a correct one. Naming the command a variable in the env 
would cause it to trigger as a valid command_path, which it isnt,
triggering an invalid free bug down the line. AUG 4
*/
bool	is_path_a_variable(t_cmd *cmd)
{
	if (cmd->cmd_tokens[0].is_exp == 1)
	{
		if (access(cmd->cmd_path, F_OK | X_OK) == 0)
			return (true);
	}
	return (false);
}

int	set_cmd_args(t_cmd *cmd)
{
	int	i;
	int	j;
	int	arg_count;

	i = 0;
	j = 0;
	arg_count = get_cmd_argcount(cmd);
	cmd->args = ft_calloc(sizeof(char *), arg_count + 1);
	if (!cmd->args)
		return (ft_error_set_arg());
	while (i < cmd->cmd_token_count)
	{
		if (cmd->cmd_tokens[i].type != WORD)
		{
			i += 2;
			if (i >= cmd->cmd_token_count)
				break ;
		}
		cmd->args[j++] = ft_strdup(cmd->cmd_tokens[i++].arg);
	}
	cmd->args[j] = NULL;
	if (j == 0)
		return (2);
	return (0);
}

int	ft_error_set_arg(void)
{
	perror(MLLC_ERR);
	return (-1);
}
