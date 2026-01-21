#include "cub3d.h"

static float	calc_distance(float x1, float y1, float x2, float y2)
{
	float	dx;
	float	dy;

	dx = x2 - x1;
	dy = y2 - y1;
	return (sqrtf(dx * dx + dy * dy));
}

static void	normalize_direction(float *dx, float *dy, float dist)
{
	if (dist > 0.1f)
	{
		*dx /= dist;
		*dy /= dist;
	}
}

static int	can_move_enemy(t_game *g, float x, float y)
{
	int	mx;
	int	my;
	int	mp;

	mx = (int)x >> 6;
	my = (int)y >> 6;
	mp = my * g->map.x + mx;
	if (mp < 0 || mp >= g->map.x * g->map.y)
		return (0);
	return (g->map.map_data[mp] == 0);
}

static void	apply_movement(t_game *g, t_sprite *e, float dx, float dy)
{
	float	new_x;
	float	new_y;

	new_x = e->x + dx * ENEMY_SPEED;
	new_y = e->y + dy * ENEMY_SPEED;
	if (can_move_enemy(g, new_x, e->y))
		e->x = new_x;
	if (can_move_enemy(g, e->x, new_y))
		e->y = new_y;
}

void    move_enemy(t_game *g, t_sprite *e)
{
    float   dx;
    float   dy;
    float   dist;

    dx = g->player.x - e->x;
    dy = g->player.y - e->y;
    dist = calc_distance(e->x, e->y, g->player.x, g->player.y);
    
    if (dist < 32.0f)
    {
        if (g->damage_cooldown <= 0.0f)  // OK to take damage
        {
            g->health -= ENEMY_DAMAGE;
            g->damage_cooldown = DAMAGE_COOLDOWN;
            
            printf("HP: %d/%d\n", g->health, g->max_health);  // DEBUG
            
            if (g->health <= 0)
            {
                g->health = 0;
                ft_putstr_fd("Game Over! You died!\n", 1);
                close_window(g);
            }
            else
            {
                ft_putstr_fd("Hit by enemy! -20 HP\n", 1);
            }
        }
    }
    
    normalize_direction(&dx, &dy, dist);
    apply_movement(g, e, dx, dy);
}