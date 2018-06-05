/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tavelino <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 15:00:10 by tavelino          #+#    #+#             */
/*   Updated: 2018/06/06 01:37:15 by tavelino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		checkerror(int fd, char **str, char **line)
{
	if (fd < 0 || line == NULL)
		return (-1);
	if (!*str)
	{
		if (!(*str = (char*)malloc(sizeof(char) * (BUFF_SIZE + 1))))
			return (-1);
	}
	return (0);
}

#include <stdio.h>

int		readline(char **line, int fd)
{
	static char	*rest;
	int			b_read;
	char		*position;

	//TODO: Protect strnew
	if (!rest)
		rest = ft_strnew(BUFF_SIZE);
	else if ((position = ft_strchr(rest, '\n')))
	{
		*position = '\0';
		*line = ft_strjoin(*line, rest);
		rest = ft_strdup(position + 1);
		return (1);
	}
	/* tentei arrumar esse while mas ta meio bosta*/
	*line = ft_strjoin(*line, rest);
//	printf("rest: %s\n", rest);
	while ((b_read = read(fd, rest, BUFF_SIZE)) > 0 && !(position = ft_strchr(rest, '\n')))
	{
		*line = ft_strjoin(*line, rest);
		printf("read line: %s\n", *line);
	}
	if (b_read > 0)
	{
		*position = '\0';
		*line = ft_strjoin(*line, rest);
		rest = ft_strdup(position + 1);
		return (1);
	}
	free(rest);
	return (b_read);
}

int		get_next_line(int const fd, char **line)
{
//	static char	*str;
	int			i;

//	if (checkerror(fd, &str, line) == -1)
//		return (-1);
//	if (*str)
//		ft_strcpy(*line, str);
	// se nao da esse espaco pro line nao da nada de resultado.. estranho pq ?
	*line = ft_memalloc(1);
	i = readline(line, fd);
/*	if (str[i])
	{
		while (str[i] != '\n' && str[i])
			i++
		if (i == 0)
			(*line) = ft_strdup("");
		else
		{
			(*line) = ft_strsub(str, 0, i);
			str = &str[i + 1];
		}
		return (1);
	}
	else
		(*line) = ft_strdup("");*/
	return (i);
}