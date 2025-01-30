/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevso <kevso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 18:56:19 by kevisout          #+#    #+#             */
/*   Updated: 2025/01/30 03:02:22 by kevso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/wait.h>
# include <stdbool.h>

typedef struct s_cmd
{
	bool	is_absolute;
	char	*cmd;
	char	**args;
}	t_cmd;

typedef struct s_file
{
	int		fd;
	char	*file;
}	t_file;

typedef struct s_pipex
{
	char	**env;
	char	*path;
	bool	no_env;
	int		pipefd[2];
	pid_t	pid;
	pid_t	pid2;
	t_file	file1;
	t_file	file2;
	t_cmd	cmd1;
	t_cmd	cmd2;
}	t_pipex;

/* Init */
int		count_args(char *arg);
char	**concat_cmd_to_dirs(char *cmd, char **dirs);
char	**concat_slash_to_dirs(char **dirs);
int		init_args(t_cmd *cmd, char *arg, char *path);
int		init_cmd_struct(t_cmd *cmd, char *arg, char *path);
int		init(t_pipex *pipex, char **av, char **envp);

/* Exec */
int		exec(t_pipex *pipex);

/* Utils */
void	free_tab(char **tab);
void	free_all(t_pipex *pipex);

#endif