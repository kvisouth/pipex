/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevisout <kevisout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 18:56:19 by kevisout          #+#    #+#             */
/*   Updated: 2025/01/23 16:14:42 by kevisout         ###   ########.fr       */
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

/*
- cmd is dynamically allocated : It's the executable (/bin/ls)
- args only contains pointers to 'cmd' and his arguments from argv (-l -a ..)
	args[0] is a pointer to 'cmd'
	args[1] is a pointer to '-l' (from argv) (using ft_strtok)
*/
typedef struct s_cmd
{
	bool	is_absolute;
	char	*cmd;
	char	**args;
	pid_t	pid;
}	t_cmd;

typedef struct s_file
{
	int		access;
	int		fd;
	char	*file;
}	t_file;

typedef struct s_pipex
{
	char	**env;
	char	*path;
	int		pipefd[2];
	t_file	file1;
	t_file	file2;
	t_cmd	cmd1;
	t_cmd	cmd2;
}	t_pipex;

/* Parsing */
int		parsing(t_pipex *pipex, int ac, char **av);

/* Init */
int		count_args(char *arg);
char	**concat_cmd_to_dirs(char *cmd, char **dirs);
char	**concat_slash_to_dirs(char **dirs);
int		init_args(t_cmd *cmd, char *arg, char *path);
int		init_cmd_struct(t_cmd *cmd, char *arg, char *path);
int		init(t_pipex *pipex, char **av, char **envp);

/* Exec */
int		exec(t_pipex *pipex);

void	free_tab(char **tab);
void	free_all(t_pipex *pipex);

#endif