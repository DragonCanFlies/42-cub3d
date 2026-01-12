/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_colors_helpers.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latabagl <latabagl@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 17:21:30 by latabagl          #+#    #+#             */
/*   Updated: 2026/01/09 19:31:44 by latabagl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void	skip_space_or_tab(char *line, int *i)
{
	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
}

void	skip_token(char *line, int *i)
{
	while (line[*i] != ' ' && line[*i] != '\t' && line[*i] != '\n')
		(*i)++;
}

int	handle_config_flag(int *config_flag, int flag)
{
	if (*config_flag == 0)
	{
		*config_flag = 1;
		return (flag);
	}
	else
	{
		print_error(ID_DUPLICATA);
		return (-1);
	}
}

// which identifier is it: NO SO EA WE C F
int	get_config_flag(char *line, int i, int j, t_config_flags *config_flags)
{
	if (ft_strncmp(&line[j], "NO", i - j) == 0 && (i - j) == 2)
		return (handle_config_flag(&config_flags->has_no, NO));
	else if (ft_strncmp(&line[j], "SO", i - j) == 0 && (i - j) == 2)
		return (handle_config_flag(&config_flags->has_so, SO));
	else if (ft_strncmp(&line[j], "EA", i - j) == 0 && (i - j) == 2)
		return (handle_config_flag(&config_flags->has_ea, EA));
	else if (ft_strncmp(&line[j], "WE", i - j) == 0 && (i - j) == 2)
		return (handle_config_flag(&config_flags->has_we, WE));
	else if (ft_strncmp(&line[j], "F", i - j) == 0 && (i - j) == 1)
		return (handle_config_flag(&config_flags->has_f, F));
	else if (ft_strncmp(&line[j], "C", i - j) == 0 && (i - j) == 1)
		return (handle_config_flag(&config_flags->has_c, C));
	else
	{
		print_error(INVALID_ID);
		return (-1);
	}
}

// return 1 if all textures and floor/ceiling colors have been extracted
int	all_elements_except_map(t_config_flags *config_flags)
{
	return (config_flags->has_no
		&& config_flags->has_so
		&& config_flags->has_ea
		&& config_flags->has_we
		&& config_flags->has_f
		&& config_flags->has_c);
}
