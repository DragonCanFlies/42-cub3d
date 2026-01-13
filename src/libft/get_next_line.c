/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loasaad <loasaad@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:24:50 by loasaad           #+#    #+#             */
/*   Updated: 2025/05/28 19:02:37 by loasaad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup(const char *src)
{
	char	*copy;
	int		strlen;
	int		i;

	strlen = ft_strlen(src);
	copy = ((char *) malloc(sizeof(char) * (strlen + 1)));
	if (!copy)
		return (NULL);
	i = 0;
	while (src[i])
	{
		copy[i] = src[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

char	*ft_line_maker(char **leftover)
{
	char	*line;
	char	*temp;
	char	*ptr_newline;
	int		len_line;

	ptr_newline = ft_strchr(*leftover, '\n');
	if (ptr_newline)
	{
		ptr_newline++;
		len_line = ptr_newline - *leftover;
		line = ft_substr(*leftover, 0, len_line);
		temp = ft_strdup(ptr_newline);
		free (*leftover);
		*leftover = temp;
		return (line);
	}
	line = ft_strdup(*leftover);
	ft_free_null(leftover);
	return (line);
}

int	ft_read_loop(char **leftover, char *buffer, int fd)
{
	int		bytes_read;
	char	*temp;

	while (!ft_strchr(*leftover, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
			return (bytes_read);
		buffer[bytes_read] = '\0';
		temp = ft_strjoin(*leftover, buffer);
		if (!temp)
		{
			ft_free_null(leftover);
			return (-1);
		}
		free(*leftover);
		*leftover = temp;
	}
	return (1);
}

void	ft_free_null(char **ptr)
{
	if (ptr && *ptr)
	{
		free (*ptr);
		*ptr = NULL;
	}
}

char	*get_next_line(int fd)
{
	static char	*leftover;
	char		*buffer;
	int			bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	if (!leftover)
		leftover = ft_strdup("");
	bytes_read = ft_read_loop(&leftover, buffer, fd);
	free (buffer);
	if (bytes_read == -1 || !leftover || leftover[0] == '\0')
	{
		ft_free_null(&leftover);
		return (NULL);
	}
	return (ft_line_maker(&leftover));
}
