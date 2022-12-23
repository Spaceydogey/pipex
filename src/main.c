/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 12:35:01 by hdelmas           #+#    #+#             */
/*   Updated: 2022/12/23 15:43:49 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int ac, char **av, char **envp)
{
	char	**path;
	char	*acc;
	int		i;

	(void)ac;
	path = get_path(envp);// to free
	if (!path)
		return (1);
	i = -1;
	while (path[++i])
	{
		printf("%s\n", path[i]);
	}
	acc = get_access(path, "ls");
	if (!acc)
		return (1);
	free_tab(path);
	printf("%s\n",acc);

}
