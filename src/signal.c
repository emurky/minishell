/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkombu <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 22:34:15 by rkombu            #+#    #+#             */
/*   Updated: 2021/09/19 22:34:17 by rkombu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int sig)
{
	(void)sig;
	if (g_shell.shell_state == FOREGROUNG_JOB)
		ft_putstr_fd("\n", STDOUT_FILENO);
	if (g_shell.shell_state == SHELL)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	return ;
}

void	sigquit_handler(int sig)
{
	if (g_shell.shell_state == FOREGROUNG_JOB)
		printf("Quit: %d\n", sig);
	return ;
}
