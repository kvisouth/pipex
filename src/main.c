/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevso <kevso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 19:01:20 by kevisout          #+#    #+#             */
/*   Updated: 2025/01/20 22:44:35 by kevso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	free_all(t_pipex *pipex)
{
	free(pipex->path);
	free_tab(pipex->cmd1.args);
	free_tab(pipex->cmd2.args);
}

int	exec(t_pipex *pipex)
{
	execve(pipex->cmd1.cmd, pipex->cmd1.args, pipex->env);
	perror("execve");
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;

	if (!parsing(&pipex, ac, av))
		return (1);
	if (!init(&pipex, av, envp))
		return (1);
	// if (!exec(&pipex))
	// 	return (1);
	free_all(&pipex);
	return (0);
}
