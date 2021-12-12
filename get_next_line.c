/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sky <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 23:44:38 by sky               #+#    #+#             */
/*   Updated: 2020/08/29 04:58:26 by sky              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 320
#endif

int		set_static(int end, char ****sneak, char *str)
{
	int		len;

	len = 0;
	if (str[end + 1])
	{
		end++;
		while (str[end + len])
			len++;
		if (!(***sneak = (char *)malloc(sizeof(char) * len + 1)))
			return (0);
		(***sneak)[len] = '\0';
		while (len--)
			(***sneak)[len] = str[end + len];
	}
	else
		***sneak = NULL;
	return (1);
}

char	*get_join(char *str, int len, char ***sneak, int **eol)
{
	char	*join;
	int		start;
	int		end;

	start = 0;
	while (start < len)
	{
		if (str[start] == '\n')
		{
			**eol = 1;
			end = start;
			if (!(join = (char *)malloc(sizeof(char) * start + 1)))
				return (NULL);
			join[start] = '\0';
			while (start--)
				join[start] = str[start];
			if (!set_static(end, &sneak, str))
				return (NULL);
			return (join);
		}
		start++;
	}
	if (!(join = s_strdup(str)))
		return (NULL);
	return (join);
}

char	*break_str(int fd, char **sneak, int *stat, int *eol)
{
	char	*str;
	char	*join;
	int		len;

	if (!(str = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1)))
		return (NULL);
	len = read(fd, str, BUFFER_SIZE);
	if (len < 0)
	{
		*stat = -1;
		free(str);
		return (NULL);
	}
	str[len] = '\0';
	if (!(join = get_join(str, len, &sneak, &eol)))
		return (NULL);
	if (len != BUFFER_SIZE && join && !*eol)
		*stat = 1;
	free(str);
	return (join);
}

int		get_next_line(int fd, char **line)
{
	int			stat;
	int			eol;
	char		*join;
	static char *sneak;

	stat = 0;
	eol = 0;
	*line = NULL;
	if (!line || BUFFER_SIZE < 1)
		return (-1);
	while (!stat)
	{
		*line = compare_readed(&eol, &sneak, &line);
		if (stat == -1 || eol == 1)
			return (stat == -1 ? -1 : 1);
		join = break_str(fd, &sneak, &stat, &eol);
		if (stat == -1 || !join)
			return (-1);
		*line = compare_readed(&stat, &join, &line);
		if (stat == 1 || stat == -1)
			return (stat == 1 ? 0 : -1);
		if (eol)
			return (1);
	}
	return (1);
}
