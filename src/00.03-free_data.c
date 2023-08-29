/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00.03-free_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfortin <kfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 15:49:43 by kfortin           #+#    #+#             */
/*   Updated: 2023/08/04 16:49:48 by kfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_free_lexical(t_data *data)
{
	if (data->raw_line)
	{
		free(data->raw_line);
		data->raw_line = NULL;
	}
	ft_clean_token(data);
}

void	ft_clean_token(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->token_count)
	{
		if (data->tok_ch[i].arg)
		{
			free(data->tok_ch[i].arg);
			data->tok_ch[i].arg = NULL;
		}
		i++;
	}
	if (data->tok_ch)
	{
		free(data->tok_ch);
		data->tok_ch = NULL;
	}
}

void	ft_free_pid(t_data *data)
{
	if (data->pid)
	{
		free(data->pid);
		data->pid = 0;
	}
}

void	ft_print_path(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->cmd_count)
	{
		ft_printf("arg path 1:\n%s\n", data->cmd_list[i].cmd_path);
		i++;
	}
}

void	ft_print_array_struct(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->token_count)
	{
		ft_printf("[%s] quote code : %d\n", data->tok_ch[i].arg,
			data->tok_ch[i].is_quoted);
		i++;
	}
}
