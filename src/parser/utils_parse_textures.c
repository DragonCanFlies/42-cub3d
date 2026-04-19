/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse_textures.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latabagl <latabagl@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 14:32:07 by latabagl          #+#    #+#             */
/*   Updated: 2026/03/22 14:55:22 by latabagl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Skip whitespace characters (spaces and tabs)
void	skip_space_or_tab(char *line, int *i)
{
	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
}

// Skip non-whitespace characters (advance to next space/tab/newline)
void	skip_token(char *line, int *i)
{
	while (line[*i] && line[*i] != ' ' && line[*i] != '\t' && line[*i] != '\n')
		(*i)++;
}

// Mark an element as found and check for duplicates
// Returns the element ID on success, -1 on duplicate
int	handle_map_flag(int *map_flag, int flag)
{
	if (*map_flag == 0)
	{
		*map_flag = 1;
		return (flag);
	}
	else
	{
		print_error(ID_DUPLICATA);
		return (-1);
	}
}

// Identify which element type this line represents (NO, SO, EA, WE, C, F)
// Compares the token against valid identifiers and checks for duplicates
int	get_map_flag(char *line, int i, int j, t_map_flags *flags)
{
	if (ft_strncmp(&line[j], "NO", i - j) == 0 && (i - j) == 2)
		return (handle_map_flag(&flags->has_no, NO));
	else if (ft_strncmp(&line[j], "SO", i - j) == 0 && (i - j) == 2)
		return (handle_map_flag(&flags->has_so, SO));
	else if (ft_strncmp(&line[j], "EA", i - j) == 0 && (i - j) == 2)
		return (handle_map_flag(&flags->has_ea, EA));
	else if (ft_strncmp(&line[j], "WE", i - j) == 0 && (i - j) == 2)
		return (handle_map_flag(&flags->has_we, WE));
	else if (ft_strncmp(&line[j], "F", i - j) == 0 && (i - j) == 1)
		return (handle_map_flag(&flags->has_f, F));
	else if (ft_strncmp(&line[j], "C", i - j) == 0 && (i - j) == 1)
		return (handle_map_flag(&flags->has_c, C));
	else
	{
		print_error(INVALID_ID);
		return (-1);
	}
}

/*
** Checks if all required elements have been found
** Returns 1 if complete (all 6 elements: NO, SO, EA, WE, F, C), 0 otherwise
*/
int	textures_are_extracted(t_map_flags *flags)
{
	return (flags->has_no
		&& flags->has_so
		&& flags->has_ea
		&& flags->has_we
		&& flags->has_f
		&& flags->has_c);
}
