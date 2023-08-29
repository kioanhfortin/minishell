/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00.06-ft_split_struct_utilis.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfortin <kfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 17:29:34 by kfortin           #+#    #+#             */
/*   Updated: 2023/08/04 18:28:46 by kfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_split_quote(char *str, t_data *data)
{
	char	c;

	c = '\0';
	c = ft_is_c(str, data, c);
	if (str[data->tok_ch->i] == c)
	{
		if (ft_split_quote_2(str, data, c) == 1)
			return ;
		if (data->tok_ch->i > data->size_raw_line)
			return ;
		ft_fix_position(data, c, str);
		if (data->tok_ch[data->tok_ch->k].pos_out > 0)
		{
			if (data->tok_ch[data->tok_ch->k].pos_in
				+ 1 == data->tok_ch[data->tok_ch->k].pos_out)
				return ;
			data->tok_ch[data->tok_ch->k].arg = ft_strdup_end_start(str,
					data->tok_ch[data->tok_ch->k].pos_in + 1,
					data->tok_ch[data->tok_ch->k].pos_out - 1);
			data->tok_ch->i = data->tok_ch[data->tok_ch->k].pos_out + 1;
			if (data->tok_ch->i > data->size_raw_line)
				return ;
			data->tok_ch->k++;
		}
	}
}

void	ft_fix_position(t_data *data, char c, char *str)
{
	data->tok_ch[data->tok_ch->k].pos_in = data->tok_ch->i;
	data->tok_ch[data->tok_ch->k].pos_out = ft_search_next(str, data, c);
}

int	ft_split_quote_2(char *str, t_data *data, char c)
{
	if (str[data->tok_ch->i + 1] == c)
	{
		data->tok_ch->i += 2;
		return (1);
	}
	else if (ft_is_single_quote(str, data, c) == 1)
	{
		ft_printf("error : single quoted\n");
		exit(0);
	}
	if (data->tok_ch->i > 0 && ft_is_white_space(str[data->tok_ch->i - 1]) == 1)
		data->tok_ch[data->tok_ch->k].w_space_between = 1;
	return (0);
}

char	ft_is_c(char *str, t_data *data, char c)
{
	ft_before_meta_quote(str, data);
	if (str[data->tok_ch->i] == '\"')
	{
		c = '\"';
		data->tok_ch[data->tok_ch->k].is_quoted = DOUBLE_QUOTE;
	}
	if (str[data->tok_ch->i] == '\'')
	{
		c = '\'';
		data->tok_ch[data->tok_ch->k].is_quoted = SINGLE_QUOTE;
	}
	return (c);
}
