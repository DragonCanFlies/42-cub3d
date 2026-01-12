/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latabagl <latabagl@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 15:58:52 by latabagl          #+#    #+#             */
/*   Updated: 2026/01/09 16:04:08 by latabagl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

static void	get_player_data_helper(t_config *config, int row, int col)
{
	config->player_x = col;
	config->player_y = row;
	if (config->map[row][col] == 'N')
		config->player_angle = 90.0;
	else if (config->map[row][col] == 'S')
		config->player_angle = 270.0;
	else if (config->map[row][col] == 'W')
		config->player_angle = 180.0;
	else
		config->player_angle = 0.0;
	config->map[row][col] = '0';
}

void	get_player_data(t_config *config)
{
	int	row;
	int	col;

	row = 0;
	while (config->map[row])
	{
		col = 0;
		while (config->map[row][col])
		{
			if (config->map[row][col] == 'N'
		|| config->map[row][col] == 'S'
		|| config->map[row][col] == 'E'
		|| config->map[row][col] == 'W')
			{
				get_player_data_helper(config, row, col);
				return ;
			}
			col++;
		}
		row++;
	}
	return ;
}
