/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevisout <kevisout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 17:21:14 by kevso             #+#    #+#             */
/*   Updated: 2025/01/31 08:28:38 by kevisout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

/* Closes fd of the pipe and the file (-1 if no files)*/
void	close_pipes_and_fd(int *pipefd, int fd)
{
	close(pipefd[0]);
	close(pipefd[1]);
	close(fd);
}

/* Frees all allocated memory and exits with given code */
void	free_and_exit(t_pipex *pipex, int code)
{
	free_all(pipex);
	exit(code);
}

/* Create a child process, redirects STDIN and STDOUT and executes */
void	child_cmd1(t_pipex *pipex)
{
	pipex->pid = fork();
	if (pipex->pid == -1)
	{
		close_pipes_and_fd(pipex->pipefd, 0);
		free_and_exit(pipex, 1);
	}
	if (pipex->pid == 0)
	{
		pipex->file1.fd = open(pipex->file1.file, O_RDONLY);
		if (pipex->file1.fd == -1)
		{
			close_pipes_and_fd(pipex->pipefd, 0);
			free_and_exit(pipex, 1);
		}
		dup2(pipex->file1.fd, STDIN_FILENO);
		dup2(pipex->pipefd[1], STDOUT_FILENO);
		close_pipes_and_fd(pipex->pipefd, pipex->file1.fd);
		if (execve(pipex->cmd1.cmd, pipex->cmd1.args, pipex->env) == -1)
		{
			ft_putstr_fd("Error: command not found\n", STDERR_FILENO);
			free_and_exit(pipex, 127);
		}
	}
}

/* Create a child process, redirects STDIN and STDOUT and executes */
void	child_cmd2(t_pipex *pipex)
{
	pipex->pid2 = fork();
	if (pipex->pid2 == -1)
	{
		close_pipes_and_fd(pipex->pipefd, 0);
		free_and_exit(pipex, 1);
	}
	if (pipex->pid2 == 0)
	{
		pipex->file2.fd = open(pipex->file2.file,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (pipex->file2.fd == -1)
		{
			close_pipes_and_fd(pipex->pipefd, 0);
			free_and_exit(pipex, 1);
		}
		dup2(pipex->pipefd[0], STDIN_FILENO);
		dup2(pipex->file2.fd, STDOUT_FILENO);
		close_pipes_and_fd(pipex->pipefd, pipex->file2.fd);
		if (execve(pipex->cmd2.cmd, pipex->cmd2.args, pipex->env) == -1)
		{
			ft_putstr_fd("Error: command not found\n", STDERR_FILENO);
			free_and_exit(pipex, 127);
		}
	}
	close_pipes_and_fd(pipex->pipefd, 0);
}

/* Create a pipe, execute command 1 and 2 simultaneously */
int	exec(t_pipex *pipex)
{
	if (pipe(pipex->pipefd) == -1)
		return (0);
	child_cmd1(pipex);
	child_cmd2(pipex);
	waitpid(pipex->pid, NULL, 0);
	waitpid(pipex->pid2, NULL, 0);
	free_all(pipex);
	return (1);
}
