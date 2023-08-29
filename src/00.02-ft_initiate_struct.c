/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00.02-ft_initiate_struct.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfortin <kfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 14:53:11 by kfortin           #+#    #+#             */
/*   Updated: 2023/08/05 11:36:09 by kfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_init_data(t_data *data)
{
	data->raw_line = NULL;
	data->size_raw_line = 0;
	data->cmd_count = 1;
	data->pos_cmd_i = 0;
	data->back_up_out = 0;
	data->back_up_in = 0;
	data->nb_meta = 0;
	data->k_temp = 0;
	data->i = 0;
	data->j = 0;
	data->count = 0;
}

void	ft_init_data_2(t_data *data)
{
	data->cmd_list = NULL;
	data->raw_line = NULL;
	data->size_raw_line = 0;
	data->token_count = 0;
	data->token_count_temp = 0;
	data->cmd_count = 1;
	data->envp = NULL;
	data->paths = NULL;
	data->pid = 0;
	data->fd = 0;
	data->pos_cmd_i = 0;
	data->back_up_out = 0;
	data->back_up_in = 0;
	data->nb_meta = 0;
	data->k_temp = 0;
	data->i = 0;
	data->j = 0;
	data->count = 0;
}

void	set_env_path(t_data *data, char **envp)
{
	int	i;
	int	env_len;

	env_len = ft_arrlen(envp);
	data->envp = x_calloc(sizeof(char *) * (env_len + 1));
	if (!data->envp)
	{
		perror(MLLC_ERR);
		clean_exit(data);
	}
	i = 0;
	while (i < env_len)
	{
		data->envp[i] = ft_strdup(envp[i]);
		i++;
	}
	data->envp[i] = NULL;
	data->paths = pathfinder(data);
}

char	**pathfinder(t_data *data)
{
	int		i;
	char	*tmp;
	char	**paths;

	i = 0;
	while (data->envp[i] && ft_strnstr(data->envp[i], "PATH=", 5) == 0)
		i++;
	if (!data->envp[i])
	{
		perror(PTH_ERR);
		clean_exit(data);
	}
	tmp = data->envp[i] + 5;
	paths = ft_split(tmp, ':');
	return (paths);
}

void	ft_init_token(t_token *tok_ch)
{
	int	i;

	i = 0;
	while (i < MAX_CMD)
	{
		tok_ch[i].is_quoted = 0;
		tok_ch[i].is_exp = 0;
		tok_ch[i].i = 0;
		tok_ch[i].k = 0;
		tok_ch[i].pos_in = 0;
		tok_ch[i].pos_out = 0;
		tok_ch[i].flag_do = 0;
		tok_ch[i].w_space_between = 0;
		i++;
	}
}
