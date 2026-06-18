/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <hbelleuv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 00:00:00 by hbelleuv          #+#    #+#             */
/*   Updated: 2026/06/17 22:38:44 by hbelleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	redir_append_node(t_redir **redir, t_redir *new_node)
{
	t_redir	*last_node;

	if (*redir == NULL)
		*redir = new_node;
	else
	{
		last_node = *redir;
		while (last_node->next != NULL)
			last_node = last_node->next;
		last_node->next = new_node;
	}
}

static int	add_redir(t_redir **redir, t_token_type type,
	char *file, int heredoc_fd)
{
	t_redir	*new_node;

	new_node = ft_calloc(1, sizeof(t_redir));
	if (!new_node)
	{
		if (heredoc_fd >= 0)
			close(heredoc_fd);
		return (-1);
	}
	new_node->type = type;
	new_node->file = ft_strdup(file);
	if (!new_node->file)
	{
		if (heredoc_fd >= 0)
			close(heredoc_fd);
		free(new_node);
		return (-1);
	}
	new_node->heredoc_fd = heredoc_fd;
	redir_append_node(redir, new_node);
	return (0);
}

static int	handle_redir_token(t_shell *shell, t_cmd *cmd, t_token **token)
{
	int	heredoc_fd;

	heredoc_fd = -1;
	if ((*token)->token_type == HEREDOC)
	{
		heredoc_fd = read_heredoc(shell, (*token)->next->value, cmd);
		if (heredoc_fd == -1)
			return (-1);
	}
	if (add_redir(&(cmd->redir), (*token)->token_type,
			(*token)->next->value, heredoc_fd) == -1)
	{
		if (heredoc_fd >= 0)
			close(heredoc_fd);
		return (-1);
	}
	*token = (*token)->next->next;
	return (0);
}

int	fill_cmd_args(t_shell *shell, t_cmd *cmd, t_token **token)
{
	int	i;

	i = 0;
	while (*token != NULL && (*token)->token_type != PIPE)
	{
		if (is_redirection((*token)->token_type))
		{
			if (handle_redir_token(shell, cmd, token) == -1)
				return (-1);
		}
		else
		{
			cmd->args[i] = ft_strdup((*token)->value);
			if (cmd->args[i] == NULL)
				return (-1);
			i++;
			*token = (*token)->next;
		}
	}
	cmd->args[i] = NULL;
	return (0);
}
