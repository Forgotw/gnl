/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 10:19:47 by lsohler           #+#    #+#             */
/*   Updated: 2022/11/11 14:52:19 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
//#include <string.h>
#include <stdio.h>
//#include <stdlib.h>
//#include <unistd.h>
#include <fcntl.h>

char	*ft_strdup(const char *s1)
{
	char	*s2;
	int		i;

	i = 0;
	s2 = malloc(sizeof(char) * ft_strlen(s1) + 1);
	if (!s2)
		return (NULL);
	while (s1[i] != '\0')
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

char	*ft_read_to_stash(char *stash, int fd)
{
	char	*buffer;
	int		i;

	i = 1;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	while (!ft_strchr(stash, '\n') && i > 0)
	{
		i = read(fd, buffer, BUFFER_SIZE);
		if (i == -1)
		{
			free(stash);
			free(buffer);
			return (NULL);
		}
		buffer[i] = '\0';
		stash = ft_stashjoin(stash, buffer);
	}
	free(buffer);
	return (stash);
}

char	*ft_stash_to_nl(char *stash)
{
	char		*line;
	size_t		i;

	i = 0;
	if (!stash[i])
		return (NULL);
	while (stash[i] != '\n' && stash[i] != '\0')
		i++;
	if (stash[i] == '\n')
		i++;
	line = malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	ft_strlcpy(line, stash, i + 1);
	return (line);
}

char	*ft_trim_stash(char *stash)
{
	int		i;	
	char	*str;

	i = 0;
	while (stash[i] != '\n' && stash[i] != '\0')
		i++;
	if (stash[i] == '\0')
	{
		free(stash);
		return (NULL);
	}	
	if (stash[i] == '\n')
		i++;
	str = ft_strdup(&stash[i]);
	free(stash);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*stash[4096];
	char		*str;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	stash[fd] = ft_read_to_stash(stash[fd], fd);
	if (!stash[fd])
		return (NULL);
	str = ft_stash_to_nl(stash[fd]);
	stash[fd] = ft_trim_stash(stash[fd]);
	return (str);
}
/*
int	main(void)
{
	int		fd;
	char	*str;
	int		i;
//	static char *test;
//	char testjoin[] = "Bonjour";

	i = 0;
	fd = open("gnltest", O_RDONLY);
	str = get_next_line(fd);
	printf("%s", str);
	while (i != 15 && str != NULL)
	{
		str = get_next_line(fd);
		printf("%sGNL\n", str);
		i++;
	}
//	test = ft_strjoin(test, testjoin);
//	printf("%s\n", test);
	close(fd);
}*/
