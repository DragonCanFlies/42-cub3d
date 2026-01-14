#include "cub3d.h"

void	setup_hooks(t_game *g)
{
	mlx_hook(g->win, 2, 1L << 0, key_press, g);     // Key down
	mlx_hook(g->win, 3, 1L << 1, key_release, g);   // Key up
	mlx_hook(g->win, 17, 0, close_window, g);       // Window close
	mlx_loop_hook(g->mlx, render, g);                // Render loop
}
