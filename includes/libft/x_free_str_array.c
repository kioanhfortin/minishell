/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x_free_str_array.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmiyakaw <gmiyakaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 13:52:20 by gmiyakaw          #+#    #+#             */
/*   Updated: 2023/07/20 15:27:55 by gmiyakaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

	// frees every string in a NULL TERMINATED string array, and the pointer
	// itself at the end. Sets all pointers to NULL
#include "libft.h"

void	x_free_str_array(char **array)
{
	size_t	i;

	i = 0;
	while (array[i])
	{
		array[i] = x_free(array[i]);
		i++;
	}
	array = x_free(array);
	return ;
}
