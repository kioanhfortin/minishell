/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00.00-main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfortin <kfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 11:14:38 by gmiyakaw          #+#    #+#             */
/*   Updated: 2023/08/05 18:22:17 by kfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_free_all_fd(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->cmd_count)
	{
		data->fd[i] = x_free(data->fd[i]);
		i++;
	}
	data->fd = x_free(data->fd);
}

int	ft_tchek_if_quote(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
			return (1);
		i++;
	}
	return (0);
}

void	ft_buff_null(t_data *data)
{
	g_exit_v = 0;
	printf("exit\n");
	ft_close_all();
	if (data)
		free_data_struct(data);
	exit(g_exit_v);
}

void	ft_main_program(t_data *data)
{
	add_history(data->buffer);
	if (ft_tchek_if_only_meta(data->buffer) == 1)
	{
		data->raw_line = ft_strdup(data->buffer);
		data->size_raw_line = ft_strlen(data->raw_line);
		data->tok_ch = ft_calloc(sizeof(struct s_token), MAX_CMD);
		ft_init_token(data->tok_ch);
		data = ft_split_struct_on_quote(data->raw_line, data);
		if (parser(data) == 0)
		{
			if (data->cmd_count == 1)
				ft_single_cmd(data);
			else
				ft_multi_pipe(data);
		}
		ft_clean_array_struct(data);
		ft_free_lexical(data);
		ft_free_pid(data);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_data	*data;

	(void)ac;
	(void)av;
	data = ft_calloc(sizeof(struct s_data), 1);
	ft_init_data_2(data);
	set_env_path(data, envp);
	ft_init_signal();
	while (1)
	{
		data->buffer = readline("minishell>> ");
		if (data->buffer == NULL)
			ft_buff_null(data);
		if (ft_strlen(data->buffer) > 0)
			ft_main_program(data);
		ft_close_all();
		if (data->buffer)
			data->buffer = x_free(data->buffer);
	}
	clear_history();
	if (data)
		free_data_struct(data);
	return (0);
}
