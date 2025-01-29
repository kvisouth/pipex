/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevisout <kevisout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 16:31:48 by kevisout          #+#    #+#             */
/*   Updated: 2025/01/29 03:36:02 by kevisout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

/* Get the PATH variable from the environment (envp) */
int	get_path(char **envp, t_pipex *pipex)
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
				return (0);
			pipex->path = path;
			return (1);
		}
		i++;
	}
	return (-1);
}

/* Initializes variables of the structure */
int	init_struct_vars(t_pipex *pipex, char **av, char **envp)
{
	pipex->env = envp;
	get_path(envp, pipex);
	if (!pipex->path)
		pipex->no_env = true;
	else
		pipex->no_env = false;
	pipex->file1.file = av[1];
	pipex->file2.file = av[4];
	return (1);
}

int	init(t_pipex *pipex, char **av, char **envp)
{
	if (!init_struct_vars(pipex, av, envp))
		return (0);
	if (!init_cmd_struct(&pipex->cmd1, av[2], pipex->path))
		return (0);
	if (!init_cmd_struct(&pipex->cmd2, av[3], pipex->path))
		return (0);
	return (1);
}
