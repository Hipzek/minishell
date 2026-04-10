/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <hbelleuv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 13:25:58 by hbelleuv          #+#    #+#             */
/*   Updated: 2026/04/10 15:29:18 by hbelleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv)
{
	(void)argc;
	int	status;

	/*
	char	*input;
	input = readline("minishell >");
	*/

	if (fork() == 0)
		execve("/bin/ls", &argv[1], argv + 1);

	wait(&status);
	
	return (EXIT_SUCCESS);
}
