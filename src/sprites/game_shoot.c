#include "cub3d.h"

static float	calc_dist(float x1, float y1, float x2, float y2)
{
	float	dx;
	float	dy;

	dx = x2 - x1;
	dy = y2 - y1;
	return (sqrtf(dx * dx + dy * dy));
}

static float	calc_aim_dot(t_game *g, t_sprite *s, float dist)
{
	float	to_x;
	float	to_y;

	to_x = (s->x - g->player.x) / dist;
	to_y = (s->y - g->player.y) / dist;
	return (g->player.dx * to_x + g->player.dy * to_y);
}

static t_sprite *find_target(t_game *g)
{
    int         i;
    float       dist;
    float       dot;
    t_sprite    *closest;
    float       min_dist;

    i = 0;
    closest = NULL;
    min_dist = 999999.0f;
    while (i < g->sprite_count)
    {
        if (g->sprites[i].type == TYPE_ENEMY && g->sprites[i].alive)
        {
            dist = calc_dist(g->player.x, g->player.y,
                    g->sprites[i].x, g->sprites[i].y);
            dot = calc_aim_dot(g, &g->sprites[i], dist);
            if (dot > 0.9f && dist < min_dist)
            {
                min_dist = dist;
                closest = &g->sprites[i];
            }
        }
        i++;
    }
    return (closest);
}
void    player_shoot(t_game *g)
{
    t_sprite    *target;

    if (!g->gun.active)
        return;
    
    // Check cooldown (shouldn't happen since gun_update checks, but just in case)
    if (g->gun.fire_cooldown > 0.0f)
        return;
    
    // Check ammo
    if (g->gun.ammo <= 0)
        return;
    
    // Fire the shot
    g->gun.ammo--;
    g->gun.fire_cooldown = FIRE_RATE;
    
    // Start firing animation if not already
    if (g->gun.state == GUN_IDLE || g->gun.state == GUN_FIRE_END)
    {
        g->gun.state = GUN_FIRE_START;
        g->gun.anim_timer = 0.0f;
    }
    // If already in FIRE_START or FIRING, just stay there
    
    // Find and hit target
    target = find_target(g);
    if (target)
    {
        target->health--;
        if (target->health <= 0)
        {
            target->alive = 0;
            ft_putstr_fd("Enemy killed!\n", 1);
        }
    }
}