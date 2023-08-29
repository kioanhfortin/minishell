/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmiyakaw <gmiyakaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 10:35:42 by kfortin           #+#    #+#             */
/*   Updated: 2023/08/05 16:56:44 by gmiyakaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	our_cd(t_cmd *cmd)
{
	char	*pwd;
	char	*path;

	path = NULL;
	pwd = NULL;
	cmd->args = join_args(cmd);
	if (ft_arrlen(cmd->args) < 2)
	{
		path = ft_cd_home(cmd, path, pwd);
		return (g_exit_v);
	}
	if (cmd->cmd_token_count < 2)
		path = ft_cd_home(cmd, path, pwd);
	else
		path = ft_cd_directory(cmd, path);
	if (path)
		path = x_free(path);
	return (g_exit_v);
}

char	*ft_cd_home(t_cmd *cmd, char *path, char *pwd)
{
	pwd = ft_cd_home_2(cmd, pwd);
	if (chdir(pwd) != 0)
	{
		g_exit_v = 1;
		perror("chdir home");
	}
	else
	{
		path = getcwd(path, PATH_MAX);
		if (path != NULL)
			cmd->data->pwd = path;
		else
		{
			g_exit_v = 1;
			perror("getcwd home");
		}
	}
	return (path);
}

char	*ft_cd_home_2(t_cmd *cmd, char *pwd)
{
	if (ft_tchek_if_env(cmd) == 0)
	{
		g_exit_v = 1;
		perror("minishell: cd: HOME not set");
	}
	pwd = getenv("HOME");
	if (pwd == NULL)
	{
		g_exit_v = 1;
		perror("getenv");
	}
	return (pwd);
}

int	ft_tchek_if_env(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->data->envp[i])
	{
		if (strncmp(cmd->data->envp[i], "HOME=", 5) == 0)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_cd_directory(t_cmd *cmd, char *path)
{
	if (chdir(cmd->args[1]) != 0)
	{
		g_exit_v = 1;
		perror("chdir red");
	}
	else
	{
		path = getcwd(path, PATH_MAX);
		if (path != NULL)
			cmd->data->pwd = path;
		else
		{
			g_exit_v = 1;
			perror("getcwd red");
		}
	}
	return (path);
}
