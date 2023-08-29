/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01.02-parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmiyakaw <gmiyakaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:28:49 by gmiyakaw          #+#    #+#             */
/*   Updated: 2023/08/05 16:35:57 by gmiyakaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	parser(t_data *data)
{
	classifier(data);
	if (syntax_check(data) != 0)
		return (1);
	if (find_expansion(data) != 0)
		return (2);
	if (init_cmds(data) != 0)
		return (3);
	if (make_cmd_tokens(data, data->tok_ch) != 0)
		return (4);
	if (parse_cmds(data->cmd_list, data->cmd_count, \
		data->paths) != 0)
		return (5);
	return (0);
}

void	classifier(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->token_count)
	{
		if (ft_strcmp(data->tok_ch[i].arg, "|") == \
			0 && data->tok_ch[i].is_quoted != SINGLE_QUOTE)
			data->tok_ch[i].type = PIPE;
		else if (ft_strcmp(data->tok_ch[i].arg, "<") == \
			0 && data->tok_ch[i].is_quoted != SINGLE_QUOTE)
			data->tok_ch[i].type = REDIR_IN;
		else if (ft_strcmp(data->tok_ch[i].arg, ">") == \
			0 && data->tok_ch[i].is_quoted != SINGLE_QUOTE)
			data->tok_ch[i].type = REDIR_OUT;
		else if (ft_strcmp(data->tok_ch[i].arg, ">>") == \
			0 && data->tok_ch[i].is_quoted != SINGLE_QUOTE)
			data->tok_ch[i].type = APPEND;
		else if (ft_strcmp(data->tok_ch[i].arg, "<<") == \
			0 && data->tok_ch[i].is_quoted != SINGLE_QUOTE)
			data->tok_ch[i].type = HEREDOC;
		else
			data->tok_ch[i].type = WORD;
	}
	return ;
}

int	syntax_check(t_data *data)
{
	int		i;
	bool	invalid;

	invalid = false;
	i = -1;
	while (++i < data->token_count && invalid == false)
	{
		if (data->tok_ch[i].type == PIPE)
		{
			check_pipe(data, i, &invalid);
			data->cmd_count++;
		}
		else if (data->tok_ch[i].type == REDIR_IN)
			check_redir_in(data, i, &invalid);
		else if (data->tok_ch[i].type == REDIR_OUT)
			check_redir_out(data, i, &invalid);
		else if (data->tok_ch[i].type == HEREDOC)
			check_heredoc(data, i, &invalid);
		else if (data->tok_ch[i].type == APPEND)
			check_append(data, i, &invalid);
	}
	if (invalid == true)
		return (-1);
	else
		return (0);
}
