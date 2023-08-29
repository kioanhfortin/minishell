/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01.07-expansions2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfortin <kfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 10:25:56 by gmiyakaw          #+#    #+#             */
/*   Updated: 2023/08/04 19:49:01 by kfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// 2nd check -> is it the last, then its not an exp.
bool	is_expansion(t_token *tok, int i, int tok_i)
{
	if (tok->is_quoted == SINGLE_QUOTE)
		return (false);
	if (tok_i > 0)
	{
		if (ft_strncmp((tok - 1)->arg, "<<", 2) == 0)
			return (false);
	}
	if ((unsigned int)i == ft_strlen(tok->arg) - 1)
		return (false);
	else
		return (true);
}

char	*alias_finder(t_token *tok, int dollar_position)
{
	char	*alias;
	int		end;

	end = dollar_position + 1;
	while (is_valid_alias_char(tok->arg[end]) == true)
		end++;
	alias = ft_substr(tok->arg, dollar_position + 1, (end - 1)
			- dollar_position);
	return (alias);
}

bool	is_valid_alias_char(char c)
{
	if (ft_isalpha(c) == true || ft_isdigit(c) == true || c == '_')
	{
		return (true);
	}
	else
		return (false);
}

void	replace_empty(t_token *token, int dollar_position, t_exp *exp)
{
	char	*pre_alias;
	char	*post_alias;

	pre_alias = ft_strdup_end_start(token->arg, 0, (dollar_position - 1));
	post_alias = ft_strdup_end_start(token->arg, dollar_position
			+ ft_strlen(exp->alias) + 1, ft_strlen(token->arg));
	token->arg = x_free(token->arg);
	token->arg = ft_strjoin(pre_alias, post_alias);
	pre_alias = x_free(pre_alias);
	post_alias = x_free(post_alias);
	return ;
}

char	*target_finder(char *alias, t_data *data)
{
	char	*target;
	char	*tmp;
	int		i;
	int		alias_len;

	alias_len = ft_strlen(alias);
	i = 0;
	while (data->envp[i] && ft_strncmp(data->envp[i], alias, alias_len) != 0)
	{
		i++;
	}
	if (!data->envp[i] || data->envp[i][alias_len] != '=')
	{
		return (NULL);
	}
	tmp = &data->envp[i][alias_len + 1];
	target = ft_strdup(tmp);
	tmp = NULL;
	free(tmp);
	return (target);
}
