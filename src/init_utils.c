/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevisout <kevisout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 16:10:02 by kevisout          #+#    #+#             */
/*   Updated: 2025/01/23 17:25:56 by kevisout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

/* Sets the is_absolute variable in cmd */
void	set_absolute_var(t_cmd *cmd, char *arg)
{
	if (arg[0] == '/')
		cmd->is_absolute = true;
	else
		cmd->is_absolute = false;
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
	i = -1;
	while (dirs[++i])
		new_dirs[i] = dirs[i];
	return (free(dirs), free(command), new_dirs);
}

/* Initializes the cmd struct */
int	init_cmd_struct(t_cmd *cmd, char *arg, char *path)
{
	set_absolute_var(cmd, arg);
	if (cmd->is_absolute == false && path)
	{
		if (!init_args(cmd, arg, path))
			return (0);
		cmd->args[0] = cmd->cmd;
	}
	else
	{
		cmd->cmd = ft_substr(arg, 0, ft_strchr(arg, ' ') - arg);
		if (!cmd->cmd)
			return (0);
		cmd->args = ft_split(arg, ' ');
		if (!cmd->args)
			return (0);
	}
	return (1);
}
