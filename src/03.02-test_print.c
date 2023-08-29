/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03.02-test_print.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfortin <kfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 15:05:34 by gmiyakaw          #+#    #+#             */
/*   Updated: 2023/08/05 12:23:11 by kfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_token(t_token *token)
{
	printf("\t\tprinting token\n");
	if (token->arg)
		printf("|%s|\n", token->arg);
	if (token->is_quoted)
		printf("is quoted: %d\n", token->is_quoted);
	if (token->type == WORD)
		printf("type: word\n");
	else if (token->type == PIPE)
		printf("type: pipe\n");
	else if (token->type == REDIR_IN)
		printf("type: redir in\n");
	else if (token->type == REDIR_OUT)
		printf("type: redir out\n");
	else if (token->type == HEREDOC)
		printf("type: heredoc\n");
	else if (token->type == APPEND)
		printf("type: append\n");
	else if (token->type == DOLLAR)
		printf("type: dollar sign");
	printf("quoted?:%d\n", token->is_quoted);
	printf("space between the next?:%d\n", token->w_space_between);
	printf("expansion?: %d\n__________\n", token->is_exp);
	return ;
}

void	print_token_chain(t_token *token_chain, int token_count)
{
	int	i;

	i = -1;
	while (++i < token_count)
	{
		print_token(&token_chain[i]);
	}
}

void	print_struct(t_data *data)
{
	printf("\tprinting struct:\n");
	printf("raw line: %s\n", data->raw_line);
	printf("token count: %d\n", data->token_count);
	printf("size_raw_line: %d\n", data->size_raw_line);
	printf("cmd_count: %d\n", data->cmd_count);
}

void	print_cmd_tok_chain(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->cmd_count)
	{
		printf("\t\t printing command token chain cmd: %d\n", i);
		printf("cmdlist token count: %d\n", data->cmd_list[i].cmd_token_count);
		print_token_chain(data->cmd_list[i].cmd_tokens,
			data->cmd_list[i].cmd_token_count);
		printf("\n\t\tend of token chain \n");
	}
}

void	print_cmd_struct(t_cmd *cmd)
{
	int	i;

	printf("printing command struct:\n");
	print_token_chain(cmd->cmd_tokens, cmd->cmd_token_count);
	printf("cmd token count: %d\n", cmd->cmd_token_count);
	printf("___\narguments:\n");
	i = -1;
	while (cmd->args[++i])
	{
		printf("arg[%d]:|%s|\n", i, cmd->args[i]);
	}
	printf("null terminator check: arg[%d] |%s|\n", i, cmd->args[i]);
	printf("command path: %s\n", cmd->cmd_path);
	printf("__________\n");
}
