/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01.09 - heredoc2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmiyakaw <gmiyakaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 18:39:38 by gmiyakaw          #+#    #+#             */
/*   Updated: 2023/07/31 18:41:25 by gmiyakaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// go through buffer, trying to finid a $.
// if one is found, try to expand it. Rules for valid expansion
// are looser since heredocs dont seem to care about single quote
char	*heredoc_find_expansion(t_cmd *cmd, char *buffer, int metachar_pos)
{
	int	i;
	int	buffer_len;

	if (ft_strcmp(buffer, cmd->cmd_tokens[metachar_pos + 1].arg) == 0)
		return (buffer);
	i = -1;
	buffer_len = ft_strlen(buffer);
	while (++i < buffer_len)
	{
		if (buffer[i] == '$')
		{
			buffer = heredoc_expand(buffer, i, cmd->data);
			if (buffer == NULL)
				return (NULL);
			i = 0;
			buffer_len = ft_strlen(buffer);
		}
	}
	return (buffer);
}

char	*heredoc_expand(char *buffer, int dollar_pos, t_data *data)
{
	t_exp	*exp;

	exp = x_calloc(sizeof (t_exp));
	if (!exp)
	{
		perror(MLLC_ERR);
		return (NULL);
	}
	exp->alias = heredoc_alias_finder(buffer, dollar_pos);
	exp->target = target_finder(exp->alias, data);
	buffer = heredoc_switcheroo(buffer, dollar_pos, exp);
	exp->alias = x_free(exp->alias);
	exp->target = x_free(exp->target);
	exp = x_free(exp);
	return (buffer);
}
