#include "cub3d.h"

static void    render_health_bar(t_game *g)
{
    int     bar_width;
    int     bar_height;
    int     x;
    int     y;
    int     health_width;
    int     i;
    int     j;
    int     color;  // MOVED TO TOP

    bar_width = 200;
    bar_height = 20;
    x = 20;
    y = 20;
    
    health_width = (g->health * bar_width) / g->max_health;
    if (health_width < 0)
        health_width = 0;
    
    // Draw background (black)
    j = 0;
    while (j < bar_height)
    {
        i = 0;
        while (i < bar_width)
        {
            put_pixel(&g->img, x + i, y + j, 0x000000);
            i++;
        }
        j++;
    }
    
    // Calculate health color
    if (g->health < 30)
        color = 0xFF0000;
    else if (g->health < 60)
        color = 0xFFFF00;
    else
        color = 0x00FF00;
    
    // Draw health bar
    j = 0;
    while (j < bar_height)
    {
        i = 0;
        while (i < health_width)
        {
            put_pixel(&g->img, x + i, y + j, color);
            i++;
        }
        j++;
    }
    
    // Draw border (white)
    i = 0;
    while (i < bar_width)
    {
        put_pixel(&g->img, x + i, y, 0xFFFFFF);
        put_pixel(&g->img, x + i, y + bar_height - 1, 0xFFFFFF);
        i++;
    }
    j = 0;
    while (j < bar_height)
    {
        put_pixel(&g->img, x, y + j, 0xFFFFFF);
        put_pixel(&g->img, x + bar_width - 1, y + j, 0xFFFFFF);
        j++;
    }
}

void    render_player_hud(t_game *g)
{
    char    text[64];
    static float    elapsed = 0.0f;
    static int      frames = 0;
    
    // Render health bar
    render_health_bar(g);
    
    // Draw health text
    snprintf(text, sizeof(text), "HP: %d/%d", g->health, g->max_health);
    mlx_string_put(g->mlx, g->win, 20, 50, 0xFFFFFF, text);
    
    // FPS counter (for debugging timer)
    elapsed += g->delta_time;
    frames++;
    if (elapsed >= 1.0f)
    {
        snprintf(text, sizeof(text), "FPS: %d", frames);
        mlx_string_put(g->mlx, g->win, 20, 80, 0xFFFF00, text);
        frames = 0;
        elapsed = 0.0f;
    }
    
    // If taking damage, flash red
    if (g->damage_cooldown > 0.0f)
    {
        mlx_string_put(g->mlx, g->win, WIN_WIDTH / 2 - 30, 50,
            0xFF0000, "DAMAGED!");
    }
}
