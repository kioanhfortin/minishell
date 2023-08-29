/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfortin <kfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 14:07:09 by gmiyakaw          #+#    #+#             */
/*   Updated: 2023/08/01 20:54:38 by kfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// returns the number of elements in a NULL terminated string array
// added a -1 for the offset july 27
int	ft_arrlen(char **str)
{
	int	i;

	if (!str)
	{
		return (0);
	}
	i = 0;
	while (str[i])
		i++;
	return (i);
}
