/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latabagl <latabagl@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 19:22:17 by latabagl          #+#    #+#             */
/*   Updated: 2026/01/17 19:22:32 by latabagl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_game		g;

	ft_bzero(&g, sizeof(t_game));
	parse_input(argc, argv, &g);
	init_game(&g);
	setup_hooks(&g);
	mlx_loop(g.mlx);
	clean_exit_game(&g);
	return (0);
}
