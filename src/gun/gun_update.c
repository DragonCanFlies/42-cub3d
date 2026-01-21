#include "cub3d.h"

void    update_gun(t_game *g)
{
    if (g->damage_cooldown > 0.0f)
        g->damage_cooldown -= g->delta_time;
    
    if (!g->gun.active)
        return;
    
    // Update timer
    g->gun.timer -= g->delta_time;
    if (g->gun.timer <= 0.0f)
    {
        g->gun.active = 0;
        g->gun.ammo = 0;
        g->gun.state = GUN_IDLE;
        ft_putstr_fd("Weapon expired!\n", 1);
        return;
    }
    
    // If out of ammo
    if (g->gun.ammo <= 0)
    {
        if (g->gun.state == GUN_FIRING || g->gun.state == GUN_FIRE_START)
        {
            g->gun.state = GUN_FIRE_END;
            g->gun.anim_timer = 0.0f;
        }
        animate_gun(&g->gun);
        return;
    }
    
    // Update fire cooldown
    if (g->gun.fire_cooldown > 0.0f)
        g->gun.fire_cooldown -= g->delta_time;
    
    // Auto-fire if space is held and cooldown expired
    if (g->keys.space && g->gun.fire_cooldown <= 0.0f)
    {
        player_shoot(g);
    }
    
    // If not shooting and not in middle of animation, transition to end
    if (!g->keys.space && g->gun.fire_cooldown <= 0.0f)
    {
        if (g->gun.state == GUN_FIRING)
        {
            g->gun.state = GUN_FIRE_END;
            g->gun.anim_timer = 0.0f;
        }
    }
    
    // Update animation timer
    g->gun.anim_timer += g->delta_time;
    
    // Animate
    animate_gun(&g->gun);
}