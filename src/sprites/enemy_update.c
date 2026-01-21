#include "cub3d.h"

void	update_sprites(t_game *g)
{
	update_enemies(g);
	check_collectibles(g);
}

static int	is_enemy(t_sprite *s)
{
	return (s->type == TYPE_ENEMY && s->alive);
}

void	update_enemies(t_game *g)
{
	int	i;

	i = 0;
	while (i < g->sprite_count)
	{
		if (is_enemy(&g->sprites[i]))
		{
			move_enemy(g, &g->sprites[i]);
			animate_enemy(g, &g->sprites[i]);
		}
		i++;
	}
}
void	update_delta_time(t_game *g)
{
	static struct timeval	last_tv;
	static int				first_call = 1;
	struct timeval			current_tv;
	float					delta_sec;
	float					delta_usec;

	gettimeofday(&current_tv, NULL);

	// First call - just initialize
	if (first_call)
	{
		last_tv = current_tv;
		first_call = 0;
		g->delta_time = 0.0f;
		printf("  → First call initialized\n");
		return;
	}
	
	
	// Calculate delta components
	delta_sec = (float)(current_tv.tv_sec - last_tv.tv_sec);
	delta_usec = (float)(current_tv.tv_usec - last_tv.tv_usec) / 1000000.0f;
	
	g->delta_time = delta_sec + delta_usec;
	
	// Sanity check
	if (g->delta_time > 1.0f)
		g->delta_time = 1.0f;
	if (g->delta_time < 0.0f)
		g->delta_time = 0.0f;
	
	// Save for next frame
	last_tv = current_tv;
}