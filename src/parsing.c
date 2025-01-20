/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevso <kevso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 19:40:54 by kevisout          #+#    #+#             */
/*   Updated: 2025/01/18 00:36:53 by kevso            ###   ########.fr       */
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
	return (ACCESSIBLE_FILE);
}

/* Parses "file1" */
int	parsing(t_pipex *pipex, int ac, char **av)
{
	if (ac != 5)
		return (ft_putstr_fd("pipex: Wrong number of arguments\n", 2), 0);
	pipex->file1.access = check_file1(av[1]);
	return (1);
}
