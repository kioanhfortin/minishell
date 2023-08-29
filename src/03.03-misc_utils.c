/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03.03-misc_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfortin <kfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 14:18:45 by gmiyakaw          #+#    #+#             */
/*   Updated: 2023/08/05 12:31:03 by kfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*clone_tok_ch(t_data *data, int start, int end, int *cmd_token_count)
{
	int		i;
	t_token	*cmd_tokens;

	cmd_tokens = x_calloc(sizeof(t_token) * data->token_count);
	if (ft_error_404(cmd_tokens) == 0)
		return (NULL);
	i = -1;
	while (++i <= end && start <= end)
	{
		cmd_tokens[i].type = data->tok_ch[start].type;
		cmd_tokens[i].quote = data->tok_ch[start].quote;
		cmd_tokens[i].arg = ft_strdup(data->tok_ch[start].arg);
		cmd_tokens[i].pos_in = data->tok_ch[start].pos_in;
		cmd_tokens[i].pos_out = data->tok_ch[start].pos_out;
		cmd_tokens[i].i = data->tok_ch[start].i;
		cmd_tokens[i].k = data->tok_ch[start].k;
		cmd_tokens[i].is_quoted = data->tok_ch[start].is_quoted;
		cmd_tokens[i].is_exp = data->tok_ch[start].is_exp;
		cmd_tokens[i].flag_do = data->tok_ch[start].flag_do;
		cmd_tokens[i].w_space_between = data->tok_ch[start].w_space_between;
		start++;
	}
	*cmd_token_count = i;
	return (cmd_tokens);
}

int	ft_error_404(t_token *cmd_tokens)
{
	if (!cmd_tokens)
	{
		perror(MLLC_ERR);
		return (0);
	}
	return (1);
}

t_token	*remove_token(t_token *tok_ch, int rmv_i, int *tok_count)
{
	int		i;
	int		new_i;
	t_token	*new_tok_ch;

	new_tok_ch = x_calloc(sizeof(t_token) * (*tok_count - 1));
	i = 0;
	new_i = 0;
	while (new_i < (*tok_count - 1))
	{
		if (i == rmv_i)
			i++;
		else
		{
			new_tok_ch[new_i] = copy_token(tok_ch[i]);
			new_i++;
			i++;
		}
	}
	free_token_chain(tok_ch, *tok_count);
	*tok_count -= 1;
	return (new_tok_ch);
}

t_token	copy_token(t_token old_tok)
{
	t_token	new_tok;

	new_tok.type = old_tok.type;
	new_tok.quote = old_tok.quote;
	new_tok.arg = ft_strdup(old_tok.arg);
	new_tok.pos_in = old_tok.pos_in;
	new_tok.pos_out = old_tok.pos_out;
	new_tok.i = old_tok.i;
	new_tok.k = old_tok.k;
	new_tok.is_quoted = old_tok.is_quoted;
	new_tok.is_exp = old_tok.is_exp;
	new_tok.flag_do = old_tok.flag_do;
	new_tok.w_space_between = old_tok.w_space_between;
	return (new_tok);
}

void	delete_file(char *filename)
{
	char	*tmp;
	char	*path;

	tmp = NULL;
	tmp = getcwd(tmp, 0);
	path = ft_strjoin_free(tmp, "/");
	tmp = (ft_strjoin_free(path, filename));
	if (access(tmp, F_OK) == 0)
	{
		unlink(tmp);
	}
	tmp = x_free(tmp);
	return ;
}
