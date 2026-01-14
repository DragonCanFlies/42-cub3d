/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loasaad <loasaad@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 19:46:01 by latabagl          #+#    #+#             */
/*   Updated: 2026/01/13 15:35:29 by loasaad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	extract_color(char *str, int *i)
{
	int	digits;
	int	color;

	color = 0;
	digits = 0;
	if (!str[*i] || !(str[*i] >= '0' && str[*i] <= '9'))
		return (-1);
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		digits++;
		if (digits > 3)
			return (-1);
		color = color * 10 + str[*i] - 48;
		(*i)++;
	}
	if (color > 255)
		return (-1);
	return (color);
}

int	handle_rgb(uint8_t	colors[3], char *str)
{
	int	i;
	int	j;
	int	tmp_colors[3];

	i = 0;
	j = 0;
	while (j < 3)
	{
		tmp_colors[j] = extract_color(str, &i);
		if (tmp_colors[j] == -1)
			return (free(str), -1);
		if (j++ < 2)
		{
			if (str[i] != ',')
				return (free(str), -1);
			i++;
		}
	}
	if (str[i])
		return (free(str), -1);
	free(str);
	colors[0] = tmp_colors[0];
	colors[1] = tmp_colors[1];
	colors[2] = tmp_colors[2];
	return (1);
}
