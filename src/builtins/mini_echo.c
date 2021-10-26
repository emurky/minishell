/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkombu <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 21:22:22 by rkombu            #+#    #+#             */
/*   Updated: 2021/10/19 21:25:46 by rkombu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	no_newline_option(char *str)
{
	if (!str || *str++ != '-' || *str++ != 'n')
		return (false);
	while (*str)
		if (*str++ != 'n')
			return (false);
	return (true);
}

bool	mini_echo(char *argv[])
{
	bool	newline;
	int		i;

	discard_quotes_in_argv(argv);
	i = 1;
	newline = true;
	if (no_newline_option(argv[1]))
	{
		i++;
		newline = false;
	}
	if (argv[i])
		printf("%s", argv[i++]);
	while (argv[i])
		printf(" %s", argv[i++]);
	if (newline)
		printf("\n");
	g_shell.exit_code = 0;
	return (true);
}
