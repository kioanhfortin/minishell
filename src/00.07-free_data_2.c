/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00.07-free_data_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfortin <kfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 16:50:57 by kfortin           #+#    #+#             */
/*   Updated: 2023/08/04 18:23:24 by kfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_clean_array_struct(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->token_count)
	{
		if (data->tok_ch[i].arg)
			data->tok_ch[i].arg = x_free(data->tok_ch[i].arg);
		i++;
	}
	if (data->tok_ch->arg)
		data->tok_ch->arg = x_free(data->tok_ch->arg);
	if (data->fd)
		ft_free_all_fd(data);
	i = -1;
	if (data->cmd_list)
	{
		while (++i < data->cmd_count)
			if (&data->cmd_list[i])
				free_cmd_ch(&data->cmd_list[i]);
		data->cmd_list = x_free(data->cmd_list);
	}
	if (data->raw_line)
		data->raw_line = x_free(data->raw_line);
	ft_init_data(data);
	ft_init_token(data->tok_ch);
}

void	free_cmd_ch(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (cmd->cmd_tokens)
	{
		if (cmd->cmd_tokens[i].arg)
		{
			while (i < cmd->cmd_token_count)
			{
				cmd->cmd_tokens[i].arg = x_free(cmd->cmd_tokens[i].arg);
				i++;
			}
			cmd->cmd_tokens = x_free(cmd->cmd_tokens);
		}
	}
	if (cmd->args)
		ft_free_array(cmd->args);
	if (cmd->cmd_path)
		cmd->cmd_path = x_free(cmd->cmd_path);
}

int	ft_tchek_what_before(char *str, t_data *data)
{
	int	i;

	i = data->tok_ch->i - 1;
	while (i > 0)
	{
		if (ft_is_meta_char(str[i]) == 1 || ft_is_quote(str[i]) == 1)
			return (i);
		i--;
	}
	return (0);
}
