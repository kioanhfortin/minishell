/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str_array.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmiyakaw <gmiyakaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 10:23:10 by gmiyakaw          #+#    #+#             */
/*   Updated: 2023/07/31 17:33:56 by gmiyakaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// prints a NULL TERMINATED array of strings. Prints an error in case of
//  empty array;
void	print_str_array(char **arr)
{
	int	i;

	printf("____________printing array start______________\n");
	if (!arr)
	{
		perror("ft_print_str_array error: empty array\n");
		return ;
	}
	i = -1;
	while (arr[++i] != NULL)
	{
		printf("arr[%d]:|%s|\n", i, arr[i]);
	}
	printf("null terminated check: arr[%d]: |%s|\n", i, arr[i]);
	printf("__________print array end_______________\n");
	return ;
}
