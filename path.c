/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 13:08:10 by hdelmas           #+#    #+#             */
/*   Updated: 2022/12/22 16:49:00 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	c1;
	unsigned char	c2;

	i = 0;
	while (s1[i] == s2[i] && s1[i] && s2[i])
		i++;
	c1 = (unsigned char)s1[i];
	c2 = (unsigned char)s2[i];
	if (i < n)
		return (c1 - c2);
	return (0);

}

size_t	ft_strcpy(char *dst, const char *src)
{
	size_t	i;
	size_t	srclen;

	i = -1;
	srclen = -1;
	while (src[++srclen])
		;
	while (src[++i])
		dst[i] = src[i];
	dst[i] = '\0';
	return (srclen);
}

char *get_path(char **envp)
{
	int		i;
	char	*res;

	i = -1;
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], "PATH", 4) == 0)
		{
			ft_strcpy(res, envp[i]);
			return (res);
		}
	}
	return (NULL);
}
