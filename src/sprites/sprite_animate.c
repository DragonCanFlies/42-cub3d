#include "cub3d.h"

// Helper function that uses delta_time instead of get_frame_time()
static int	should_animate(float *frame_time, float speed, float delta_time)
{
	*frame_time += delta_time;
	if (*frame_time >= speed)
	{
		*frame_time = 0.0f;
		return (1);
	}
	return (0);
}

void	animate_enemy(t_game *g, t_sprite *enemy)
{
	static float	frame_time;
	static int		frame;

	if (should_animate(&frame_time, E_ANIM_SPEED, g->delta_time))
	{
		frame = (frame + 1) % 4;
		enemy->tex_id = TEX_GHOST1 + frame;
	}
}