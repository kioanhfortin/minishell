/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x_calloc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmiyakaw <gmiyakaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 11:46:18 by gmiyakaw          #+#    #+#             */
/*   Updated: 2023/08/02 16:02:49 by gmiyakaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// mallocs and bzeros "size" bytes of memory, displays error
// message and exits in case of failure.

#include "libft.h"

void	*x_calloc(size_t size)
{
	void	*str;

	str = (void *)malloc (size);
	if (str == NULL)
	{
		perror("x_calloc error.\n");
		exit (-1);
	}
	ft_bzero(str, (size));
	return (str);
}
