/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 12:35:01 by hdelmas           #+#    #+#             */
/*   Updated: 2022/12/29 16:37:22 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

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

	res = malloc(sizeof(t_arg));
	if (!res)
		return (NULL);
	res->file.input = ft_strdup(av[1]);
	if (!res->file.input)
		return (free_all(NULL, res));
	res->file.output = ft_strdup(av[4]);
	if (!res->file.output)
		return (free_all(NULL, res));
	fd = open(res->file.output, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	if (fd == -1)
		return (free_all(NULL, res));
	close(fd);
	res->cmd1 = cmd_init(av[2]);
	if (!res->cmd1.cmd)
		return (free_all(NULL, res));
	res->cmd2 = cmd_init(av[3]);
	if (!res->cmd2.cmd)
		return (free_all(NULL, res));
	if (access(res->file.input, F_OK | R_OK) == -1)
		return (input_file_error(res));
	return (res);
}

static t_access	*exe_init(char **path, t_arg *arg)
{
	t_access	*res;

	res = malloc(sizeof(t_access));
	if (!res)
		return (NULL);
	res->exec1 = get_access(path, arg->cmd1.cmd);
	res->exec2 = get_access(path, arg->cmd2.cmd);
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
		ft_putstr_fd("Wrong number of arguments\n", 2);
		return (1);
	}
	arg = arg_init(av);
	if (!arg)
		return (1);
	path = get_path(envp);
	exe = exe_init(path, arg);
	free_tab(path);
	if (!exe->exec2)
	{
		free_all(exe, arg);
		return (127);
	}
	res = ppx_exec(exe, arg, envp);
	free_all(exe, arg);
	return (res);
}
