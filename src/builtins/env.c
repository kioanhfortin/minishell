/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfortin <kfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 09:42:07 by gmiyakaw          #+#    #+#             */
/*   Updated: 2023/08/05 12:38:49 by kfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	our_env(t_cmd *cmd)
{
	int		i;
	char	*path;

	path = env_set_path(cmd);
	if (!path)
		return (1);
	i = -1;
	while (cmd->data->envp[++i])
	{
		if (find_equal(cmd->data->envp[i]) > 0)
		{
			if (ft_strncmp(cmd->data->envp[i], "PWD=", 4) == 0)
				env_print_pwd(cmd);
			else
			{
				ft_putstr_fd(cmd->data->envp[i], \
					cmd->data->fd[cmd->data->pos_cmd_i][1]);
				ft_putstr_fd("\n", cmd->data->fd[cmd->data->pos_cmd_i][1]);
			}
		}
	}
	if (path)
		path = x_free(path);
	return (0);
}

char	*env_set_path(t_cmd *cmd)
{
	char	*path;

	path = NULL;
	path = getcwd(path, PATH_MAX);
	if (path != NULL)
		cmd->data->pwd = path;
	else
	{
		perror("getcwd pwd");
		g_exit_v = 1;
	}
	return (path);
}

void	env_print_pwd(t_cmd *cmd)
{
	cmd->data->pwd = getcwd(cmd->data->pwd, PATH_MAX);
	ft_putstr_fd("PWD=", \
		cmd->data->fd[cmd->data->pos_cmd_i][1]);
	ft_putstr_fd(cmd->data->pwd, \
		cmd->data->fd[cmd->data->pos_cmd_i][1]);
	ft_putchar_fd('\n', \
		cmd->data->fd[cmd->data->pos_cmd_i][1]); 
	return ;
}
