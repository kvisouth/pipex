/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevso <kevso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 19:01:20 by kevisout          #+#    #+#             */
/*   Updated: 2025/01/21 00:42:05 by kevso            ###   ########.fr       */
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
	pid_t	pid;

	if (pipe(pipex->pipefd) == -1)
		return (0);
	pid = fork();
	if (pid == -1)
		return (0);
	if (pid == 0)
	{
		dup2(pipex->pipefd[1], STDOUT_FILENO);
		close(pipex->pipefd[0]);
		close(pipex->pipefd[1]);
		execve(pipex->cmd1.args[0], pipex->cmd1.args, pipex->env);
	}
	else
	{
		waitpid(pid, NULL, 0);
		dup2(pipex->pipefd[0], STDIN_FILENO);
		close(pipex->pipefd[1]);
		close(pipex->pipefd[0]);
		execve(pipex->cmd2.args[0], pipex->cmd2.args, pipex->env);
	}
	return (1);
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
	// free_all(&pipex);
	return (0);
}
