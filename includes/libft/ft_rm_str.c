/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rm_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmiyakaw <gmiyakaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 15:18:22 by gmiyakaw          #+#    #+#             */
/*   Updated: 2023/08/03 12:40:18 by gmiyakaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//removes a string from a NULL terminated string array.
//takes as argument the index of the string to be removed and the OG array
//returns a copy of the string array minus the removed string and frees the
//original array.

char	**ft_rm_str(char **arr, int rm_i)
{
	int		i;
	int		j;
	char	**new_arr;

	new_arr = x_calloc((sizeof(char *)) * (ft_arrlen(arr) + 1));
	if (rm_i == 0 && arr[rm_i + 1] == NULL)
	{
		ft_free_array(new_arr);
		return (NULL);
	}
	i = 0;
	j = 0;
	while (arr[i] != NULL)
	{
		if (i != rm_i)
		{
			new_arr[j] = ft_strdup(arr[i]);
			j++;
		}
		i++;
	}
	new_arr[j] = NULL;
	ft_free_array(arr);
	return (new_arr);
}
