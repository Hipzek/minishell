/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <hbelleuv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 20:09:50 by hbelleuv          #+#    #+#             */
/*   Updated: 2026/06/15 17:38:48 by hbelleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
D'après la norme C et POSIX, l'unique façon de partager un entier entre
le programme principal et un gestionnaire de signaux asynchrone en toute sécurité
est d'utiliser volatile sig_atomic_t

Ce type garantit que la lecture et l'écriture de la variable 
se font de manière atomique (en une seule instruction processeur)
évitant les crashs si le signal arrive au mauvais moment

La consigne demande de gérer Ctrl+C, Ctrl+D et Ctrl+\ :

- Ctrl+C (SIGINT) et Ctrl+\ (SIGQUIT)
sont de vrais signaux envoyés par le terminal

- Ctrl+D est une condition de Fin de Fichier (EOF). Il ne génère aucun signal
Lorsque l'utilisateur tape Ctrl+D, la fonction readline()
renvoie simplement un pointeur NULL

Il ne faut donc jamais tenter d'intercepter Ctrl+D avec sigaction
On le gere directement dans la boucle principale
*/

#include "../includes/minishell.h"
#include <signal.h>
#include <unistd.h>

void	heredoc_sigint(int sig)
{
	(void)sig;
	g_sig = SIGINT;
	close(STDIN_FILENO);
	write(STDOUT_FILENO, "\n", 1);
}

void	handle_signal(int sig)
{
	g_sig = sig;
	ft_putchar_fd('\n', STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	setup_inter_signals(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sa_int.sa_handler = handle_signal;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = 0;
	sigaction(SIGINT, &sa_int, NULL);
	sa_quit.sa_handler = SIG_IGN;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = 0;
	sigaction(SIGQUIT, &sa_quit, NULL);
}

void	setup_exec_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

void	setup_child_signal(void)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_DFL;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

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
