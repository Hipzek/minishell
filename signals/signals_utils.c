/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <hbelleuv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 00:00:00 by hbelleuv          #+#    #+#             */
/*   Updated: 2026/06/15 00:00:00 by hbelleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	disable_sigint(struct sigaction *old_sa)
{
	struct sigaction	sa_new;

	sa_new.sa_handler = SIG_IGN;
	sigemptyset(&sa_new.sa_mask);
	sa_new.sa_flags = 0;
	sigaction(SIGINT, &sa_new, old_sa);
}

void	restore_sigint(struct sigaction *old_sa)
{
	sigaction(SIGINT, old_sa, NULL);
}
