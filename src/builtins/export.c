/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmiyakaw <gmiyakaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 11:15:57 by gmiyakaw          #+#    #+#             */
/*   Updated: 2023/08/05 16:27:53 by gmiyakaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	our_export(t_cmd *cmd)
{
	char	**var_names;
	char	**values;
	char	**new_env;

	if (ft_arrlen(cmd->args) == 1 || ft_strcmp(cmd->args[1], "") == 0)
	{
		return (export_no_arg(cmd->data));
	}
	cmd->args = export_handle_expansion(cmd);
	cmd->args = export_handle_quotes(cmd);
	cmd_rmv_empty(cmd);
	if (export_check_valid_arg(cmd) == false \
		|| cmd->args == NULL)
		return (1);
	var_names = get_var_names(cmd);
	if (var_names == NULL)
		return (1);
	values = get_values(cmd);
	new_env = make_new_env(var_names, values, cmd->data->envp);
	if (!new_env)
		return (-3);
	export_free_arrays(var_names, values, cmd->data->envp);
	cmd->data->envp = new_env;
	return (0);
}

/*
	create e a new argument array.
	go through the tokens, check if the next token is quoted, 
	if so: check if this arg ends in an =. if so join them.
	else, copy the whole token.
*/

char	**make_new_env(char **var_names, char **values, char **env)
{
	char	**new_env;
	int		i;
	int		j;

	new_env = export_copy_env(env, var_names);
	if (!new_env)
		return (NULL);
	i = ft_arrlen(new_env);
	j = 0;
	while (var_names[j])
	{
		if (is_in_env(var_names[j], new_env) == true)
		{
			replace_in_env(var_names, values, j, new_env);
			i--;
		}
		else if (values[j] == NULL)
			new_env[i] = ft_strdup(var_names[j]);
		else
			new_env[i] = ft_strjoin(var_names[j], values[j]);
		j++;
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

// mallocs new_env with the right amount of memory, taking in any repeats
// copies all of the elements of the old env, but does not NULL terminate
char	**export_copy_env(char **old_env, char **var_names)
{
	char	**new_env;
	int		i;
	int		repeat_count;
	int		old_env_len;
	int		new_len;

	repeat_count = count_repeats(var_names, old_env);
	old_env_len = ft_arrlen(old_env);
	new_len = old_env_len - repeat_count + ft_arrlen(var_names);
	if (old_env_len == -1 || ft_arrlen(var_names) == -1)
		return (NULL);
	new_env = x_calloc(sizeof(char *) * (new_len + 1));
	if (!new_env)
		return (NULL);
	i = 0;
	while (old_env[i])
	{
		new_env[i] = ft_strdup(old_env[i]);
		i++;
	}
	while (i <= new_len)
		new_env[i++] = NULL;
	return (new_env);
}

void	replace_in_env(char **var_names, char **values, int var_i, char **env)
{
	int		i;
	char	*tmp;

	i = 0;
	while (env[i])
	{
		tmp = get_alias(env[i]);
		if (ft_strncmp(tmp, var_names[var_i], ft_strlen(env[i])) == 0)
		{
			env[i] = x_free(env[i]);
			env[i] = ft_strjoin(var_names[var_i], values[var_i]);
			tmp = x_free(tmp);
			break ;
		}
		tmp = x_free(tmp);
		i++;
	}
	return ;
}
