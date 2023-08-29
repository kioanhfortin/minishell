/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x_free.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfortin <kfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 13:37:08 by gmiyakaw          #+#    #+#             */
/*   Updated: 2023/08/05 09:48:28 by kfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*x_free(void *ptr)
{
	if (ptr && ptr != NULL)
	{
		free(ptr);
	}
	return (NULL);
}

/*
OG
void	x_free(void *ptr)
{
	if (ptr && ptr != NULL)
	{
		free(ptr);
		ptr = NULL;
	}
	else
		printf("invalid xfree:%p\n", ptr);
	return ;
}
*/