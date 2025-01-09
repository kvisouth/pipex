/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nok <nok@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 19:01:20 by kevisout          #+#    #+#             */
/*   Updated: 2025/01/09 17:49:39 by nok              ###   ########.fr       */
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

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

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

/* Adds '/' and "cmd" to each "dir" */
char	**concat_cmd_to_dirs(char *cmd, char **dirs)
{
	char	**new_dirs;
	char	*new_dir_slash;
	char	*new_dir_cmd;
	int		i;

	i = 0;
	while (dirs[i])
		i++;
	new_dirs = malloc(sizeof(char *) * (i + 1));
	if (!new_dirs)
		return (NULL);
	i = 0;
	while (dirs[i])
	{
		new_dir_slash = ft_strjoin(dirs[i], "/");
		if (!new_dir_slash)
			return (NULL);
		new_dir_cmd = ft_strjoin(new_dir_slash, cmd);
		if (!new_dir_cmd)
			return (NULL);
		new_dirs[i] = new_dir_cmd;
		free(new_dir_slash);
		i++;
	}
	return (new_dirs[i] = NULL, free_tab(dirs), new_dirs);
}

/* Checks if "cmd" exists and is executable */
int	check_cmd(char *cmd, char **envp)
{
	char	*path;
	char	**dirs;
	int		i;

	path = get_path(envp);
	if (!path)
		return (ft_putstr_fd("Error: PATH not found\n", 2), 0);
	dirs = ft_split(path, ':');
	free(path);
	if (!dirs)
		return (ft_putstr_fd("Error: Failed malloc\n", 2), 0);
	dirs = concat_cmd_to_dirs(cmd, dirs);
	if (!dirs)
		return (ft_putstr_fd("Error: Failed malloc\n", 2), free_tab(dirs), 0);
	i = 0;
	while (dirs[i])
	{
		if (access(dirs[i], F_OK) == 0 && access(dirs[i], X_OK) == 0)
			return (free_tab(dirs), 1);
		i++;
	}
	free_tab(dirs);
	return (ft_putstr_fd("Error: Command not found\n", 2), 0);
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
