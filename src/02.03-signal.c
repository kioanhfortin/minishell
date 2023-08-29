/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02.03-signal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfortin <kfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 17:12:01 by kfortin           #+#    #+#             */
/*   Updated: 2023/08/05 11:52:02 by kfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_handler_ctrl_c(int signum, siginfo_t *s_info, void *content)
{
	(void)content;
	(void)s_info;
	if (signum == SIGINT)
	{
		rl_on_new_line();
		rl_redisplay();
		ft_printf("  \n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	ft_init_signal(void)
{
	struct sigaction	sa_int;

	sa_int.sa_sigaction = &ft_handler_ctrl_c;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = SA_RESTART;
	signal(SIGQUIT, SIG_IGN);
	if (sigaction(SIGINT, &sa_int, NULL) == -1)
	{
		perror("sigaction");
		exit(0);
	}
}
