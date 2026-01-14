#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_game		g;

	// TODO clean exit with textures and memory leaks
	// parse the .cub file

	parse_input(argc, argv, &g);
	
	init_game(&g);
	setup_hooks(&g);
	mlx_loop(g.mlx);
	clean_map(&g.map);
	return (0);
}