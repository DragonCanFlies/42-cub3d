#include "cub3d.h"

/*
** Optimization constants:
** - INV_RAY_ACC: Pre-computed 1/RAY_ACC to avoid division
** - RAD_TO_DEG: Pre-computed 180/π for radian-to-degree conversion
** - DEG_TO_RAD_FACTOR: Pre-computed π/180 for degree-to-radian conversion
*/

#define MIN_SPRITE_DIST 10.0f
#define MAX_SPRITE_SIZE (WIN_HEIGHT << 1)
#define INV_RAY_ACC (1.0f / RAY_ACC)
#define RAD_TO_DEG (180.0f / M_PI)
#define HALF_FOV (FOV * 0.5f)

/*
** atan2f: Expensive trigonometric function (~50-100 CPU cycles)
** Returns angle in radians, we convert to degrees for consistency
** with the rest of the codebase which uses degrees
*/
static float	calc_sprite_angle(float rel_x, float rel_y, float p_angle)
{
	float	angle_to_spr;
	float	angle_diff;

	angle_to_spr = atan2f(-rel_y, rel_x) * RAD_TO_DEG;
	angle_diff = angle_to_spr - p_angle;
	while (angle_diff > 180.0f)
		angle_diff -= 360.0f;
	while (angle_diff < -180.0f)
		angle_diff += 360.0f;
	return (angle_diff);
}

static float	calc_perp_dist(float dist, float angle_from_center)
{
	float	perp_dist;

	perp_dist = dist * cosf(deg_to_rad(angle_from_center));
	if (perp_dist > 0 && perp_dist < MIN_SPRITE_DIST)
		perp_dist = MIN_SPRITE_DIST;
	return (perp_dist);
}

static void	calc_transform(t_game *g, t_sprite *s, t_spr_draw *d)
{
	float	rel_x;
	float	rel_y;
	float	dist;
	float	angle_diff;
	float	ray_offset;

	rel_x = s->x - g->player.x;
	rel_y = s->y - g->player.y;
	dist = sqrtf(rel_x * rel_x + rel_y * rel_y);
	angle_diff = calc_sprite_angle(rel_x, rel_y, g->player.angle);
	ray_offset = HALF_FOV - angle_diff;
	d->trans_x = ray_offset * INV_RAY_ACC;
	d->trans_y = calc_perp_dist(dist, angle_diff);
}

static void	calc_screen_pos(t_game *g, t_spr_draw *d)
{
	int	size;

	d->scr_x = (int)(d->trans_x * g->px_per_ray);
	size = abs((int)(MAP_S * WIN_HEIGHT / d->trans_y));
	if (size > MAX_SPRITE_SIZE)
		size = MAX_SPRITE_SIZE;
	d->height = size;
	d->width = size;
}

void	calc_bounds(t_spr_draw *d, t_spr_bounds *b)
{
	b->start_y = -(d->height >> 1) + (WIN_HEIGHT >> 1);
	b->end_y = (d->height >> 1) + (WIN_HEIGHT >> 1);
	b->start_x = -(d->width >> 1) + d->scr_x;
	b->end_x = (d->width >> 1) + d->scr_x;
	if (b->start_y < 0)
		b->start_y = 0;
	if (b->end_y >= WIN_HEIGHT)
		b->end_y = WIN_HEIGHT - 1;
	if (b->start_x < 0)
		b->start_x = 0;
	if (b->end_x >= WIN_WIDTH)
		b->end_x = WIN_WIDTH - 1;
}

void	transform_sprite(t_game *g, t_sprite *s, t_spr_draw *d)
{
	calc_transform(g, s, d);
	calc_screen_pos(g, d);
}
// #include "cub3d.h"

// static float	calc_plane_x(t_player *p)
// {
// 	return (-p->dy * FOV_SCALE);
// }

// static float	calc_plane_y(t_player *p)
// {
// 	return (p->dx * FOV_SCALE);
// }

// static void	calc_transform(t_game *g, t_sprite *s, t_spr_draw *d)
// {
// 	float	inv_det;
// 	float	rel_x;
// 	float	rel_y;
// 	float	plane_x;
// 	float	plane_y;

// 	rel_x = s->x - g->player.x;
// 	rel_y = s->y - g->player.y;
// 	plane_x = calc_plane_x(&g->player);
// 	plane_y = calc_plane_y(&g->player);
// 	inv_det = 1.0f / (plane_x * g->player.dy - g->player.dx * plane_y);
// 	d->trans_x = inv_det * (g->player.dy * rel_x - g->player.dx * rel_y);
// 	d->trans_y = inv_det * (-plane_y * rel_x + plane_x * rel_y);
// }

// static void calc_screen_pos(t_spr_draw *d)
// {
//     d->scr_x = (int)((WIN_WIDTH / 2) * (1 + d->trans_x / d->trans_y));
//     d->height = abs((int)(MAP_S * WIN_HEIGHT / d->trans_y));  // ADD MAP_S
//     d->width = abs((int)(MAP_S * WIN_HEIGHT / d->trans_y));   // ADD MAP_S
// }

// void	calc_bounds(t_spr_draw *d, t_spr_bounds *b)
// {
// 	b->start_y = -d->height / 2 + WIN_HEIGHT / 2;
// 	b->end_y = d->height / 2 + WIN_HEIGHT / 2;
// 	b->start_x = -d->width / 2 + d->scr_x;
// 	b->end_x = d->width / 2 + d->scr_x;
// 	if (b->start_y < 0)
// 		b->start_y = 0;
// 	if (b->end_y >= WIN_HEIGHT)
// 		b->end_y = WIN_HEIGHT - 1;
// 	if (b->start_x < 0)
// 		b->start_x = 0;
// 	if (b->end_x >= WIN_WIDTH)
// 		b->end_x = WIN_WIDTH - 1;
// }

// void	transform_sprite(t_game *g, t_sprite *s, t_spr_draw *d)
// {
// 	calc_transform(g, s, d);
// 	calc_screen_pos(d);
// }