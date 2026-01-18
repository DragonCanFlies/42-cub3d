#include "cub3d.h"


static float	get_frame_time(void)
{
	static struct timeval	last_time;
	static int				first = 1;
	struct timeval			current_time;
	float					delta;

	gettimeofday(&current_time, NULL);
	if (first)
	{
		last_time = current_time;
		first = 0;
		return (0.0f);
	}
	delta = (current_time.tv_sec - last_time.tv_sec)
		+ (current_time.tv_usec - last_time.tv_usec) / 1000000.0f;
	last_time = current_time;
	return (delta);
}

static int	should_animate(float *frame_time)
{
	*frame_time += get_frame_time();
	if (*frame_time >= ANIM_SPEED)
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

	(void)g;
	if (should_animate(&frame_time))
	{
		frame = (frame + 1) % 4;
		enemy->tex_id = TEX_GHOST1 + frame;
	}
}