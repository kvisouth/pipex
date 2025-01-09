/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevisout <kevisout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 19:01:20 by kevisout          #+#    #+#             */
/*   Updated: 2025/01/09 19:45:45 by kevisout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

char	*ft_strtok(char *str, char *delim)
{
	static char	*ptr;
	char		*ret;
	int			i;

	if (str)
		ptr = str;
	if (!ptr || !*ptr)
		return (NULL);
	ret = ptr;
	i = 0;
	while (ptr[i])
	{
		if (ft_strchr(delim, ptr[i]))
		{
			ptr[i++] = '\0';
			break ;
		}
		i++;
	}
	ptr += i;
	return (ret);
}

/* Parses "file1", "cmd1", "cmd2", no need to check "file2" */
int	parsing(int ac, char **av, char **envp)
{
	if (ac != 5)
		return (ft_putstr_fd("Error: Wrong number of arguments\n", 2), 0);
	if (!check_file1(av[1]))
		return (0);
	if (!check_cmd(ft_strtok(av[2], " "), envp))
		return (0);
	if (!check_cmd(ft_strtok(av[3], " "), envp))
		return (0);
	return (1);
}

int	main(int ac, char **av, char **envp)
{
	if (!parsing(ac, av, envp))
		return (1);
	printf("Parsing OK\n");
	return (0);
}
