/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevisout <kevisout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 19:40:54 by kevisout          #+#    #+#             */
/*   Updated: 2025/01/10 14:28:41 by kevisout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

/* Checks if "file" exists and is readable */
int	check_file1(char *file)
{
	if (access(file, F_OK) == -1)
		return (ft_putstr_fd("Error: File does not exist\n", 2), 0);
	if (access(file, R_OK) == -1)
		return (ft_putstr_fd("Error: File is not readable\n", 2), 0);
	return (1);
}

char	*get_path(char **envp)
{
	int		i;
	char	*path;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path = ft_strdup(envp[i] + 5);
			if (!path)
				return (NULL);
			return (path);
		}
		i++;
	}
	return (NULL);
}

/* Parses "file1", "cmd1", "cmd2", no need to check "file2" */
int	parsing(int ac, char **av, char **envp)
{
	if (ac != 5)
		return (ft_putstr_fd("Error: Wrong number of arguments\n", 2), 0);
	if (!check_file1(av[1]))
		return (0);
	if (is_cmd_absolute(ft_strtok(av[2], " ")))
	{
		if (check_cmd_absolute(ft_strtok(av[2], " ")))
			return (0);
	}
	else if (!check_cmd_path(ft_strtok(av[2], " "), envp))
		return (0);
	if (is_cmd_absolute(ft_strtok(av[3], " ")))
	{
		if (check_cmd_absolute(ft_strtok(av[3], " ")))
			return (0);
	}
	else if (!check_cmd_path(ft_strtok(av[3], " "), envp))
		return (0);
	return (1);
}
