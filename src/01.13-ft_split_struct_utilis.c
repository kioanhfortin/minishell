/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01.13-ft_split_struct_utilis.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfortin <kfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 19:39:52 by kfortin           #+#    #+#             */
/*   Updated: 2023/08/04 20:42:08 by kfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_is_charset(char c, char *charset)
{
	int	j;

	j = 0;
	while (charset[j])
	{
		if (c == charset[j])
			return (1);
		j++;
	}
	return (0);
}

int	ft_size_w(char *str, char *charset, int i)
{
	int	j;

	j = 0;
	while (str[i])
	{
		if (ft_is_charset(str[i], charset))
			return (j);
		j++;
		i++;
	}
	return (j);
}

int	ft_count_word(char *str, char *charset)
{
	int	i;
	int	j;
	int	count_word;

	i = 0;
	j = 0;
	count_word = 0;
	while (str[i])
	{
		if (ft_is_charset(str[i], charset))
			j = 0;
		else if (!(ft_is_charset(str[i], charset)) && j == 0)
		{
			j = 1;
			count_word++;
		}
		i++;
	}
	return (count_word);
}
