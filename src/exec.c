/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nok <nok@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 17:21:14 by kevso             #+#    #+#             */
/*   Updated: 2025/01/23 15:32:15 by nok              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	exec(t_pipex *pipex)
{
	if (pipe(pipex->pipefd) == -1)
		return (perror("Error"), 0);
	pipex->file1.fd = open(pipex->file1.file, O_RDONLY);
	if (pipex->file1.fd == -1)
		return (perror("Error"), 0);
	dup2(pipex->file1.fd, STDIN_FILENO);
	dup2(pipex->pipefd[1], STDOUT_FILENO);
	close(pipex->file1.fd);
	close(pipex->pipefd[1]);
	pipex->cmd1.pid = fork();
	if (pipex->cmd1.pid == -1)
		return (perror("Error"), 0);
	if (pipex->cmd1.pid == 0)
	{
		if (execve(pipex->cmd1.cmd, pipex->cmd1.args, pipex->env) == -1)
			return (perror("Error"), 1);
	}
	pipex->file2.fd = open(pipex->file2.file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (pipex->file2.fd == -1)
		return (perror("Error"), 0);
	dup2(pipex->file2.fd, STDOUT_FILENO);
	dup2(pipex->pipefd[0], STDIN_FILENO);
	close(pipex->file2.fd);
	close(pipex->pipefd[0]);
	pipex->cmd2.pid = fork();
	if (pipex->cmd2.pid == -1)
		return (perror("Error"), 0);
	if (pipex->cmd2.pid == 0)
	{
		if (execve(pipex->cmd2.cmd, pipex->cmd2.args, pipex->env) == -1)
			return (perror("Error"), 1);
	}
	waitpid(pipex->cmd1.pid, NULL, 0);
	waitpid(pipex->cmd2.pid, NULL, 0);
	return (1);
}
