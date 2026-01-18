#include "cub3d.h"

void	calc_spr_dist(t_game *g)
{
	int		i;
	float	dx;
	float	dy;

	i = 0;
	while (i < g->sprite_count)
	{
		if (g->sprites[i].alive)
		{
			dx = g->sprites[i].x - g->player.x;
			dy = g->sprites[i].y - g->player.y;
			g->sprites[i].dist = sqrtf(dx * dx + dy * dy);
		}
		i++;
	}
}

static void	swap_sprites(t_sprite *a, t_sprite *b)
{
	t_sprite	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	sort_sprites(t_game *g)
{
	int	i;
	int	j;

	i = 0;
	while (i < g->sprite_count - 1)
	{
		j = 0;
		while (j < g->sprite_count - i - 1)
		{
			if (g->sprites[j].dist < g->sprites[j + 1].dist)
				swap_sprites(&g->sprites[j], &g->sprites[j + 1]);
			j++;
		}
		i++;
	}
}