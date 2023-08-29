/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01.05-cmd_table2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfortin <kfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 11:07:00 by gmiyakaw          #+#    #+#             */
/*   Updated: 2023/08/05 14:46:05 by kfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_cmd_argcount(t_cmd *cmd)
{
	int	arg_count;
	int	i;

	i = -1;
	arg_count = cmd->cmd_token_count + 1;
	while (++i < cmd->cmd_token_count)
	{
		if (cmd->cmd_tokens[i].type != WORD)
		{
			i += 2;
			arg_count -= 2;
		}
	}
	return (arg_count);
}

char	*cmd_pathfinder(t_cmd *cmd, char **paths)
{
	int		i;
	char	*tmp;
	char	*res;

	if (is_absolute(cmd->args[0]) == true)
		return (ft_strdup(cmd->args[0]));
	i = -1;
	while (paths[++i])
	{
		tmp = ft_strjoin(paths[i], "/");
		res = ft_strjoin(tmp, cmd->args[0]);
		tmp = x_free(tmp);
		if (access(res, F_OK | X_OK) == 0)
		{
			return (res);
		}
		res = x_free(res);
	}
	return (NULL);
}

bool	is_path_unset(t_data *data)
{
	int	i;

	i = 0;
	while (data->envp[i])
	{
		if (strncmp("PATH=", data->envp[i], 5) == 0)
			return (false);
		i++;
	}
	return (true);
}

bool	is_absolute(char *arg)
{
	if (access(arg, F_OK | X_OK) == 0)
	{
		return (true);
	}
	else
		return (false);
}
