/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01.06-expansions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfortin <kfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 10:41:35 by gmiyakaw          #+#    #+#             */
/*   Updated: 2023/08/05 12:43:52 by kfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	find_expansion(t_data *data)
{
	int	i;
	int	arg_i;

	i = -1;
	while (++i < data->token_count)
	{
		arg_i = 0;
		while (data->tok_ch[i].arg[arg_i])
		{
			if (find_expansion_loop(data, &i, &arg_i) != 0)
				return (1);
			if (data->tok_ch[i].arg[arg_i] != '\0')
				arg_i++;
		}
	}
	return (0);
}

int	find_expansion_loop(t_data *data, int *i, int *arg_i)
{
	if (data->tok_ch[*i].arg[*arg_i] == '$')
	{
		if (data->tok_ch[*i].arg[*arg_i + 1] == '?')
		{
			if (data->tok_ch[*i].arg)
				data->tok_ch[*i].arg = x_free(data->tok_ch[*i].arg);
			data->tok_ch[*i].arg = ft_itoa(g_exit_v);
		}
		else if (is_expansion(&data->tok_ch[*i], *arg_i, *i) == true)
		{
			if (expand(&data->tok_ch[*i], *arg_i, data) != 0)
				return (1);
			data->tok_ch[*i].is_exp = 1;
			*arg_i = 0;
		}
	}
	return (0);
}

	// OG as of july 31
	// if (expansion->target == NULL || expansion->alias == NULL)
	// {
	// 	replace_empty(token, dollar_position, expansion);
	// 	expand_free_array(expansion);
	// 	return (0);
	// }
int	expand(t_token *token, int dollar_position, t_data *data)
{
	t_exp	*expansion;

	expansion = x_calloc(sizeof(t_exp));
	if (!expansion)
	{
		perror(MLLC_ERR);
		expand_free_array(expansion);
		return (-1);
	}
	expansion->alias = alias_finder(token, dollar_position);
	if (is_in_env(expansion->alias, data->envp) == false)
	{
		replace_empty(token, dollar_position, expansion);
		expand_free_array(expansion);
		return (0);
	}
	expansion->target = target_finder(expansion->alias, data);
	if (expansion->target == NULL)
	{
		expand_free_array(expansion);
		return (0);
	}
	switcheroo(token, dollar_position, expansion);
	expand_free_array(expansion);
	return (0);
}

void	expand_free_array(t_exp *expansion)
{
	if (expansion->alias)
		expansion->alias = x_free(expansion->alias);
	if (expansion->target)
		expansion->target = x_free(expansion->target);
	if (expansion)
		expansion = x_free(expansion);
	return ;
}

void	switcheroo(t_token *token, int dollar_position, t_exp *expansion)
{
	char	*tmp;
	char	*res;

	tmp = ft_strdup_end_start(token->arg, 0, (dollar_position - 1));
	res = ft_strjoin(tmp, expansion->target);
	tmp = x_free(tmp);
	dollar_position += ft_strlen(expansion->alias);
	tmp = ft_strdup(res);
	res = x_free(res);
	res = ft_strjoin(tmp, &token->arg[dollar_position + 1]);
	tmp = x_free(tmp);
	token->arg = x_free(token->arg);
	token->arg = ft_strdup(res);
	res = x_free(res);
	return ;
}
