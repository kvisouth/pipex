/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevisout <kevisout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 19:01:20 by kevisout          #+#    #+#             */
/*   Updated: 2025/01/10 17:31:11 by kevisout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

/* Frees a tab */
void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

/*
- cmd1 reads from file1 and writes to the pipe
- cmd2 reads from the pipe and writes to file2
*/
int	exec(t_pipex *pipex)
{
    int pipefd[2];
    pid_t pid1, pid2;

    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        return (1);
    }

    pid1 = fork();
    if (pid1 == -1)
    {
        perror("fork");
        return (1);
    }

    if (pid1 == 0)
    {
        // Child process 1: cmd1
        int infile = open(pipex->file1.file, O_RDONLY);
        if (infile < 0)
        {
            perror("open infile");
            exit(1);
        }
        dup2(infile, STDIN_FILENO);
        close(infile);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[0]);
        close(pipefd[1]);
        execve(pipex->cmd1.cmd, pipex->cmd1.args, pipex->env);
        perror("execve cmd1");
        exit(1);
    }

    pid2 = fork();
    if (pid2 == -1)
    {
        perror("fork");
        return (1);
    }

    if (pid2 == 0)
    {
        // Child process 2: cmd2
        int outfile = open(pipex->file2.file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (outfile < 0)
        {
            perror("open outfile");
            exit(1);
        }
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[1]);
        close(pipefd[0]);
        dup2(outfile, STDOUT_FILENO);
        close(outfile);
        execve(pipex->cmd2.cmd, pipex->cmd2.args, pipex->env);
        perror("execve cmd2");
        exit(1);
    }

    close(pipefd[0]);
    close(pipefd[1]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    return (0);
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
	return (0);
}
