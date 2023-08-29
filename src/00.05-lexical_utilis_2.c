/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00.05-lexical_utilis_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfortin <kfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 17:14:58 by kfortin           #+#    #+#             */
/*   Updated: 2023/08/05 12:42:28 by kfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_tchek_only_space(char *str, t_data *data)
{
	int	i;
	int	flag;

	i = data->tok_ch->i - 1;
	flag = 0;
	while (i >= 0)
	{
		if (ft_is_white_space(str[i]) == 0)
			flag = 1;
		if (ft_is_meta_char(str[i]) == 1 || ft_is_quote(str[i]) == 1)
			break ;
		i--;
	}
	if (flag == 1)
		return (1);
	return (0);
}

int	ft_tchek_if_dollar(char *str, t_data *data)
{
	int	in;
	int	out;

	out = data->tok_ch[data->tok_ch->k].pos_out;
	in = data->tok_ch[data->tok_ch->k].pos_in;
	while (in < out)
	{
		if (str[in] == '$')
			return (1);
		in++;
	}
	return (0);
}

int	ft_tchek_if_dollar2(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

int	ft_check_multiple_c(char *str, char c)
{
	int	i;
	int	c_count;

	i = 0;
	c_count = 0;
	while (str[i])
	{
		if (c == str[i])
			c_count++;
		i++;
	}
	return (c_count);
}

int	ft_tchek_if_only_meta(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_is_quote(str[i]) != 1 && ft_is_meta_char(str[i]) != 1
			&& ft_is_white_space(str[i]) != 1)
		{
			return (1);
		}
		i++;
	}
	ft_putstr_fd("minishell: command not found\n", 2);
	g_exit_v = 127;
	return (0);
}
