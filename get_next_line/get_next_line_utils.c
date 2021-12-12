/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sky <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 00:48:24 by sky               #+#    #+#             */
/*   Updated: 2020/07/19 01:39:35 by sky              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*error_return(int **stat)
{
	**stat = -1;
	return (NULL);
}

char	*s_strdup(char *str)
{
	int		i;
	char	*str2;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i])
		i++;
	if (!(str2 = (char *)malloc(sizeof(char) * i + 1)))
		return (NULL);
	str2[i] = '\0';
	while (i--)
		str2[i] = str[i];
	return (str2);
}

char	*free_sneak(char ***sneak, int *copy_len)
{
	int		len_sneak;
	char	*break_sneak;

	len_sneak = 0;
	while ((**sneak)[len_sneak])
		len_sneak++;
	*copy_len = len_sneak;
	if (!(break_sneak = (char *)malloc(sizeof(char) * len_sneak + 1)))
		return (NULL);
	break_sneak[len_sneak] = '\0';
	while (len_sneak--)
		break_sneak[len_sneak] = (**sneak)[len_sneak];
	free(**sneak);
	**sneak = NULL;
	return (break_sneak);
}

char	*get_readed(char ****line, int len_line, char **break_sneak)
{
	int		len_break;
	char	*readed;

	len_break = 0;
	while (*break_sneak && (*break_sneak)[len_break])
		len_break++;
	if (!(readed = (char *)malloc(sizeof(char) * (len_break + len_line) + 1)))
		return (NULL);
	readed[len_break + len_line] = '\0';
	while (*break_sneak && len_break--)
		readed[len_break + len_line] = (*break_sneak)[len_break];
	if (*break_sneak)
		free(*break_sneak);
	while (***line && len_line--)
		readed[len_line] = (***line)[len_line];
	if (***line)
		free(***line);
	return (readed);
}

char	*compare_readed(int *stat, char **sneak, char ***line)
{
	int		len_line;
	char	*break_sneak;
	char	*copy_sneak;
	int		copy_len;

	len_line = 0;
	copy_sneak = NULL;
	if (**line)
		while ((**line)[len_line])
			len_line++;
	if (*sneak)
	{
		if (!(break_sneak = free_sneak(&sneak, &copy_len)))
			return (NULL);
		if (!(copy_sneak = get_join(break_sneak, copy_len, &sneak, &stat)))
			return (NULL);
		free(break_sneak);
	}
	if (copy_sneak || **line)
	{
		if (!(break_sneak = get_readed(&line, len_line, &copy_sneak)))
			return (error_return(&stat));
		return (break_sneak);
	}
	return (NULL);
}
