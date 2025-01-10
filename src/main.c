/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevisout <kevisout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 19:01:20 by kevisout          #+#    #+#             */
/*   Updated: 2025/01/10 16:32:05 by kevisout         ###   ########.fr       */
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

int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;

	if (!parsing(&pipex, ac, av))
		return (1);
	if (!init(&pipex, av, envp))
		return (1);
	return (0);
}
