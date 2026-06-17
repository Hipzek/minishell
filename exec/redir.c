/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <hbelleuv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 16:11:47 by hbelleuv          #+#    #+#             */
/*   Updated: 2026/06/17 04:31:35 by hbelleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_apply_heredoc_redir(t_shell *shell, t_redir *redir)
{
	int	fd;

	fd = redir->heredoc_fd;
	if (fd < 0)
		clean_and_exit(shell, 130);
	dup2(fd, STDIN_FILENO);
	close(fd);
	redir->heredoc_fd = -1;
}

static void	ft_apply_input_redir(t_shell *shell, t_redir *redir)
{
	int	fd;

	fd = open(redir->file, O_RDONLY);
	if (fd < 0)
	{
		perror(redir->file);
		clean_and_exit(shell, 1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		ft_putstr_fd("minishell: No such file or directory\n", STDERR_FILENO);
		clean_and_exit(shell, 1);
	}
	close(fd);
}

static void	ft_apply_output_redir(t_shell *shell, t_redir *redir, int flags)
{
	int	fd;

	fd = open(redir->file, flags, 0644);
	if (fd < 0)
	{
		perror(redir->file);
		clean_and_exit(shell, 1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	apply_redir(t_shell *shell, t_cmd *cmd)
{
	t_redir	*redir;

	redir = cmd->redir;
	while (redir != NULL)
	{
		if (redir->type == HEREDOC)
			ft_apply_heredoc_redir(shell, redir);
		else if (redir->type == REDIR_IN)
			ft_apply_input_redir(shell, redir);
		else if (redir->type == REDIR_OUT)
			ft_apply_output_redir(shell, redir, O_WRONLY | O_CREAT | O_TRUNC);
		else if (redir->type == APPEND)
			ft_apply_output_redir(shell, redir, O_WRONLY | O_CREAT | O_APPEND);
		redir = redir->next;
	}
}
