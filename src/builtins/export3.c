/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmiyakaw <gmiyakaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 12:55:57 by gmiyakaw          #+#    #+#             */
/*   Updated: 2023/08/05 16:08:04 by gmiyakaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_in_env(char *var_name, char **env)
{
	int		i;
	char	*tmp_alias;

	i = 0;
	while (env[i])
	{
		tmp_alias = get_alias(env[i]);
		if (ft_strncmp(tmp_alias, var_name, ft_strlen(env[i])) == 0)
		{
			tmp_alias = x_free(tmp_alias);
			return (true);
		}
		tmp_alias = x_free(tmp_alias);
		i++;
	}
	return (false);
}

int	count_repeats(char **var_names, char **env)
{
	int		count;
	int		i;
	int		j;
	char	*tmp_alias;

	count = 0;
	i = 0;
	while (var_names[i])
	{
		j = 0;
		while (env[j])
		{
			tmp_alias = get_alias(env[j]);
			if (ft_strncmp(tmp_alias, var_names[i], \
				ft_strlen(env[j])) == 0)
			{
				count++;
			}
			j++;
			tmp_alias = x_free(tmp_alias);
		}
		i++;
	}
	return (count);
}

char	**get_values(t_cmd *cmd)
{
	char	**values;
	int		i;
	int		arg_i;

	values = x_calloc (sizeof(char *) * (ft_arrlen(cmd->args) + 1));
	if (!values)
	{
		perror(MLLC_ERR);
		clean_exit(cmd->data);
	}
	arg_i = 0;
	i = 0;
	while (cmd->args[++arg_i])
	{
		if (find_equal(cmd->args[arg_i]) < 0)
			values[i] = NULL;
		else
			values[i] = ft_substr(cmd->args[arg_i], \
				find_equal(cmd->args[arg_i]), ft_strlen(cmd->args[arg_i]));
		i++;
	}
	values[i] = NULL;
	return (values);
}

// if no = is found, returns -1. if str is empty, returns -2
int	find_equal(char *str)
{
	int	i;

	if (!str)
	{
		perror("find equal error: empty string\n");
		return (-2);
	}
	i = 0;
	while (str[i] != '=' && str[i])
		i++;
	if (str[i] == '\0')
	{
		return (-1);
	}
	return (i);
}

char	**get_var_names(t_cmd *cmd)
{
	int		i;
	int		arg_i;
	char	**var_names;

	var_names = x_calloc (sizeof(char *) * (ft_arrlen(cmd->args) + 1));
	if (!var_names)
	{
		perror(MLLC_ERR);
		return (NULL);
	}
	arg_i = 0;
	i = 0;
	while (cmd->args[++arg_i])
	{
		var_names[i] = get_alias(cmd->args[arg_i]);
		if (var_names[i] == NULL)
		{
			perror(EXP_INV_VNM);
			ft_free_array(var_names);
			return (NULL);
		}
		i++;
	}
	var_names[i] = NULL;
	return (var_names);
}
