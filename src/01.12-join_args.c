/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01.12-join_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfortin <kfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 17:28:54 by gmiyakaw          #+#    #+#             */
/*   Updated: 2023/08/05 14:46:19 by kfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**join_args(t_cmd *cmd)
{
	int		new_len;
	char	**new_args;

	new_len = count_splits(cmd);
	if (ft_arrlen(cmd->args) == new_len)
		return (cmd->args);
	new_args = x_calloc(sizeof(char *) * (new_len + 2));
	cmd->i = 0;
	cmd->j = 0;
	while (cmd->i < cmd->cmd_token_count)
	{
		if (should_join(&cmd->cmd_tokens[cmd->i]) == true)
		{
			new_args[cmd->j - 1] = x_free(new_args[cmd->j - 1]);
			new_args[cmd->j - 1] = ft_strjoin(cmd->args[cmd->j - 1],
					cmd->args[cmd->j]);
		}
		else
			new_args[cmd->j] = ft_strdup(cmd->args[cmd->j]);
		cmd->j++;
		cmd->i++;
	}
	new_args[cmd->j] = NULL;
	ft_free_array(cmd->args);
	return (new_args);
}

bool	should_join(t_token *token)
{
	if (token->is_exp == 1 || token->is_quoted == 1)
	{
		if (token->w_space_between == 0)
			return (true);
	}
	return (false);
}

int	count_splits(t_cmd *cmd)
{
	int	i;
	int	count;
	int	new_len;

	count = 0;
	i = 0;
	while (i < cmd->cmd_token_count)
	{
		if (should_join(&cmd->cmd_tokens[i]) == true)
			count++;
		i++;
	}
	new_len = ft_arrlen(cmd->args) - count;
	return (new_len);
}
