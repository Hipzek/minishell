/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redir_parent.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <hbelleuv@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 04:30:55 by hbelleuv          #+#    #+#             */
/*   Updated: 2026/06/17 04:30:57 by hbelleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_apply_input_redir(t_redir *redir)
{
	int	fd;

	if (redir->type == REDIR_IN)
	{
		fd = open(redir->file, O_RDONLY);
		if (fd < 0)
			return (perror(redir->file), 1);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	return (0);
}

static int	ft_apply_output_redir(t_redir *redir)
{
	int	fd;

	if (redir->type == REDIR_OUT)
	{
		fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
			return (perror(redir->file), 1);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else if (redir->type == APPEND)
	{
		fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd < 0)
			return (perror(redir->file), 1);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	return (0);
}

static int	ft_apply_single_redir(t_redir *redir)
{
	int	fd;

	if (redir->type == HEREDOC)
	{
		fd = redir->heredoc_fd;
		if (fd < 0)
			return (1);
		dup2(fd, STDIN_FILENO);
		close(fd);
		redir->heredoc_fd = -1;
	}
	else if (ft_apply_input_redir(redir) == 1)
		return (1);
	else if (ft_apply_output_redir(redir) == 1)
		return (1);
	return (0);
}

int	apply_redir_parent(t_shell *shell, t_cmd *cmd)
{
	t_redir	*redir;

	(void)shell;
	redir = cmd->redir;
	while (redir != NULL)
	{
		if (ft_apply_single_redir(redir) == 1)
			return (1);
		redir = redir->next;
	}
	return (0);
}
