/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkombu <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 14:26:04 by rkombu            #+#    #+#             */
/*   Updated: 2021/10/17 14:26:06 by rkombu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array && array[i] != NULL)
		free(array[i++]);
	free(array);
}

static char	*check_relative_path(char *command)
{
	struct stat	path_stat;

	stat(command, &path_stat);
	if (!S_ISREG(path_stat.st_mode))
	{
		if (S_ISDIR(path_stat.st_mode))
		{
			printf("minishell: %s: is a directory\n", command);
			exit(126);
		}
		printf("minishell: %s: No such file or directory\n", command);
		exit(127);
	}
	if (access(command, F_OK) == -1)
		exit(print_error(command, 127));
	if (access(command, X_OK) == -1)
		exit(print_error(command, 127));
	return (command);
}

static char	**get_all_paths(void)
{
	int	i;

	i = 0;
	while (g_shell.envp[i] != NULL)
	{
		if (ft_strncmp("PATH=", g_shell.envp[i], 5) == 0)
		{
			return (ft_split(g_shell.envp[i] + 5, ':'));
		}
		i++;
	}
	return (NULL);
}

char	*full_path(char *command)
{
	int		i;
	char	**all_paths;
	char	*full_path;

	if (ft_strchr(command, '/'))
		return (check_relative_path(command));
	all_paths = get_all_paths();
	i = 0;
	if (!all_paths)
	{
		printf("minishell: %s: No such file or directory\n", command);
		exit(127);
	}
	while (all_paths[i] != NULL && *command)
	{
		full_path = ft_strjoin(all_paths[i], "/");
		full_path = append_str(full_path, command);
		if (access(full_path, F_OK | X_OK) != -1)
		{
			free_array(all_paths);
			return (full_path);
		}
		i++;
	}
	free_array(all_paths);
	printf("minishell: %s: command not found\n", command);
	exit(127);
}
