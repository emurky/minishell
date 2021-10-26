/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkombu <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 21:25:51 by rkombu            #+#    #+#             */
/*   Updated: 2021/10/19 21:25:56 by rkombu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	mini_pwd(void)
{
	char	*wd;

	wd = NULL;
	wd = getcwd(wd, 0);
	if (!wd)
	{
		printf("minishell: pwd: %s\n", strerror(errno));
		g_shell.exit_code = 1;
	}
	printf("%s\n", wd);
	free(wd);
	g_shell.exit_code = 0;
	return (true);
}
