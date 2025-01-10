/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevisout <kevisout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 19:40:54 by kevisout          #+#    #+#             */
/*   Updated: 2025/01/10 16:43:22 by kevisout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

/* Checks if "file" exists and is readable */
int	check_file1(char *file)
{
	if (access(file, F_OK) == -1)
		return (perror("Error"), INEXISTANT_FILE);
	if (access(file, R_OK) == -1)
		return (perror("Error"), UNREADABLE_FILE);
	return (0);
}

/* Parses "file1" */
int	parsing(t_pipex *pipex, int ac, char **av)
{
	if (ac != 5)
		return (ft_putstr_fd("pipex: Wrong number of arguments\n", 2), 0);
	if (check_file1(av[1]) == INEXISTANT_FILE)
		pipex->file1.access = INEXISTANT_FILE;
	else if (check_file1(av[1]) == UNREADABLE_FILE)
		pipex->file1.access = UNREADABLE_FILE;
	else
		pipex->file1.access = ACCESSIBLE_FILE;
	return (1);
}
