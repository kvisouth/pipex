/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevso <kevso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 17:21:14 by kevso             #+#    #+#             */
/*   Updated: 2025/01/16 17:22:46 by kevso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

/* Redirects stdin to file1 and stdout to pipefd[1] */
int	redirect_file1(t_pipex pipex)
{
	if (dup2(pipex.file1.fd, STDIN_FILENO) == -1)
		return (perror("Error"), 0);
	close(pipex.file1.fd);
	if (dup2(pipex.pipefd[1], STDOUT_FILENO) == -1)
		return (perror("Error"), 0);
	close(pipex.pipefd[1]);
	return (1);
}

/* Creates file2, and redirects stdout to it */
int	redirect_file2(t_pipex pipex)
{
	if (dup2(pipex.pipefd[0], STDIN_FILENO) == -1)
		return (perror("Error"), 0);
	pipex.file2.fd = open(pipex.file2.file, O_WRONLY
			| O_CREAT | O_TRUNC, 0644);
	if (pipex.file2.fd == -1)
		return (perror("Error"), 0);
	if (dup2(pipex.file2.fd, STDOUT_FILENO) == -1)
		return (perror("Error"), 0);
	close(pipex.pipefd[0]);
	close(pipex.file2.fd);
	return (1);
}

/* Creates a child process and executes the command (cmd1 or cmd2) */
int	execute_cmd(t_pipex *pipex, int command)
{
	if (command == 1)
	{
		pipex->pid1 = fork();
		if (pipex->pid1 == -1)
			return (perror("Error"), 0);
		if (pipex->pid1 == 0)
		{
			execve(pipex->cmd1.cmd, pipex->cmd1.args, pipex->env);
			perror("Error");
			exit(EXIT_FAILURE);
		}
	}
	else if (command == 2)
	{
		pipex->pid2 = fork();
		if (pipex->pid2 == -1)
			return (perror("Error"), 0);
		if (pipex->pid2 == 0)
		{
			execve(pipex->cmd2.cmd, pipex->cmd2.args, pipex->env);
			perror("Error");
			exit(EXIT_FAILURE);
		}
	}
	return (1);
}

int	exec(t_pipex *pipex)
{
	if (pipe(pipex->pipefd) == -1)
		return (perror("Error"), 0);
	if (!redirect_file1(*pipex))
		return (0);
	if (!execute_cmd(pipex, 1))
		return (0);
	if (dup2(pipex->pipefd[0], STDIN_FILENO) == -1)
		return (perror("Error"), 0);
	if (!redirect_file2(*pipex))
		return (0);
	if (!execute_cmd(pipex, 2))
		return (0);
	waitpid(pipex->pid1, NULL, 0);
	waitpid(pipex->pid2, NULL, 0);
	return (1);
}
