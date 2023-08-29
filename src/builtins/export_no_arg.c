/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_no_arg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfortin <kfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 13:14:15 by gmiyakaw          #+#    #+#             */
/*   Updated: 2023/08/05 10:27:40 by kfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	export_no_arg(t_data *data)
{
	char	**alias_list;
	int		i;

	alias_list = make_alias_list(data->envp);
	if (!alias_list)
		return (-1);
	put_in_order(alias_list);
	if (print_ordered_list(alias_list, data->envp, data) < 0)
		return (-1);
	i = 0;
	while (alias_list[i])
	{
		if (alias_list[i] != NULL)
			alias_list[i] = x_free(alias_list[i]);
		i++;
	}
	alias_list = x_free(alias_list);
	return (0);
}

char	**make_alias_list(char **envp)
{
	int		i;
	char	**alias_list;
	int		env_len;

	env_len = ft_arrlen(envp);
	alias_list = x_calloc((sizeof(char *) * (env_len + 1)));
	if (!alias_list)
	{
		perror(MLLC_ERR);
		return (NULL);
	}
	i = -1;
	while (++i < env_len)
	{
		alias_list[i] = get_alias(envp[i]);
	}
	alias_list[i] = NULL;
	return (alias_list);
}

int	print_ordered_list(char **alias_list, char **env, t_data *data)
{
	int	i;
	int	*repeat;

	repeat = ft_make_int_arr(ft_arrlen(alias_list));
	if (repeat == NULL)
	{
		perror(MLLC_ERR);
		return (-1);
	}
	i = 0;
	while (alias_list[i])
	{
		print_ordered_list_2(repeat, env, alias_list[i], data);
		i++;
	}
	repeat = x_free(repeat);
	return (0);
}

void	print_ordered_list_2(int *repeat, char **env, char *alias_list,
		t_data *data)
{
	int		j;
	char	*tmp;
	char	*path;

	j = 0;
	path = NULL;
	path = ft_get_path_2(data, path);
	while (env[j])
	{
		tmp = ft_strnstr(env[j], alias_list, ft_strlen(alias_list));
		if (tmp != NULL && repeat[j] == 0)
		{
			if (ft_strncmp(env[j], "PWD=", 4) == 0)
				ft_print_pwd(data);
			else
				ft_print_normal(data, tmp);
			repeat[j] = 1;
			break ;
		}
		j++;
	}
	if (path)
		path = x_free(path);
	return ;
}

void	put_in_order(char **alias_list)
{
	int		i;
	int		arrlen;
	char	*tmp;

	tmp = NULL;
	arrlen = ft_arrlen(alias_list);
	i = -1;
	while (++i < arrlen - 1)
	{
		if (ft_strcmp(alias_list[i], alias_list[i + 1]) > 0)
		{
			tmp = alias_list[i];
			alias_list[i] = alias_list[i + 1];
			alias_list[i + 1] = tmp;
			tmp = NULL;
			i = -1;
		}
	}
	return ;
}
