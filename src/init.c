/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevisout <kevisout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 16:31:48 by kevisout          #+#    #+#             */
/*   Updated: 2025/01/10 16:35:06 by kevisout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

/* Get the PATH variable from the environment (envp) */
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

/* Initializes the "cmd" structure */
int	init_cmd(t_cmd *cmd, char *arg)
{
	cmd->args = ft_split(arg, ' ');
	if (!cmd->args)
		return (0);
	cmd->cmd = ft_strtok(arg, " ");
	if (!cmd->cmd)
		return (0);
	return (1);
}

/* Initializes the "pipex" structure */
int	init(t_pipex *pipex, char **av, char **envp)
{
	pipex->env = envp;
	pipex->env_i = false;
	pipex->path = get_path(envp);
	if (!pipex->path)
		pipex->env_i = true;
	pipex->file1.file = av[1];
	pipex->file2.file = av[4];
	if (pipex->file1.access == 1)
	{
		pipex->file1.fd = open(av[1], O_RDONLY);
		if (pipex->file1.fd == -1)
			return (ft_putstr_fd("Unexpected error\n", 2), 0);
	}
	if (!init_cmd(&pipex->cmd1, av[2]))
		return (ft_putstr_fd("malloc error\n", 2), 0);
	if (!init_cmd(&pipex->cmd2, av[3]))
		return (ft_putstr_fd("malloc error\n", 2), 0);
	return (1);
}
