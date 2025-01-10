/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevisout <kevisout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 18:56:19 by kevisout          #+#    #+#             */
/*   Updated: 2025/01/10 14:34:55 by kevisout         ###   ########.fr       */
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

typedef struct s_pipex
{
	
}	t_pipex;

/* Parsing */
int		parsing(int ac, char **av, char **envp);
int		is_cmd_absolute(char *cmd);
int		check_cmd_absolute(char *cmd);
int		check_cmd_path(char *cmd, char **envp);
char	**concat_cmd_to_dirs(char *cmd, char **dirs);
char	*get_path(char **envp);
int		check_file1(char *file);

void	free_tab(char **tab);

#endif