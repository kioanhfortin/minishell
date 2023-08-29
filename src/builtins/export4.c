/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmiyakaw <gmiyakaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 12:57:39 by gmiyakaw          #+#    #+#             */
/*   Updated: 2023/08/05 15:27:12 by gmiyakaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**export_handle_expansion(t_cmd *cmd)
{
	int		i;
	int		j;
	char	**new_args;

	new_args = x_calloc(sizeof(char *) * (cmd->cmd_token_count + 1));
	if (new_args == NULL)
		return (NULL);
	i = -1;
	j = 0;
	while (++i < cmd->cmd_token_count)
	{
		if (cmd->cmd_tokens[i].is_exp == 1)
		{
			if (find_equal(cmd->cmd_tokens[i - 1].arg) == \
				(int)ft_strlen(cmd->cmd_tokens[i - 1].arg) - 1)
				export_join_expanded(cmd, new_args, i--, j);
		}
		else
			new_args[j++] = ft_strdup(cmd->cmd_tokens[i].arg);
	}
	new_args[j] = NULL;
	ft_free_array(cmd->args);
	return (new_args);
}

void	export_join_expanded(t_cmd *cmd, char **new_args, int i, int j)
{
	j--;
	new_args[j] = x_free(new_args[j]);
	new_args[j] = ft_strjoin(cmd->cmd_tokens[i - 1].arg, \
		cmd->cmd_tokens[i].arg);
	cmd->cmd_tokens[j].arg = x_free(cmd->cmd_tokens[j].arg);
	cmd->cmd_tokens[j].arg = ft_strdup(new_args[j]);
	j++;
	cmd->cmd_tokens = remove_token(cmd->cmd_tokens, j, \
		&cmd->cmd_token_count);
	return ;
}

char	**export_handle_quotes(t_cmd *cmd)
{
	int		i;
	int		j;
	char	**new_args;

	new_args = x_calloc(sizeof(char *) * (cmd->cmd_token_count + 1));
	i = -1;
	j = 0;
	while (++i < cmd->cmd_token_count)
	{
		if (cmd->cmd_tokens[i].is_quoted == SINGLE_QUOTE || \
			cmd->cmd_tokens[i].is_quoted == DOUBLE_QUOTE)
		{
			if (cmd->cmd_tokens[i + 1].w_space_between == 1)
			{
				if (find_equal(cmd->cmd_tokens[i - 1].arg) == \
				(int)ft_strlen(cmd->cmd_tokens[i - 1].arg) - 1)
					new_args = export_join_quoted_arg(cmd, new_args, i, j);
			}
		}
		else
			new_args[j++] = ft_strdup(cmd->cmd_tokens[i].arg);
	}
	new_args[j] = NULL;
	ft_free_array(cmd->args);
	return (new_args);
}

char	**export_join_quoted_arg(t_cmd *cmd, char **new_args, int i, int j)
{
	new_args[j - 1] = x_free(new_args[j - 1]);
	new_args[j - 1] = ft_strjoin(cmd->cmd_tokens[i -1].arg, \
	cmd->cmd_tokens[i].arg);
	return (new_args);
}
