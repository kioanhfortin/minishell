/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00.01-ft_split_struct_quoted.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfortin <kfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 18:13:28 by kfortin           #+#    #+#             */
/*   Updated: 2023/08/05 18:15:53 by kfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_tchek_if_end(char *str, t_data *data)
{
	int	i;
	int	flag;

	i = data->tok_ch->i;
	flag = 1;
	while (str[i])
	{
		if (str[i] == '$' || ft_is_meta_char(str[i]) == 1
			|| ft_is_quote(str[i]) == 1)
			flag = 0;
		i++;
	}
	if (flag == 1)
		return (1);
	return (0);
}

t_data	*ft_split_struct_on_quote(char *str, t_data *data)
{
	int	j;

	j = 0;
	if (!(data->tok_ch))
		return (NULL);
	while (str[data->tok_ch->i])
	{
		j = ft_split_struct_on_quote_2(data, str);
		if (j == 1)
			break ;
		if (data->tok_ch->i == data->size_raw_line)
		{
			ft_before_meta_quote(str, data);
			break ;
		}
	}
	data->token_count = data->tok_ch->k;
	return (data);
}

int	ft_split_struct_on_quote_2(t_data *data, char *str)
{
	if (ft_is_charset(str[data->tok_ch->i], "|<>") == 1)
		ft_go_to_meta(data, str);
	else if (ft_is_charset(str[data->tok_ch->i], "\'\"") == 1)
	{
		ft_split_quote(str, data);
		data->tok_ch[data->tok_ch->k].flag_do = 0;
	}
	else if (ft_is_charset(str[data->tok_ch->i], "$") == 1)
	{
		if (ft_is_charset(str[data->tok_ch->i + 1], "\'\"|<>$") == 1)
			data->tok_ch->i++;
		else
			ft_is_dollar(str, data);
	}
	else if (ft_is_white_space(str[data->tok_ch->i]))
		data->tok_ch->i++;
	else
	{
		if (data->tok_ch->i + 1 > data->size_raw_line)
			return (1);
		data->tok_ch->i++;
	}
	return (0);
}

void	ft_go_to_meta(t_data *data, char *str)
{
	ft_split_metachar(str, data);
	data->tok_ch[data->tok_ch->k].flag_do = 0;
}

void	ft_is_dollar(char *str, t_data *data)
{
	ft_before_meta_quote(str, data);
	if (data->tok_ch->i > 0 && ft_is_white_space(str[data->tok_ch->i - 1]) == 1)
		data->tok_ch[data->tok_ch->k].w_space_between = 1;
	if (data->tok_ch->k != 0 && (ft_is_white_space(str[data->tok_ch->i]) == 1))
		data->tok_ch[data->tok_ch->k].pos_in = data->tok_ch[data->tok_ch->k
			- 1].pos_out;
	else
		data->tok_ch[data->tok_ch->k].pos_in = data->tok_ch->i;
	data->tok_ch->i++;
	while (str[data->tok_ch->i] && ft_is_charset(str[data->tok_ch->i + 1],
			"|<>\'\"\t\n\r\v\f $") == 0)
		data->tok_ch->i++;
	data->tok_ch[data->tok_ch->k].pos_out = data->tok_ch->i;
	data->tok_ch[data->tok_ch->k].arg
		= ft_strdup_end_start(str, data->tok_ch[data->tok_ch->k].pos_in,
			data->tok_ch[data->tok_ch->k].pos_out);
	data->tok_ch[data->tok_ch->k].flag_do = 1;
	data->tok_ch->k++;
}
