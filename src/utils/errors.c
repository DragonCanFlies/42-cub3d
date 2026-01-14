/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loasaad <loasaad@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 13:58:00 by latabagl          #+#    #+#             */
/*   Updated: 2026/01/14 15:28:00 by loasaad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_error(char *msg)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(msg, 2);
}

void	handle_error(char *msg)
{
	print_error(msg);
	exit(1);
}

void	clean_exit(char *msg, t_map *map, char *line, int fd)
{
	print_error(msg);
	clean_map(map);
	if (line)
		free(line);
	if (fd != -1)
		close(fd);
	exit(1);
}

void	clean_exit_no_msg(t_map *map, char *line, int fd)
{
	clean_map(map);
	if (line)
		free(line);
	if (fd != -1)
		close(fd);
	exit(1);
}

void	perror_exit(const char *message)
{
	printf("%s\n", message);
	exit(EXIT_FAILURE);
}
