/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevso <kevso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 16:08:12 by kevisout          #+#    #+#             */
/*   Updated: 2025/01/30 03:03:47 by kevso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

/* strdup() the first valid directory into cmd->cmd */
int	get_args_loop_1(char **dirs, t_cmd *cmd)
{
	int	i;

	i = 0;
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
	return (1);
}

/* strdup() the arguments of a command into cmd->args[1] to the last one */
int	get_args_loop_2(t_cmd *cmd, char *arg)
{
	char	*token;
	int		i;

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

/* Fills cmd->cmd in loop1, then if failed, just strdup() the first directory */
/* Then fills cmd->args from args[1] to args[n] in loop2 */
int	get_args(char **dirs, t_cmd *cmd, char *arg)
{
	cmd->cmd = NULL;
	cmd->args = malloc(sizeof(char *) * (count_args(arg) + 1));
	if (!cmd->args)
		return (0);
	if (!get_args_loop_1(dirs, cmd))
		return (0);
	if (!cmd->cmd)
	{
		cmd->cmd = ft_strdup(dirs[0]);
		if (!cmd->cmd)
			return (0);
	}
	free_tab(dirs);
	cmd->args[0] = cmd->cmd;
	if (!get_args_loop_2(cmd, arg))
		return (0);
	return (1);
}

/* Splits PATH= into multiple directories and concatenates "/cmd" to it */
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
