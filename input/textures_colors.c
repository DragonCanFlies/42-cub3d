/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_colors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latabagl <latabagl@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 12:49:43 by latabagl          #+#    #+#             */
/*   Updated: 2026/01/09 20:05:28 by latabagl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

static void	save_in_config(char *str, char *line, t_config *config, int fd)
{
	if (config->flag == NO)
		config->north_path = str;
	else if (config->flag == SO)
		config->south_path = str;
	else if (config->flag == EA)
		config->east_path = str;
	else if (config->flag == WE)
		config->west_path = str;
	else if (config->flag == F)
	{
		if (handle_rgb(config->floor, str) == -1)
			clean_exit(COLOR, config, line, fd);
	}
	else if (config->flag == C)
	{
		if (handle_rgb(config->ceiling, str) == -1)
			clean_exit(COLOR, config, line, fd);
	}
}

// return -1 is line is empty, index if key is read
static int	read_config_key(char *line, t_config *config,
	t_config_flags *config_flags, int fd)
{
	int	i;
	int	j;

	i = 0;
	skip_space_or_tab(line, &i);
	if (!line[i] || line[i] == '\n')
		return (-1);
	j = i;
	skip_token(line, &i);
	config->flag = get_config_flag(line, i, j, config_flags);
	if (config->flag == -1)
		clean_exit_no_msg(config, line, fd);
	skip_space_or_tab(line, &i);
	if (!line[i] || line[i] == '\n')
		clean_exit(NO_INFO, config, line, fd);
	return (i);
}

static void	read_config_value(char *line, t_config *config,
	int i, int fd)
{
	int		k;
	char	*str;

	k = i;
	skip_token(line, &i);
	str = ft_substr(line, k, i - k);
	if (!str)
		clean_exit(MALLOC, config, line, fd);
	save_in_config(str, line, config, fd);
	skip_space_or_tab(line, &i);
	if (line[i] && line[i] != '\n')
		clean_exit(EXTRA_INFO, config, line, fd);
}

static void	parse_line(char *line, t_config *config,
	t_config_flags *config_flags, int fd)
{
	int		i;

	i = read_config_key(line, config, config_flags, fd);
	if (i == -1)
		return ;
	read_config_value(line, config, i, fd);
}

char	*extract_walls_floor_ceiling(t_config *config,
	t_config_flags *config_flags, int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line && !all_elements_except_map(config_flags))
	{
		parse_line(line, config, config_flags, fd);
		free(line);
		line = get_next_line(fd);
	}
	if (!all_elements_except_map(config_flags))
		clean_exit(INCOMPLETE_FILE, config, line, fd);
	return (line);
}
