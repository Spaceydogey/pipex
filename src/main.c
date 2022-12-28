/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 12:35:01 by hdelmas           #+#    #+#             */
/*   Updated: 2022/12/28 18:30:31 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	free_all(t_access *exe, t_arg *arg)
{
	if (exe)
	{
		if (exe->exec1)
			free(exe->exec1);
		if (exe->exec1)
			free(exe->exec2);
		free(exe);
	}
	if (arg)
	{
		if (arg->file.input)
			free(arg->file.input);
		if (arg->file.output)
			free(arg->file.output);
		if (arg->cmd1.tab)
			free_tab(arg->cmd1.tab);
		if (arg->cmd2.tab)
			free_tab(arg->cmd2.tab);
		free(arg);
	}
	return (errno);
}

static t_cmd	cmd_init(char *str)
{
	t_cmd	res;
	char	**tab;
	int		i;

	res.cmd = NULL;
	tab = ft_split(str, ' ');
	if (!tab)
		return (res);
	res.cmd = tab[0];
	res.tab = tab;
	return (res);
}

static t_arg	*arg_init(char **av)
{
	t_arg	*res;
	int		fd;
//free all on return if malloc fails
	res = malloc(sizeof(t_arg));
	if (!res)
		return (NULL);
	res->file.input = ft_strdup(av[1]);
	if (!res->file.input)
		return (NULL);
	res->file.output = ft_strdup(av[4]);
	if (!res->file.output)
		return (NULL);
	fd = open(res->file.output, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	close(fd);
	res->cmd1 = cmd_init(av[2]);
	if (!res->cmd1.cmd)
		return (NULL);
	res->cmd2 = cmd_init(av[3]);
	if (!res->cmd2.cmd)
		return (NULL);
	if (access(res->file.input, F_OK | X_OK) == -1)
	{
		perror(res->file.input);
		return (NULL);
	}
	return (res);
}

static t_access	*exe_init(char **path, t_arg *arg)
{
	t_access	*res;

	res = malloc(sizeof(t_access));
	if (!res)
		return (NULL);
	res->exec1 = get_access(path, arg->cmd1.cmd);
	// if (!res->exec1)
	// {
	// 	strerror(errno);
	// }
	res->exec2 = get_access(path, arg->cmd2.cmd);
	// if (!res->exec2)
	// {
	// 	strerror(errno);
	// }
	free_tab(path);
	return (res);
}

int	main(int ac, char **av, char **envp)
{
	char		**path;
	t_access	*exe;
	t_arg		*arg;
	int			res;

	if (ac != 5)
	{
		perror("");
		return (1);
	}
	arg = arg_init(av);
	if (!arg)
		return (1);
	path = get_path(envp);
	exe = exe_init(path, arg);
	if (!exe->exec2)
	{
		return (127);
	}
	res = ppx_exec(exe, arg, envp);
	free_all(exe, arg);
	return (res);
}
