/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sky <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 23:45:30 by sky               #+#    #+#             */
/*   Updated: 2020/07/19 01:57:07 by sky              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

#ifdef __cplusplus
extern "C"{
#endif

int		get_next_line(int fd, char **line);
char	*get_join(char *str, int len, char ***sneak, int **eol);
char	*compare_readed(int	*stat, char **sneak, char ***line);
char	*s_strdup(char *str);

#ifdef __cplusplus
}
#endif

#endif
