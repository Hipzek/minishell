/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <hbelleuv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 16:11:47 by hbelleuv          #+#    #+#             */
/*   Updated: 2026/06/12 19:23:48 by hbelleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	apply_redir_parent(t_shell *shell, t_cmd *cmd)
{
	t_redir	*redir;
	int		fd;

	(void)shell;
	redir = cmd->redir;
	while (redir != NULL)
	{
		if (redir->type == HEREDOC)
		{
			fd = redir->heredoc_fd;
			if (fd < 0)
				return (1);
			dup2(fd, STDIN_FILENO);
			close(fd);
			redir->heredoc_fd = -1;
		}
		else if (redir->type == REDIR_IN)
		{
			fd = open(redir->file, O_RDONLY);
			if (fd < 0)
			{
				perror(redir->file);
				return (1);
			}
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else if (redir->type == REDIR_OUT)
		{
			fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd < 0)
			{
				perror(redir->file);
				return (1);
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (redir->type == APPEND)
		{
			fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd < 0)
			{
				perror(redir->file);
				return (1);
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		redir = redir->next;
	}
	return (0);
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
			{
				//ft_putstr_fd("minishell: heredoc failed\n", STDERR_FILENO);
				clean_and_exit(shell, 130);
			}
			dup2(fd, STDIN_FILENO);
			close(fd);
			redir->heredoc_fd = -1;
		}
		else if (redir->type == REDIR_IN)
		{
			fd = open(redir->file, O_RDONLY);
			if (fd < 0)
			{
				perror(redir->file);
				clean_and_exit(shell, 1);
			}
			if (dup2(fd, STDIN_FILENO) == -1)
			{
				ft_putstr_fd("minishell: No such file or directory\n",
					STDERR_FILENO);
				clean_and_exit(shell, 1);
			}
			close(fd);
		}
		else if (redir->type == REDIR_OUT)
		{
			fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd < 0)
			{
				perror(redir->file);
				clean_and_exit(shell, 1);
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (redir->type == APPEND)
		{
			fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd < 0)
			{
				perror(redir->file);
				clean_and_exit(shell, 1);
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		redir = redir->next;
	}
//	printf("FIN DU TRAITE DES REDIRECTIONS\n");
	// printf(" FD = %d\n", fd);
	// ft_print_cmd(cmd);
}

int	is_builtin(t_cmd *cmd)
{
	char	*name;

	if (!cmd || !cmd->args || !cmd->args[0])
		return (0);
	name = cmd->args[0];
	if (ft_strncmp(name, "echo", 5) == 0)
		return (1);
	if (ft_strncmp(name, "cd", 3) == 0)
		return (1);
	if (ft_strncmp(name, "pwd", 4) == 0)
		return (1);
	if (ft_strncmp(name, "export", 7) == 0)
		return (1);
	if (ft_strncmp(name, "unset", 6) == 0)
		return (1);
	if (ft_strncmp(name, "env", 4) == 0)
		return (1);
	if (ft_strncmp(name, "exit", 5) == 0)
		return (1);
	return (0);
}

int	exec_builtin(t_shell *shell, t_cmd *cmd)
{
	char	*name;

	if (!shell || !cmd || !cmd->args || !cmd->args[0])
		return (1);
	name = cmd->args[0];
	if (ft_strncmp(name, "echo", 5) == 0)
		return (ft_echo(shell, cmd));
	if (ft_strncmp(name, "cd", 3) == 0)
		return (ft_cd(shell, cmd));
	if (ft_strncmp(name, "pwd", 4) == 0)
		return (ft_pwd(shell, cmd));
	if (ft_strncmp(name, "export", 7) == 0)
		return (ft_export(shell, cmd));
	if (ft_strncmp(name, "unset", 6) == 0)
		return (ft_unset(shell, cmd));
	if (ft_strncmp(name, "env", 4) == 0)
		return (ft_env(shell, cmd));
	if (ft_strncmp(name, "exit", 5) == 0)
		return (ft_exit(shell, cmd));
	return (-1);
}

/*
if (WIFEXITED(status)) //Terminaison classique (exit(0) ou exit(127))
else if (WIFSIGNALED(status)) //Terminaison forcee par un signal
*/
void	wait_pipeline(t_shell *shell, pid_t last_pid)
{
	int		status;
	pid_t	wait_pid;

	wait_pid = waitpid(-1, &status, 0);
	while (wait_pid > 0)
	{
		if (wait_pid == last_pid)
		{
			if (WIFEXITED(status))
				shell->exit_code = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				shell->exit_code = 128 + WTERMSIG(status);
				if (WTERMSIG(status) == SIGQUIT)
					ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
				else if (WTERMSIG(status) == SIGINT)
					printf("\n");
			}
		}
		wait_pid = waitpid(-1, &status, 0);
	}
}

/*
// TODO : A supprimer au moment de la correction
void	ft_print_arr(char **arr) {
	int i = -1;

	while (arr[++i])
		printf("%s\n", arr[i]);
}

void	ft_print_ttype(t_token_type type) {
	printf("TYPE ");
	if (type == WORD)
		printf("WORD ");
	else if (type == PIPE)
		printf("PIPE ");
	else if (type == REDIR_IN)
		printf("REDIR_IN ");
	else if (type == REDIR_OUT)
		printf("REDIR_OUT ");
	else if (type == APPEND)
		printf("APPEND ");
	else if (type == HEREDOC)
		printf("HEREDOC ");
}

void	ft_print_token(t_token *token) {
	ft_print_ttype(token->token_type);
	printf("VALUE = %s\n", token->value);
}

void	ft_print_redir(t_redir *redir) {
	ft_print_ttype(redir->type);
	printf(" PATH = %s || FD = %d\n", redir->file, redir->heredoc_fd); 
}

void	ft_print_cmd(t_cmd *cmd) {
	printf("ARGS = ");
	ft_print_arr(cmd->args);
	printf("\nPATH = %s|| PID = %d\n", cmd->path, cmd->pid);
}

void	ft_print_shell(t_shell *shell, int mod) {
	printf("SHELL CONTAINS \n");
	if (mod == 1)
		ft_print_arr(shell->env);
	if (mod == 0)
	{
		while (shell->token) {
			ft_print_token(shell->token);
			shell->token = shell->token->next;
		}
	}
	printf("STDIN = [%d] || STDOUT = [%d]\n", shell->saved_stdin, shell->saved_stdout);
	printf("EXIT CODE = [%d]\n", shell->exit_code);
}*/
