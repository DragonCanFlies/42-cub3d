#include "cub3d.h"

#include "cub3d.h"

void    animate_gun(t_gun *gun)
{
    // Clamp current_frame to valid range [0-4]
    if (gun->current_frame < 0)
        gun->current_frame = 0;
    if (gun->current_frame > 4)
        gun->current_frame = 4;
    
    if (gun->state == GUN_IDLE)
    {
        gun->current_frame = 0;
        gun->anim_timer = 0.0f;
    }
    else if (gun->state == GUN_FIRE_START)
    {
        gun->current_frame = 1;
        if (gun->anim_timer >= GUN_ANIM_SPEED)
        {
            gun->state = GUN_FIRING;
            gun->current_frame = 2;
            gun->anim_timer = 0.0f;
        }
    }
    else if (gun->state == GUN_FIRING)
    {
        // Cycle between frames 2 and 3 while firing
        if (gun->anim_timer >= GUN_ANIM_SPEED)
        {
            if (gun->current_frame == 2)
                gun->current_frame = 3;
            else if (gun->current_frame == 3)
                gun->current_frame = 2;
            else
                gun->current_frame = 2;  // Reset if out of sync
            gun->anim_timer = 0.0f;
        }
    }
    else if (gun->state == GUN_FIRE_END)
    {
        gun->current_frame = 4;
        if (gun->anim_timer >= GUN_ANIM_SPEED)
        {
            gun->state = GUN_IDLE;
            gun->current_frame = 0;
            gun->anim_timer = 0.0f;
        }
    }
}