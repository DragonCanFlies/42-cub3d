#include "cub3d.h"

void	init_game(t_game *g)
{
	g->mlx = mlx_init();
	if (!g->mlx)		//change the func
		perror_exit ("MLX init failed");
	g->win = mlx_new_window(g->mlx, WIN_WIDTH, WIN_HEIGHT, "Raycaster MLX");
	if (!g->win)		//change the func
		perror_exit ("Window creation failed");;
	g->img.img = mlx_new_image(g->mlx, WIN_WIDTH, WIN_HEIGHT);
	g->img.buffer = mlx_get_data_addr(g->img.img, &g->img.bpp,
		&g->img.line_len, &g->img.endian);
	g->px_per_ray = (WIN_WIDTH * RAY_ACC) / FOV;
	if (fmod((WIN_WIDTH * RAY_ACC), FOV) != 0)
		write(2, ERR_PPR, 75);
	ft_bzero(&g->keys, sizeof(g->keys));
	init_texture(g);
}
