/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevisout <kevisout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 17:21:14 by kevso             #+#    #+#             */
/*   Updated: 2025/01/23 15:52:37 by kevisout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

/* Redirects stdin and stdout to files or pipes */
void	redirect_cmd(t_pipex *pipex, int i)
{
	if (i == 1)
	{
		dup2(pipex->file1.fd, STDIN_FILENO);
		dup2(pipex->pipefd[1], STDOUT_FILENO);
		close(pipex->file1.fd);
		close(pipex->pipefd[1]);
	}
	else if (i == 2)
	{
		dup2(pipex->pipefd[0], STDIN_FILENO);
		dup2(pipex->file2.fd, STDOUT_FILENO);
		close(pipex->pipefd[0]);
		close(pipex->file2.fd);
	}
}

/* Creates a child process and executes a command */
int	child_process(t_pipex *pipex, int i)
{
	if (i == 1)
	{
		pipex->cmd1.pid = fork();
		if (pipex->cmd1.pid == -1)
			return (perror("Error"), 1);
		if (pipex->cmd1.pid == 0)
		{
			if (execve(pipex->cmd1.cmd, pipex->cmd1.args, pipex->env) == -1)
				return (perror("Error"), 1);
		}
	}
	else if (i == 2)
	{
		pipex->cmd2.pid = fork();
		if (pipex->cmd2.pid == -1)
			return (perror("Error"), 1);
		if (pipex->cmd2.pid == 0)
		{
			if (execve(pipex->cmd2.cmd, pipex->cmd2.args, pipex->env) == -1)
				return (perror("Error"), 1);
		}
	}
	return (1);
}

/* Redirects, executes, redirects, execute, waits */
int	exec(t_pipex *pipex)
{
	if (pipe(pipex->pipefd) == -1)
		return (perror("Error"), 1);
	pipex->file1.fd = open(pipex->file1.file, O_RDONLY);
	if (pipex->file1.fd == -1)
		return (perror("Error"), 1);
	redirect_cmd(pipex, 1);
	child_process(pipex, 1);
	pipex->file2.fd = open(pipex->file2.file, O_CREAT
			| O_WRONLY | O_TRUNC, 0644);
	if (pipex->file2.fd == -1)
		return (perror("Error"), 1);
	redirect_cmd(pipex, 2);
	child_process(pipex, 2);
	waitpid(pipex->cmd1.pid, NULL, 0);
	waitpid(pipex->cmd2.pid, NULL, 0);
	return (1);
}
