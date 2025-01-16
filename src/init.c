/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevso <kevso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 16:31:48 by kevisout          #+#    #+#             */
/*   Updated: 2025/01/16 15:52:14 by kevso            ###   ########.fr       */
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

/* Concatenates the path with the command */
int	concat_path_with_cmd(t_cmd *cmd, char *arg, char *path)
{
	char	*cmd_to_concat;
	char	**dirs;
	int		i;

	if (!arg)
		return (ft_putstr_fd("Error: Failed malloc\n", 2), 0);
	cmd_to_concat = ft_strtok(arg, " ");
	dirs = ft_split(path, ':');
	if (!dirs)
		return (ft_putstr_fd("Error: Failed malloc\n", 2), 0);
	dirs = concat_cmd_to_dirs(cmd_to_concat, dirs);
	if (!dirs)
		return (ft_putstr_fd("Error: Failed malloc\n", 2), free_tab(dirs), 0);
	i = 0;
	while (dirs[i])
	{
		if (access(dirs[i], F_OK) == 0 && access(dirs[i], X_OK) == 0)
		{
			cmd->cmd = dirs[i];
			return (1);
		}
		i++;
	}
	free_tab(dirs);
	return (ft_putstr_fd("Error: Command not found\n", 2), 0);
}

/* Initializes the "cmd" structure */
int	init_cmd(t_cmd *cmd, char *arg, char *path)
{
	if (!concat_path_with_cmd(cmd, ft_strdup(arg), path))
		return (ft_putstr_fd("malloc error\n", 2), 0);
	cmd->args = ft_split(arg, ' ');
	if (!cmd->args)
		return (ft_putstr_fd("malloc error\n", 2), 0);
	free(cmd->args[0]);
	cmd->args[0] = cmd->cmd;
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
	pipex->pipefd[0] = -1;
	pipex->pipefd[1] = -1;
	if (pipex->file1.access == ACCESSIBLE_FILE)
	{
		pipex->file1.fd = open(av[1], O_RDONLY);
		if (pipex->file1.fd == -1)
			return (ft_putstr_fd("Unexpected error\n", 2), 0);
	}
	if (!init_cmd(&pipex->cmd1, av[2], pipex->path))
		return (ft_putstr_fd("malloc error\n", 2), 0);
	if (!init_cmd(&pipex->cmd2, av[3], pipex->path))
		return (ft_putstr_fd("malloc error\n", 2), 0);
	return (1);
}
