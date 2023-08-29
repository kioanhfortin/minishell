/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01.01-ft_split_struct.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfortin <kfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 14:39:26 by kfortin           #+#    #+#             */
/*   Updated: 2023/08/05 14:45:33 by kfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_data	*ft_split_struct(char *str, char *charset, t_data *data)
{
	data->i = 0;
	data->j = 0;
	data->k_temp = data->tok_ch->k;
	if (!str || !data->tok_ch)
		return (NULL);
	while (str[data->i])
	{
		if (ft_is_charset(str[data->i], charset)
			&& !(ft_is_charset(str[data->i + 1], charset)) && data->j > 0)
			data->j = ft_is_charset_2(data, data->j, data->i);
		if (!(ft_is_charset(str[data->i], charset)))
		{
			if (data->j == 0)
			{
				data->tok_ch[data->k_temp].arg = ft_calloc(sizeof(char),
						ft_size_w(str, charset, data->i) + 1);
				ft_flag_space(data, data->i);
			}
			data->tok_ch[data->k_temp].arg[data->j] = str[data->i];
			data->j++;
		}
		data->i++;
	}
	data->token_count_temp = ft_count_word(str, charset);
	return (data);
}

int	ft_is_charset_2(t_data *data, int j, int i)
{
	data->tok_ch[data->k_temp].is_quoted = NO_QUOTE;
	if (i == 0)
		data->tok_ch[data->k_temp].w_space_between = 1;
	data->k_temp++;
	j = 0;
	return (j);
}

void	ft_flag_space(t_data *data, int i)
{
	if (i != 0 && ft_is_white_space(data->raw_line[i - 1]) == 1)
		data->tok_ch[data->k_temp].w_space_between = 1;
	if (i == 0 && ft_is_white_space(data->raw_line[data->tok_ch->i]) == 1)
		data->tok_ch[data->k_temp].w_space_between = 1;
}

int	ft_not_charset(t_data *data, int j, int i, char *charset)
{
	if (j == 0)
	{
		data->tok_ch[data->k_temp].arg = ft_calloc(sizeof(char),
				ft_size_w(data->raw_line, charset, i) + 1);
		if (i != 0 && ft_is_white_space(data->raw_line[i - 1]) == 1)
			data->tok_ch[data->k_temp].w_space_between = 1;
		if (i == 0 && ft_is_white_space(data->raw_line[data->tok_ch->i]) == 1)
			data->tok_ch[data->k_temp].w_space_between = 1;
	}
	data->tok_ch[data->k_temp].arg[j] = data->raw_line[i];
	j++;
	return (j);
}
