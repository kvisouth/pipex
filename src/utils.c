/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevisout <kevisout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 17:24:52 by kevso             #+#    #+#             */
/*   Updated: 2025/01/23 17:30:50 by kevisout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

/* Frees all allocated memory */
void	free_all(t_pipex *pipex)
{
	if (pipex->no_env == false)
		free(pipex->path);
	free_tab(pipex->cmd1.args);
	free_tab(pipex->cmd2.args);
	if (pipex->cmd1.is_absolute)
		free(pipex->cmd1.cmd);
	if (pipex->cmd2.is_absolute)
		free(pipex->cmd2.cmd);
}

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
