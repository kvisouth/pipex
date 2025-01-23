/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevisout <kevisout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 19:01:20 by kevisout          #+#    #+#             */
/*   Updated: 2025/01/23 17:31:38 by kevisout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;

	if (!parsing(&pipex, ac, av))
		return (1);
	if (!init(&pipex, av, envp))
		return (1);
	if (!exec(&pipex))
		return (1);
	free_all(&pipex);
	return (0);
}
