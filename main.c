/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 12:49:55 by tsadouk           #+#    #+#             */
/*   Updated: 2023/11/22 12:49:55 by tsadouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// Lire jusqu a qu on trouve un retour a la ligne
// 


char	*get_next_line(int fd)
{
	static char	*stash = NULL;
	char		*line;
	char		*temp;
	char		buff[BUFFER_SIZE + 1];
	int			bytes_read;

	if (!stash)
	{
		stash = ft_strdup("");
		if (!stash)
			return (NULL);
	}
	while ((bytes_read = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[bytes_read] = '\0';
		temp = ft_strjoin(stash, buff);
		free(stash);
		stash = temp;
		if (ft_strchr(stash, '\n') || bytes_read == 0)
			break ;
	}
	if (bytes_read < 0)
	{
		free(stash);
		return (NULL);
	}
	line = ft_strdup(stash);
	if (bytes_read == 0)
		temp = ft_strdup(stash + ft_strlen(line));
	else if (bytes_read == 1)
		temp = ft_strdup(stash + ft_strlen(line) + 1);
	free(stash);
	stash = temp;
	return (line);
}