/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 13:02:04 by hdelmas           #+#    #+#             */
/*   Updated: 2022/12/29 17:03:23 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static int	exec_cmd1(char *exec, t_arg *arg, char **envp, int p_fd[2])
{
	int		f_fd;

	close(p_fd[0]);
	if (dup2(p_fd[1], STDOUT_FILENO) == -1)
	{
		close(p_fd[1]);
		return (errno);
	}
	close(p_fd[1]);
	f_fd = open(arg->file.input, O_RDONLY);
	if (f_fd == -1)
		return (errno);
	if (dup2(f_fd, STDIN_FILENO) == -1)
	{
		close(f_fd);
		return (errno);
	}
	close(f_fd);
	return (execve(exec, arg->cmd1.tab, envp));
}

static int	exec_cmd2(char *exec, t_arg *arg, char **envp, int p_fd[2])
{
	int		f_fd;

	close(p_fd[1]);
	if (dup2(p_fd[0], STDIN_FILENO) == -1)
	{
		close(p_fd[0]);
		return (errno);
	}
	close(p_fd[0]);
	f_fd = open(arg->file.output, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	if (f_fd == -1)
		return (errno);
	if (dup2(f_fd, STDOUT_FILENO) == -1)
	{
		close(f_fd);
		return (errno);
	}
	close(f_fd);
	return (execve(exec, arg->cmd2.tab, envp));
}

static int	pipe_close(int fd[2])
{
	close(fd[0]);
	close(fd[1]);
	return (errno);
}

static	int	ft_fork(int *id)
{
	*id = fork();
	if (*id == -1)
		return (-1);
	return (0);
}

int	ppx_exec(t_access *exe, t_arg *arg, char **envp)
{
	int		p_fd[2];
	int		id[2];
	int		res;

	res = 0;
	if (pipe(p_fd) == -1)
		return (errno);
	if (ft_fork(&id[0]) == -1)
		return (pipe_close(p_fd));
	if (id[0] == 0)
	{
		if (exec_cmd1(exe->exec1, arg, envp, p_fd) == -1)
			res = errno;
	}
	else
	{	
		wait(NULL);
		if (ft_fork(&id[1]) == -1)
			return (pipe_close(p_fd));
		if (id[1] == 0)
			if (exec_cmd2(exe->exec2, arg, envp, p_fd) == -1)
				res = errno;
	}
	pipe_close(p_fd);
	return (res);
}
