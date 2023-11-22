/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 10:36:51 by tsadouk           #+#    #+#             */
/*   Updated: 2023/11/20 11:31:57 by tsadouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
// lire jusquw \n = read_until_null
// stocker dans static
// char temp = debut - first \n
// fonction qui modifie la static = la static sans la pemiere ligne 
// strjoin entre static et la premiere ligne

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*ptr1;
	char	*ptr2;
	size_t	i;

	i = 0;
	if (dst && src)
	{
		ptr1 = (char *)dst;
		ptr2 = (char *)src;
		while (i < n)
		{
			ptr1[i] = ptr2[i];
			i++;
		}
	}
	return (dst);
}

char	*ft_realloc(char *ptr, size_t old_size, size_t new_size)
{
	char	*new_ptr;
	size_t	min_size;

	new_ptr = (char *)malloc(new_size);
	if (!new_ptr)
	{
		free(ptr);
		return (NULL);
	}
	if (old_size < new_size)
		min_size = old_size;
	else
		min_size = new_size;
	ft_memcpy(new_ptr, ptr, min_size);
	free(ptr);
	return (new_ptr);
}


char	*read_until_null(int fd)
{
	size_t	buffer_size;
	size_t	new_size;
	size_t	index;
	char	*buffer;
	char	*temp;
	char 	*result;
	char	c;

	buffer_size = 64;
	buffer = (char *)malloc(buffer_size);
	if (!buffer)
		return (NULL);
	index = 0;
	while (read(fd, &c, 1) > 0)
	{
		if (index == buffer_size)
		{
			new_size = buffer_size * 2;
			temp = (char *)ft_realloc(buffer, buffer_size, new_size);
			if (!temp)
			{
				free(buffer);
				return (NULL);
			}
			buffer = temp;
		}
		buffer[index++] = c;
		if (c == '\0')
			break ;
	}
	result = ft_realloc(buffer, buffer_size, index);
	if (!result)
		return (NULL);
	return (result);
}


char	*get_next_line(int fd)
{
	static char	*static_buffer = NULL;
	char		*line;
	char		*temp;

	if (!static_buffer)
		static_buffer = read_until_null(fd);

	if (!static_buffer)
		return (NULL);

	// Trouver la taille de la première ligne
	size_t line_size = 0;
	while (static_buffer[line_size] && static_buffer[line_size] != '\n')
		line_size++;

	// Allouer de la mémoire pour la ligne
	line = (char *)malloc(line_size + 1);
	if (!line)
		return (NULL);

	// Copier la première ligne dans la variable 'line'
	ft_memcpy(line, static_buffer, line_size);
	line[line_size] = '\0';

	// Mettre à jour la variable statique (supprimer la première ligne)
	temp = ft_realloc(static_buffer, ft_strlen(line) + 1, ft_strlen(static_buffer));
	if (!temp)
	{
		free(line);
		return (NULL);
	}
	static_buffer = temp;

	return (line);
}
