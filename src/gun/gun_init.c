#include "cub3d.h"

void    init_gun(t_game *g)
{
    // Load 5 gun animation frames
    if (!load_texture("textures/gun1.xpm", &g->gun.frames[0], g))
        perror_exit("Gun1 texture failed");
    if (!load_texture("textures/gun2.xpm", &g->gun.frames[1], g))
        perror_exit("Gun2 texture failed");
    if (!load_texture("textures/gun3.xpm", &g->gun.frames[2], g))
        perror_exit("Gun3 texture failed");
    if (!load_texture("textures/gun4.xpm", &g->gun.frames[3], g))
        perror_exit("Gun4 texture failed");
    if (!load_texture("textures/gun5.xpm", &g->gun.frames[4], g))
        perror_exit("Gun5 texture failed");
    
    g->gun.current_frame = 0;
    g->gun.state = GUN_IDLE;  // Start in idle state
    g->gun.ammo = 0;
    g->gun.timer = 0.0f;
    g->gun.active = 0;
    g->gun.fire_cooldown = 0.0f;
    g->gun.anim_timer = 0.0f;
}