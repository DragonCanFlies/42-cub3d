#include "cub3d.h"

// return 1 if filename ends with .cub
static void	check_filename(char	*filename)
{
	size_t	len;

	len = ft_strlen(filename);
	if (len < 4)
		handle_error(INVALID_FILENAME);
	if (!(filename[len - 4] == '.'
			&& filename[len - 3] == 'c'
			&& filename[len - 2] == 'u'
			&& filename[len - 1] == 'b'))
		handle_error(INVALID_FILENAME);
}

static int	open_file(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		handle_error(OPEN_MAP);
	return (fd);
}

static int	create_int_map_array(t_map *map)
{
	int	row;
	int	col;

	map->map_data = malloc(map->x * map->y * sizeof(int));
	if (!map->map_data)
		return (0);
	row = 0;
	while (row < map->y)
	{
		col = 0;
		while (col < map->x)
		{
			if (map->raw_map[row][col] == '1' || map->raw_map[row][col] == 'D')
				map->map_data[row * map->x + col] = 1;
			else
				map->map_data[row * map->x + col] = 0;
			col++;
		}
		row++;
	}
	return (1);
}

/* Inside main :
	t_map	config;

	parse_config(argc, argv, &config);
	clean_config(&config);*/
void	parse_input(int argc, char **argv, t_game *g)
{
	int				fd;
	t_map_flags		map_flags;
	char			*line;

	ft_bzero(&g->map, sizeof(t_map));
	ft_bzero(&map_flags, sizeof(map_flags));
	if (argc != 2)
		handle_error(ARG_NB_ERR);
	check_filename(argv[1]);
	fd = open_file(argv[1]);
	line = parse_textures(&g->map, &map_flags, fd);
	parse_map(&g->map, fd, line);
	normalize_map(&g->map);
	parse_player_data(g);
	parse_doors(g);
	parse_tp(g);
	ensure_closed_map(g);
	if (!create_int_map_array(&g->map))
		clean_exit(MALLOC, &g->map, line, fd);
}
