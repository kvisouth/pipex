/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevso <kevso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 19:01:20 by kevisout          #+#    #+#             */
/*   Updated: 2025/01/16 20:59:55 by kevso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

/* Cleans the structure */
void	clean_struct(t_pipex *pipex)
{
	free(pipex->cmd1.cmd);
	free(pipex->cmd2.cmd);
	(void)pipex;
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
