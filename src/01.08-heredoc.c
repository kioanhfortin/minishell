/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01.08-heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmiyakaw <gmiyakaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 15:57:26 by gmiyakaw          #+#    #+#             */
/*   Updated: 2023/07/31 18:41:40 by gmiyakaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	just_here_docking(t_cmd *cmd, int metachar_pos)
{
	char	*buffer;

	delete_file(TMP_HD);
	cmd->fd_input = open("tmp_heredoc", O_RDWR | O_CREAT, 0666);
	while (1)
	{
		buffer = readline("heredocking>>");
		if (ft_strlen(buffer) > 0)
		{
			buffer = heredoc_find_expansion(cmd, buffer, metachar_pos);
			if (ft_strcmp(buffer, cmd->cmd_tokens[metachar_pos + 1].arg) == 0)
				break ;
			write(cmd->fd_input, buffer, ft_strlen(buffer));
			write(cmd->fd_input, "\n", 1);
		}
		buffer = x_free(buffer);
	}
	if (buffer != NULL)
		buffer = x_free(buffer);
	return ;
}

char	*heredoc_switcheroo(char *buffer, int dollar_pos, t_exp *exp)
{
	char	*head;
	char	*tail;
	char	*head_and_target;
	char	*final_buffer;

	if (exp->target == NULL)
	{
		buffer = heredoc_replace_null(buffer, dollar_pos, exp);
		return (buffer);
	}
	head = ft_strdup_end_start(buffer, 0, dollar_pos - 1);
	tail = ft_strdup_end_start(buffer, dollar_pos + 1 + \
		ft_strlen(exp->alias), ft_strlen(buffer));
	head_and_target = ft_strjoin(head, exp->target);
	if (head_and_target == NULL)
		head_and_target = ft_strdup(exp->target);
	final_buffer = ft_strjoin(head_and_target, tail);
	if (final_buffer == NULL)
		final_buffer = ft_strdup(head_and_target);
	buffer = x_free(buffer);
	buffer = ft_strdup(final_buffer);
	heredoc_free_arrays(final_buffer, head_and_target, tail, head);
	return (buffer);
}

void	heredoc_free_arrays(char *a, char *b, char *c, char *d)
{
	if (a)
		a = x_free(a);
	if (b)
		b = x_free(b);
	if (c)
		c = x_free(c);
	if (d)
		d = x_free(d);
	return ;
}

char	*heredoc_replace_null(char *buffer, int dollar_position, t_exp *exp)
{
	char	*pre_alias;
	char	*post_alias;

	pre_alias = ft_strdup_end_start(buffer, 0, (dollar_position - 1));
	post_alias = ft_strdup_end_start(buffer, dollar_position + \
		ft_strlen(exp->alias) + 1, ft_strlen(buffer));
	buffer = x_free(buffer);
	buffer = ft_strjoin(pre_alias, post_alias);
	pre_alias = x_free(pre_alias);
	post_alias = x_free(post_alias);
	return (buffer);
}

char	*heredoc_alias_finder(char *buffer, int dollar_pos)
{
	char	*alias;
	int		end;

	end = dollar_pos;
	while (is_valid_alias_char(buffer[++end]) == true)
		alias = ft_substr(buffer, dollar_pos + 1, end - dollar_pos);
	return (alias);
}
