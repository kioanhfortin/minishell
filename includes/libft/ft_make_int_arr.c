/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_int_arr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmiyakaw <gmiyakaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 15:42:28 by gmiyakaw          #+#    #+#             */
/*   Updated: 2023/06/14 15:50:59 by gmiyakaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// create a int array of size length, sets all elements to 0
// returns a pointer to the arr or NULL if error.
int	*ft_make_int_arr(int length)
{
	int	*arr;
	int	i;

	arr = malloc(sizeof(int) * length);
	if (!arr)
	{
		return (NULL);
	}
	i = 0;
	while (i < length)
	{
		arr[i] = 0;
		i++;
	}
	return (arr);
}
