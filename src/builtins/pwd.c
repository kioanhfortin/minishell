/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfortin <kfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 14:08:46 by kfortin           #+#    #+#             */
/*   Updated: 2023/08/05 12:40:49 by kfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	our_pwd(t_cmd *cmd)
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
	ft_putstr_fd(cmd->data->pwd, cmd->data->fd[cmd->data->pos_cmd_i][1]);
	ft_putchar_fd('\n', cmd->data->fd[cmd->data->pos_cmd_i][1]);
	if (path)
		path = x_free(path);
	return (1);
}
