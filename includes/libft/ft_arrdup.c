/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmiyakaw <gmiyakaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 16:11:21 by gmiyakaw          #+#    #+#             */
/*   Updated: 2023/07/31 17:31:03 by gmiyakaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// possible invalid write, use with caution
// allocates and copies the content of a NULL TERMINATED array.
char	**ft_arrdup(char **arr)
{
	char	**new_arr;
	int		i;

	if (!arr)
		return (NULL);
	new_arr = x_calloc(sizeof(char *) * (ft_arrlen(arr) + 1));
	i = 0;
	while (arr[i])
	{
		new_arr[i] = ft_strdup(arr[i]);
		i++;
	}
	new_arr[i] = NULL;
	return (new_arr);
}
