/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevso <kevso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 18:56:19 by kevisout          #+#    #+#             */
/*   Updated: 2025/01/17 02:32:03 by kevso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define UNREADABLE_FILE 0
# define INEXISTANT_FILE -1
# define ACCESSIBLE_FILE 1

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
	char	*cmd;
	char	**args;
}	t_cmd;

typedef struct s_file
{
	int		access;
	int		fd;
	char	*file;
}	t_file;

typedef struct s_ptr
{
	char	*arg1;
	char	*arg2;
	char	**dirs1;
	char	**dirs2;
}	t_ptr;

typedef struct s_pipex
{
	char	**env;
	char	*path;
	bool	env_i;
	int		pipefd[2];
	pid_t	pid1;
	pid_t	pid2;
	t_file	file1;
	t_file	file2;
	t_cmd	cmd1;
	t_cmd	cmd2;
	t_ptr	ptr;
}	t_pipex;

/* Parsing */
int		check_file1(char *file);
int		parsing(t_pipex *pipex, int ac, char **av);
// int		is_cmd_absolute(char *cmd);
// int		check_cmd_absolute(char *cmd);
// int		check_cmd_path(char *cmd, char **envp);
// char	**concat_cmd_to_dirs(char *cmd, char **dirs);

/* Init */
char	*get_path(char **envp);
int		init_cmd(t_cmd *cmd, char *arg, char *path, t_pipex *pipex);
int		init(t_pipex *pipex, char **av, char **envp);

/* Exec */
int		exec(t_pipex *pipex);

void	free_tab(char **tab);

#endif