/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 13:08:10 by hdelmas           #+#    #+#             */
/*   Updated: 2022/12/29 16:47:49 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	**get_path(char **envp)
{
	int		i;
	char	*str;
	char	**res;

	i = -1;
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], "PATH", 4) == 0)
		{
			str = ft_strdup(envp[i]);
			if (!str)
				return (NULL);
			res = ft_split(&str[5], ':');
			free(str);
			return (res);
		}
	}
	return (NULL);
}

static char	*check_access(char **path, char *cmd)
{
	char	*res;
	char	*tmp;
	int		i;

	i = -1;
	while (path[++i])
	{
		tmp = ft_strjoin(path[i], "/");
		if (!tmp)
			return (NULL);
		res = ft_strjoin(tmp, cmd);
		if (!res)
			return (NULL);
		free(tmp);
		if (access(res, F_OK | X_OK) != -1)
			return (res);
		free(res);
	}
	return (NULL);
}

char	*get_access(char **path, char *cmd)
{
	char	*res;

	if (ft_strncmp(cmd, "/", 1) == 0)
	{
		res = ft_strdup(cmd);
		if (!res)
			return (NULL);
		if (access(res, F_OK | X_OK) != -1)
			return (res);
	}
	else
	{
		res = check_access(path, cmd);
		if (res)
			return (res);
	}
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
	return (NULL);
}
