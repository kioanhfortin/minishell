/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01.03-syntax_checkers.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfortin <kfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 13:05:53 by gmiyakaw          #+#    #+#             */
/*   Updated: 2023/08/04 19:43:19 by kfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// valid [<<] [word]
void	check_heredoc(t_data *data, int i, bool *invalid)
{
	if (i == data->token_count - 1)
	{
		syntax_error(data);
		*invalid = true;
	}
	if (data->tok_ch[i + 1].type != WORD)
	{
		syntax_error(data);
		*invalid = true;
	}
	else
		return ;
}

// valid: >[word] 
// must not be the last one
void	check_redir_out(t_data *data, int i, bool *invalid)
{
	if (i == data->token_count - 1)
	{
		syntax_error(data);
		*invalid = true;
	}
	if (data->tok_ch[i + 1].type != WORD)
	{
		syntax_error(data);
		*invalid = true;
	}
	else
		return ;
}

// valid: "< [word]" and "[word] < [word]"
void	check_redir_in(t_data *data, int i, bool *invalid)
{
	if (i == data->token_count - 1)
	{
		syntax_error(data);
		*invalid = true;
	}
	if (data->tok_ch[i + 1].type != WORD)
	{
		syntax_error(data);
		*invalid = true;
	}
	else
		return ;
}

// valid [>>] [word] and perhaps [word/fd] [>>] [word]
void	check_append(t_data *data, int i, bool *invalid)
{
	if (i == data->token_count - 1)
	{
		syntax_error(data);
		*invalid = true;
	}
	if (data->tok_ch[i + 1].type != WORD)
	{
		syntax_error(data);
		*invalid = true;
	}
	else
		return ;
}

//			TO BE FIXED: | << = legal. check what else as well.
void	check_pipe(t_data *data, int i, bool *invalid)
{
	if (i == 0 || i == (data->token_count - 1))
	{
		syntax_error(data);
		*invalid = true;
	}
	if (i > 0 && data->tok_ch[i - 1].type != WORD)
	{
		syntax_error(data);
		*invalid = true;
	}
	if (data->tok_ch[i + 1].type != WORD)
	{
		syntax_error(data);
		*invalid = true;
	}
	return ;
}
