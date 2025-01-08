/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevisout <kevisout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 19:01:20 by kevisout          #+#    #+#             */
/*   Updated: 2025/01/08 19:11:39 by kevisout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	check_valid_file_name(char *file1, char *file2)
{
	
}

int	parsing(int ac, char **av)
{
	if (ac != 5)
		return (ft_putstr_fd("Error: Wrong number of arguments\n", 2), 0);
	if (!check_valid_file_name(av[1], av[4]))
		return (ft_putstr_fd("Error: File doesn't exist\n", 2), 0);
}

int	main(int ac, char **av)
{
	if (!parsing(ac, av))
		return (1);
	return (0);
}