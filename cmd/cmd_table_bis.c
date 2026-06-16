/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_table_bis.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <hbelleuv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 13:59:43 by hbelleuv          #+#    #+#             */
/*   Updated: 2026/06/17 01:48:39 by hbelleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_args(t_token *token)
{
	int	count;

	count = 0;
	while (token != NULL && token->token_type != PIPE)
	{
		if (is_redirection(token->token_type))
			token = token->next->next;
		else
		{
			count++;
			token = token->next;
		}
	}
	return (count);
}

static t_redir	*ft_create_redir_node(t_token_type type,
	char *file, int heredoc_fd)
{
	t_redir	*new_node;

	new_node = ft_calloc(1, sizeof(t_redir));
	if (!new_node)
	{
		if (heredoc_fd >= 0)
			close(heredoc_fd);
		return (NULL);
	}
	new_node->type = type;
	new_node->file = ft_strdup(file);
	if (!new_node->file)
	{
		if (heredoc_fd >= 0)
			close(heredoc_fd);
		free(new_node);
		return (NULL);
	}
	new_node->heredoc_fd = heredoc_fd;
	return (new_node);
}

static int	add_redir(t_redir **redir, t_token_type type,
	char *file, int heredoc_fd)
{
	t_redir	*new_node;
	t_redir	*last_node;

	new_node = ft_create_redir_node(type, file, heredoc_fd);
	if (!new_node)
		return (-1);
	if (*redir == NULL)
		*redir = new_node;
	else
	{
		last_node = *redir;
		while (last_node->next != NULL)
			last_node = last_node->next;
		last_node->next = new_node;
	}
	return (0);
}

static int	ft_process_redirection(t_shell *shell, t_cmd *cmd, t_token **token)
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
			if (ft_process_redirection(shell, cmd, token) == -1)
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
