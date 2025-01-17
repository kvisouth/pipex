/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevisout <kevisout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 19:01:20 by kevisout          #+#    #+#             */
/*   Updated: 2025/01/17 18:33:29 by kevisout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	clean_struct(t_pipex *pipex)
{
	free(pipex->cmd1.cmd);
	free(pipex->cmd2.cmd);
	free_tab(pipex->cmd1.args);
	free_tab(pipex->cmd2.args);
	free(pipex->ptr.arg1);
	free(pipex->ptr.arg2);
	free(pipex->path);
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;

	if (!parsing(&pipex, ac, av))
		return (1);
	if (!init(&pipex, av, envp))
		return (1);
	if (!exec(&pipex))
		return (1);
	clean_struct(&pipex);
	return (0);
}
