/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03.01-error_exit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmiyakaw <gmiyakaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:50:22 by gmiyakaw          #+#    #+#             */
/*   Updated: 2023/08/05 15:02:58 by gmiyakaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	syntax_error(t_data *data)
{
	(void)data;
	g_exit_v = 2;
	ft_putstr_fd("minishell: syntax error near unexpected token\n", 2);
	return (0);
}

void	clean_exit(t_data *data)
{
	if (data->raw_line)
		free(data->raw_line);
	if (data->tok_ch)
		free(data->tok_ch);
	exit(0);
}

void	free_token_chain(t_token *tok_ch, int token_count)
{
	int	i;

	i = -1;
	while (++i < token_count)
	{
		if (tok_ch[i].arg)
			tok_ch[i].arg = x_free(tok_ch[i].arg);
	}
	tok_ch = x_free(tok_ch);
}

void	*free_data_struct(t_data *data)
{
	delete_file(TMP_HD);
	if (data->tok_ch)
		free_token_chain(data->tok_ch, data->token_count);
	free_cmd_list(data);
	if (data->raw_line)
		data->raw_line = x_free(data->raw_line);
	if (data->envp)
		ft_free_array(data->envp);
	if (data->paths)
		ft_free_array(data->paths);
	if (data->pid)
		data->pid = x_free(data->pid);
	if (data->fd)
		ft_free_all_fd(data);
	if (data->buffer)
		data->buffer = x_free(data->buffer);
	x_free(data);
	return (NULL);
}

void	free_cmd_list(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->cmd_count)
	{
		if (&data->cmd_list[i])
			free_cmd_ch(&data->cmd_list[i]);
		i++;
	}
	if (data->cmd_list)
		data->cmd_list = x_free(data->cmd_list);
}
