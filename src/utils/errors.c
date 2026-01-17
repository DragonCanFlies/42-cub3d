/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latabagl <latabagl@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 13:58:00 by latabagl          #+#    #+#             */
/*   Updated: 2026/01/17 19:05:15 by latabagl         ###   ########.fr       */
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
	get_next_line(-1);
	clean_map(map);
	if (line)
		free(line);
	if (fd != -1)
		close(fd);
	exit(1);
}

void	clean_exit_no_msg(t_map *map, char *line, int fd)
{
	get_next_line(-1);
	clean_map(map);
	if (line)
		free(line);
	if (fd != -1)
		close(fd);
	exit(1);
}
