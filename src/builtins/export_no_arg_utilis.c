/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_no_arg_utilis.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfortin <kfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 13:10:08 by kfortin           #+#    #+#             */
/*   Updated: 2023/08/05 12:39:52 by kfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_get_path_2(t_data *data, char *path)
{
	path = getcwd(path, PATH_MAX);
	if (path != NULL)
		data->pwd = path;
	else
	{
		perror("getcwd pwd");
		g_exit_v = 1;
	}
	return (path);
}

void	ft_print_pwd(t_data *data)
{
	ft_putstr_fd("declare -x PWD=", data->fd[data->pos_cmd_i][1]);
	ft_putstr_fd(data->pwd, data->fd[data->pos_cmd_i][1]);
	ft_putchar_fd('\n', data->fd[data->pos_cmd_i][1]);
}

void	ft_print_normal(t_data *data, char *tmp)
{
	ft_putstr_fd(PRE_EXP, data->fd[data->pos_cmd_i][1]);
	ft_putstr_fd(tmp, data->fd[data->pos_cmd_i][1]);
	ft_putchar_fd('\n', data->fd[data->pos_cmd_i][1]);
}
