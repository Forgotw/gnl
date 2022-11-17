/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 10:31:49 by lsohler           #+#    #+#             */
/*   Updated: 2022/11/17 12:21:29 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if ((char)c == '\0')
		return ((char *)&s[i]);
	return (0);
}

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	while (src[i] != '\0' && i + 1 < dstsize)
	{
		dst[i] = src[i];
		i++;
	}
	if (dstsize != 0)
		dst[i] = '\0';
	return (ft_strlen(src));
}

char	*ft_stashjoin(char *stash, char *buffer)
{
	size_t		i;
	size_t		j;
	char		*joined;

	i = -1;
	j = -1;
	if (!stash)
	{
		stash = malloc(sizeof(char));
		stash[0] = '\0';
	}
	joined = malloc(sizeof(char) * (ft_strlen(stash) + ft_strlen(buffer)) + 1);
	if (!joined)
		return (NULL);
	while (stash[++i] != '\0')
		joined[i] = stash[i];
	while (buffer[++j] != '\0')
		joined[i + j] = buffer[j];
	joined[i + j] = '\0';
	free(stash);
	return (joined);
}
