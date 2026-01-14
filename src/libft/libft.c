/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loasaad <loasaad@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:31:17 by latabagl          #+#    #+#             */
/*   Updated: 2026/01/14 20:01:02 by loasaad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*byte;

	byte = s;
	while (n > 0)
	{
		*byte++ = 0;
		n--;
	}
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}


int	ft_strncmp(const char *s1, const char *s2, unsigned int n)
{
	unsigned int	i;

	if (n == 0)
		return (0);
	i = 1;
	while (*s1 == *s2 && *s1 && *s2 && i < n)
	{
		s1++;
		s2++;
		i++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

// static void			*ft_memcpy(void *dest, const void *src, size_t n)
// {
// 	unsigned char		*dest_byte;
// 	const unsigned char	*src_byte;

// 	if (!dest || !src)
// 		return (dest);
// 	dest_byte = dest;
// 	src_byte = src;
// 	while (n > 0)
// 	{
// 		*dest_byte++ = *src_byte++;
// 		n--;
// 	}
// 	return (dest);
// }


