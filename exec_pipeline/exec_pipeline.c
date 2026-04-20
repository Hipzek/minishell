#include "pipex.h"

static int	ft_parent_sys_error(t_px *px, char *erreur)
{
	perror(erreur);
	ft_cleanup_px(px);
	return (1);
}

static void	ft_child_sys_error(t_px *px, char *error, int exit_code)
{
	perror(error);
	ft_cleanup_px(px);
	_exit(exit_code);
}

/* forward declarations removed — functions are defined with external linkage to
	match prototypes in includes/pipex.h */

int	ft_exec_pipeline(t_px *px)
{
	int	i;

	if (!px)
		return (1);
	if (ft_first_cmds(px, 0) != 0)
		return (1);
	i = 1;
	while (i < (px->nb_cmds - 1))
	{
		if (ft_middle_cmd(px, i) != 0)
			return (1);
		i++;
	}
	if (ft_last_cmd(px, i) != 0)
		return (1);
	return (0);
}

int	ft_first_cmds(t_px *px, int i)
{
	pid_t	pid;

	if (!px)
		return (1);
	if (pipe(px->pipefd) < 0)
		return (ft_parent_sys_error(px, "pipe"));
	pid = fork();
	if (pid < 0)
		return (ft_parent_sys_error(px, "fork"));
	if (pid == 0)
	{
		if (dup2(px->fd_relai, 0) < 0)
			ft_child_sys_error(px, "dup2", 1);
		if (dup2(px->pipefd[1], 1) < 0)
			ft_child_sys_error(px, "dup2", 1);
		close(px->fd_relai);
		close(px->pipefd[1]);
		close(px->pipefd[0]);
		close(px->file.outfile_fd);
		execve(px->cmds[i].path, px->cmds[i].ready_execve, px->envp);
		if (px->cmds[i].ready_execve && px->cmds[i].ready_execve[0])
			ft_child_sys_error(px, px->cmds[i].ready_execve[0], 127);
		ft_child_sys_error(px, "execve", 127);
	}
	close(px->fd_relai);
	close(px->pipefd[1]);
	px->fd_relai = px->pipefd[0];
	return (0);
}

int	ft_middle_cmd(t_px *px, int i)
{
	pid_t	pid;

	if (!px)
		return (1);
	if (pipe(px->pipefd) < 0)
		return (ft_parent_sys_error(px, "pipe"));
	pid = fork();
	if (pid < 0)
		return (ft_parent_sys_error(px, "fork"));
	if (pid == 0)
	{
		if (dup2(px->fd_relai, 0) < 0)
			ft_child_sys_error(px, "dup2", 1);
		if (dup2(px->pipefd[1], 1) < 0)
			ft_child_sys_error(px, "dup2", 1);
		close(px->fd_relai);
		close(px->pipefd[1]);
		close(px->pipefd[0]);
		close(px->file.outfile_fd);
		execve(px->cmds[i].path, px->cmds[i].ready_execve, px->envp);
		ft_child_sys_error(px, "execve", 127);
	}
	close(px->fd_relai);
	close(px->pipefd[1]);
	px->fd_relai = px->pipefd[0];
	return (0);
}

int	ft_last_cmd(t_px *px, int i)
{
	pid_t	pid;

	if (!px)
		return (1);
	pid = fork();
	if (pid < 0)
		return (ft_parent_sys_error(px, "fork"));
	if (pid == 0)
	{
		if (dup2(px->fd_relai, 0) < 0)
			ft_child_sys_error(px, "dup2", 1);
		if (dup2(px->file.outfile_fd, 1) < 0)
			ft_child_sys_error(px, "dup2", 1);
		close(px->fd_relai);
		close(px->file.outfile_fd);
		execve(px->cmds[i].path, px->cmds[i].ready_execve, px->envp);
		if (px->cmds[i].ready_execve && px->cmds[i].ready_execve[0])
			ft_child_sys_error(px, px->cmds[i].ready_execve[0], 127);
		ft_child_sys_error(px, "execve", 127);
	}
	close(px->fd_relai);
	close(px->file.outfile_fd);
	return (0);
}

