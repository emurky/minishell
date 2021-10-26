/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkombu <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 21:26:25 by rkombu            #+#    #+#             */
/*   Updated: 2021/10/19 21:26:29 by rkombu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	mini_env()
{
	int	i;

	i = 0;
	while (g_shell.envp[i])
	{
		if (ft_strchr(g_shell.envp[i], '='))
			printf("%s\n", g_shell.envp[i]);
		i++;
	}
	return (true);
}
