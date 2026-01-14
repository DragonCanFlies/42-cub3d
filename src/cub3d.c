#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_game		g;

	// TODO clean exit with textures and memory leaks
	// parse the .cub file
	ft_bzero(&g, sizeof(t_game));
	// printf("DEBUG: Starting parse_input...\n");
	parse_input(argc, argv, &g);
	// printf("DEBUG: Parse complete, starting init_game...\n");
	init_game(&g);
	// printf("DEBUG: Init complete, setting up hooks...\n");
	setup_hooks(&g);
	// printf("DEBUG: Starting MLX loop...\n");
	mlx_loop(g.mlx);
	clean_map(&g.map);
	return (0);
}