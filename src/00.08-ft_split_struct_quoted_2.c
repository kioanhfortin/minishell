/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00.08-ft_split_struct_quoted_2.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfortin <kfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 17:05:12 by kfortin           #+#    #+#             */
/*   Updated: 2023/08/04 18:13:31 by kfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_before_meta_quote(char *str, t_data *data)
{
	char	*str2;

	str2 = NULL;
	if (data->tok_ch->i > data->size_raw_line || data->tok_ch->i == 0)
		return ;
	ft_quote_part_2(data, str);
	if (ft_tchek_only_space(str, data) == 0)
		return ;
	if (data->tok_ch[data->tok_ch->k].pos_in == 0)
		str2 = ft_strdup_end_start(str, data->tok_ch[data->tok_ch->k].pos_in,
				data->tok_ch[data->tok_ch->k].pos_out - 1);
	else
		str2 = ft_strdup_end_start2(str, data->tok_ch[data->tok_ch->k].pos_in
				+ 1, data->tok_ch[data->tok_ch->k].pos_out - 1);
	if (data->tok_ch[data->tok_ch->k].pos_in
		== data->tok_ch[data->tok_ch->k].pos_out)
		return ;
	if (str2)
	{
		data = ft_split_struct(str2, " \n\t\v\f\r", data);
		data->tok_ch->k += data->token_count_temp;
		data->token_count_temp = 0;
	}
	if (str2)
		x_free(str2);
}

void	ft_quote_part_2(t_data *data, char *str)
{
	data->tok_ch[data->tok_ch->k].pos_out = data->tok_ch->i;
	if (data->tok_ch->k > 0 && data->tok_ch[data->tok_ch->k - 1].flag_do == 1)
		data->tok_ch[data->tok_ch->k].pos_in = data->tok_ch[data->tok_ch->k
			- 1].pos_out;
	else if (data->tok_ch->k == 1 && data->tok_ch[data->tok_ch->k
			- 1].is_quoted == 3)
		data->tok_ch[data->tok_ch->k].pos_in = data->tok_ch[data->tok_ch->k
			- 1].pos_out + 1;
	else if (data->tok_ch->k > 0 && data->tok_ch[data->tok_ch->k
			- 1].flag_do == 0)
		data->tok_ch[data->tok_ch->k].pos_in = ft_tchek_what_before(str, data);
	if (ft_is_white_space(str[data->tok_ch->i]) == 1)
		data->tok_ch[data->tok_ch->k].w_space_between = 1;
}

void	ft_split_metachar(char *str, t_data *data)
{
	char	c;
	int		i;

	c = str[data->tok_ch->i];
	i = 0;
	data->nb_meta = 0;
	ft_before_meta_quote(str, data);
	while (ft_is_charset(str[data->tok_ch->i], "|<>") == 1)
	{
		if (c == str[data->tok_ch->i] && c == str[data->tok_ch->i + 1]
			&& c != '|')
		{
			c = ft_metachar_2(data, i, c, str);
		}
		else
		{
			ft_stock_meta(data, str);
			if ((data->tok_ch->i + 1) > data->size_raw_line)
				break ;
			c = str[data->tok_ch->i + 1];
		}
	}
}

char	ft_metachar_2(t_data *data, int i, char c, char *str)
{
	data->nb_meta = ft_count_same_metachar(str, data, c);
	data->tok_ch[data->tok_ch->k].arg = ft_calloc(sizeof(char), data->nb_meta
			+ 1);
	while (i < data->nb_meta)
	{
		data->tok_ch[data->tok_ch->k].arg[i] = c;
		i++;
	}
	data->tok_ch[data->tok_ch->k].arg[i] = '\0';
	if (data->nb_meta == 2)
		data->tok_ch[data->tok_ch->k].is_quoted = DOUBLE_META;
	else
		data->tok_ch[data->tok_ch->k].is_quoted = ERROR;
	data->tok_ch->i += data->nb_meta;
	c = str[data->tok_ch->i];
	data->nb_meta = 0;
	i = 0;
	data->tok_ch->k++;
	return (c);
}

void	ft_stock_meta(t_data *data, char *str)
{
	data->tok_ch[data->tok_ch->k].is_quoted = SINGLE_META;
	data->tok_ch[data->tok_ch->k].arg = ft_calloc(sizeof(char), 2);
	data->tok_ch[data->tok_ch->k].arg[0] = str[data->tok_ch->i];
	data->tok_ch[data->tok_ch->k].arg[1] = '\0';
	data->tok_ch->i += 1;
	data->tok_ch->k++;
}
