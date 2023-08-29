/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfortin <kfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 16:28:53 by gmiyakaw          #+#    #+#             */
/*   Updated: 2023/08/05 12:40:20 by kfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	export_free_arrays(char **var_names, char **values, char **envp)
{
	if (var_names != NULL)
		ft_free_array(var_names);
	if (values != NULL)
		ft_free_array(values);
	if (envp != NULL)
		ft_free_array(envp);
	return ;
}

// checks if variables names are valid, prints an error message
// if invalid.
bool	export_check_valid_arg(t_cmd *cmd)
{
	char	*var_name;
	int		i;
	int		j;

	i = 0;
	while (cmd->args[++i])
	{
		var_name = get_alias(cmd->args[i]);
		if (var_name == NULL)
			return (export_print_error());
		j = -1;
		while (var_name[++j])
		{
			if (export_valid_char(var_name[j]) == false || \
				ft_isdigit(cmd->args[i][0]) == true)
			{
				printf("export: error. invalid identifier\n");
				g_exit_v = 1;
				var_name = x_free(var_name);
				return (false);
			}
		}
		var_name = x_free(var_name);
	}
	return (true);
}

bool	export_print_error(void)
{
	printf("export: error. invalid identifier\n");
	return (false);
}

bool	export_valid_char(char c)
{
	if (ft_isalnum(c) == false && c != '_')
	{
		return (false);
	}
	return (true);
}

// char *get_alias(char *env_str)
// {
// 	int	i;
// 	char *alias;
// 							// check for invalid characters
// 	i = 0;
// 	while (env_str[i] != '=' && env_str[i] != '\0')
// 		i++;
// 	if (env_str[i] == '\0')
// 		return (NULL);
// 	alias = ft_substr(env_str, 0, i);
// 	return (alias);
// }

// new version, trying to keep the last =, in case of VAR=====VALUE
// also should accept varnames without "="
char	*get_alias(char *env_str)
{
	int		i;
	char	*alias;

	i = 0;
	while (env_str[i] != '=' && env_str[i] != '\0')
		i++;
	if (env_str[i] == '\0')
		return (ft_substr(env_str, 0, i));
	while (env_str[i + 1] == '=' && env_str[i + 1] != '\0')
		i++;
	alias = ft_substr(env_str, 0, i);
	return (alias);
}
