/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00.09-ft_initiate_struct_2.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfortin <kfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 18:18:15 by kfortin           #+#    #+#             */
/*   Updated: 2023/08/04 18:18:49 by kfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_is_white_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v'
		|| c == '\f')
		return (1);
	return (0);
}

int	ft_is_meta_char(char c)
{
	if (c == '|' || c == '<' || c == '>' || c == '$')
		return (1);
	return (0);
}

int	ft_is_quote(char c)
{
	if (c == '\"' || c == '\'')
		return (1);
	return (0);
}

int	ft_is_meta_char_2(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}
