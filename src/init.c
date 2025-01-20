/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevso <kevso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 16:31:48 by kevisout          #+#    #+#             */
/*   Updated: 2025/01/20 22:34:05 by kevso            ###   ########.fr       */
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

/* Initializes the file1 struct variable */
int	init_struct_vars(t_pipex *pipex, char **av, char **envp)
{
	pipex->env = envp;
	get_path(envp, pipex);
	pipex->file1.file = av[1];
	pipex->file2.file = av[4];
	return (1);
}

/* Sets the is_absolute variable in cmd */
void	set_absolute_var(t_cmd *cmd, char *arg)
{
	if (arg[0] == '/')
		cmd->is_absolute = true;
	else
		cmd->is_absolute = false;
}

/* Concatenates "/" to each directory (/usr/bin -> /usr/bin/) */
char	**concat_slash_to_dirs(char **dirs)
{
	int		i;
	char	*tmp;
	char	**new_dirs;

	i = 0;
	while (dirs[i])
	{
		tmp = ft_strjoin(dirs[i], "/");
		if (!tmp)
			return (NULL);
		free(dirs[i]);
		dirs[i] = tmp;
		i++;
	}
	new_dirs = ft_calloc(i + 1, sizeof(char *));
	if (!new_dirs)
		return (NULL);
	i = 0;
	while (dirs[i])
	{
		new_dirs[i] = dirs[i];
		i++;
	}
	free(dirs);
	return (new_dirs);
}

/* Concatenates the cmd to each directory (/usr/bin/ -> /usr/bin/ls) */
char	**concat_cmd_to_dirs(char *cmd, char **dirs)
{
	int		i;
	char	*tmp;
	char	*command;
	char	**new_dirs;

	command = ft_substr(cmd, 0, ft_strchr(cmd, ' ') - cmd);
	if (!command)
		return (NULL);
	i = 0;
	while (dirs[i])
	{
		tmp = ft_strjoin(dirs[i], command);
		if (!tmp)
			return (free(command), NULL);
		free(dirs[i]);
		dirs[i] = tmp;
		i++;
	}
	new_dirs = ft_calloc(i + 1, sizeof(char *));
	if (!new_dirs)
		return (free(command), NULL);
	i = 0;
	while (dirs[i])
	{
		new_dirs[i] = dirs[i];
		i++;
	}
	free(dirs);
	free(command);
	return (new_dirs);
}

/* Counts the number of arguments in arg (ls -l -r -> 3) */
int	count_args(char *arg)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (arg[i])
	{
		if (arg[i] == ' ')
			count++;
		i++;
	}
	return (count + 1);
}

/* Initializes cmd->args */
int	get_args(char **dirs, t_cmd *cmd, char *arg)
{
	int		i;
	char	*token;

	i = 0;
	cmd->cmd = NULL;
	cmd->args = malloc(sizeof(char *) * (count_args(arg) + 1));
	if (!cmd->args)
		return (0);
	while (dirs[i])
	{
		if (access(dirs[i], X_OK) == 0)
		{
			cmd->cmd = ft_strdup(dirs[i]);
			if (!cmd->cmd)
				return (0);
			break ;
		}
		i++;
	}
	if (!cmd->cmd)
	{
		printf("dirs[0]: %s\n", dirs[0]);
		cmd->cmd = ft_strdup(dirs[0]);
		if (!cmd->cmd)
			return (0);
	}
	free_tab(dirs);
	cmd->args[0] = cmd->cmd;
	i = 1;
	token = ft_strtok(arg, " ");
	token = ft_strtok(NULL, " ");
	while (token)
	{
		cmd->args[i] = ft_strdup(token);
		if (!cmd->args[i])
			return (0);
		token = ft_strtok(NULL, " ");
		i++;
	}
	cmd->args[i] = NULL;
	return (1);
}

/* Initializes cmd->args */
int	init_args(t_cmd *cmd, char *arg, char *path)
{
	char	**dirs;

	dirs = ft_split(path, ':');
	if (!dirs)
		return (0);
	dirs = concat_slash_to_dirs(dirs);
	if (!dirs)
		return (0);
	dirs = concat_cmd_to_dirs(arg, dirs);
	if (!dirs)
		return (0);
	if (!get_args(dirs, cmd, arg))
		return (0);
	return (1);
}

/* Initializes the cmd struct */
int	init_cmd_struct(t_cmd *cmd, char *arg, char *path)
{
	set_absolute_var(cmd, arg);
	if (cmd->is_absolute == false)
	{
		if (!init_args(cmd, arg, path))
			return (0);
		cmd->args[0] = cmd->cmd;
	}
	else
	{
		printf("arg: %s\n", arg);
		cmd->args = ft_split(arg, ' ');
		if (!cmd->args)
			return (0);
	}
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
