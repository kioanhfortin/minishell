/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00.04-lexical_utilis.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfortin <kfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 17:08:53 by kfortin           #+#    #+#             */
/*   Updated: 2023/08/04 18:46:20 by kfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strdup_end_start(char *src, int start, int end)
{
	char	*dup;
	int		i;

	i = 0;
	dup = ft_calloc(sizeof(char), (end - start + 2));
	if (!dup)
		return (NULL);
	while (start <= end)
	{
		dup[i] = src[start];
		start++;
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*ft_strdup_end_start2(char *src, int start, int end)
{
	char	*dup;
	int		i;

	i = 0;
	if (end < start)
		return (NULL);
	dup = ft_calloc(sizeof(char), (end - start + 2));
	if (!dup)
		return (NULL);
	while (start <= end)
	{
		dup[i] = src[start];
		start++;
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

int	ft_search_next(char *str, t_data *data, char c)
{
	data->tok_ch->i++;
	while (str[data->tok_ch->i])
	{
		if (str[data->tok_ch->i] == c)
		{
			return (data->tok_ch->i);
		}
		data->tok_ch->i++;
	}
	return (0);
}

int	ft_is_single_quote(char *str, t_data *data, char c)
{
	int	i;

	i = data->tok_ch->i + 1;
	while (str[i])
	{
		if (str[i] == c)
			return (0);
		i++;
	}
	return (1);
}

int	ft_count_same_metachar(char *str, t_data *data, char c)
{
	int	i;
	int	j;

	i = data->tok_ch->i;
	j = 0;
	while (str[i] == c)
	{
		i++;
		j++;
	}
	return (j);
}
