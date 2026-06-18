/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <hbelleuv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 16:11:47 by hbelleuv          #+#    #+#             */
/*   Updated: 2026/06/17 22:39:19 by hbelleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	open_dup_parent(t_redir *redir, int target_fd)
{
	int	fd;

	if (redir->type == REDIR_IN)
		fd = open(redir->file, O_RDONLY);
	else if (redir->type == REDIR_OUT)
		fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		return (perror(redir->file), 1);
	dup2(fd, target_fd);
	close(fd);
	return (0);
}

int	apply_redir_parent(t_shell *shell, t_cmd *cmd)
{
	t_redir	*redir;

	(void)shell;
	redir = cmd->redir;
	while (redir != NULL)
	{
		if (redir->type == HEREDOC)
		{
			if (redir->heredoc_fd < 0)
				return (1);
			dup2(redir->heredoc_fd, STDIN_FILENO);
			close(redir->heredoc_fd);
			redir->heredoc_fd = -1;
		}
		else if (redir->type == REDIR_IN)
		{
			if (open_dup_parent(redir, STDIN_FILENO) != 0)
				return (1);
		}
		else if (open_dup_parent(redir, STDOUT_FILENO) != 0)
			return (1);
		redir = redir->next;
	}
	return (0);
}

static void	apply_redir_in(t_shell *shell, t_redir *redir)
{
	int	fd;

	fd = open(redir->file, O_RDONLY);
	if (fd < 0)
		(perror(redir->file), clean_and_exit(shell, 1));
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		ft_putstr_fd("minishell: No such file or directory\n",
			STDERR_FILENO);
		clean_and_exit(shell, 1);
	}
	close(fd);
}

static void	apply_redir_out(t_shell *shell, t_redir *redir)
{
	int	fd;
	int	flags;

	if (redir->type == REDIR_OUT)
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	else
		flags = O_WRONLY | O_CREAT | O_APPEND;
	fd = open(redir->file, flags, 0644);
	if (fd < 0)
		(perror(redir->file), clean_and_exit(shell, 1));
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	apply_redir(t_shell *shell, t_cmd *cmd)
{
	t_redir	*redir;
	int		fd;

	redir = cmd->redir;
	while (redir != NULL)
	{
		if (redir->type == HEREDOC)
		{
			fd = redir->heredoc_fd;
			if (fd < 0)
				clean_and_exit(shell, 130);
			dup2(fd, STDIN_FILENO);
			close(fd);
			redir->heredoc_fd = -1;
		}
		else if (redir->type == REDIR_IN)
			apply_redir_in(shell, redir);
		else
			apply_redir_out(shell, redir);
		redir = redir->next;
	}
}
