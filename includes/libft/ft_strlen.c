/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmiyakaw <gmiyakaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 12:17:38 by gmiyakaw          #+#    #+#             */
/*   Updated: 2023/08/02 16:02:31 by gmiyakaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// runs a string until the finalizing \0. Returns the length of s.
// if an empty string is passed, displays an error message and returns -1.
#include "libft.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	if (!s)
	{
		perror("ft_strlen error: invalid/empty argument\n");
		return (-1);
	}
	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}
