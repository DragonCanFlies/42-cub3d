/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loasaad <loasaad@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 13:58:00 by latabagl          #+#    #+#             */
/*   Updated: 2026/01/13 16:29:20 by loasaad          ###   ########.fr       */
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

void	clean_exit(char *msg, t_map *config, char *line, int fd)
{
	print_error(msg);
	clean_config(config);
	if (line)
		free(line);
	if (fd != -1)
		close(fd);
	exit(1);
}

void	clean_exit_no_msg(t_map *config, char *line, int fd)
{
	clean_config(config);
	if (line)
		free(line);
	if (fd != -1)
		close(fd);
	exit(1);
}
