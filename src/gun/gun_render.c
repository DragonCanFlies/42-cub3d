#include "cub3d.h"

// Draw scaled sprite to screen
static void draw_gun_sprite(t_game *g, t_img *tex, int x, int y, int w, int h)
{
    int     screen_x;
    int     screen_y;
    int     tex_x;
    int     tex_y;
    int     color;

    screen_y = 0;
    while (screen_y < h)
    {
        screen_x = 0;
        while (screen_x < w)
        {
            tex_x = screen_x * tex->width / w;
            tex_y = screen_y * tex->height / h;
            color = get_spr_pixel(tex, tex_x, tex_y);
            if (!is_transparent(color))
                put_pixel(&g->img, x + screen_x, y + screen_y, color);
            screen_x++;
        }
        screen_y++;
    }
}

void    render_gun(t_game *g)
{
    t_img   *frame;
    int     gun_w;
    int     gun_h;
    int     x;
    int     y;

    if (!g->gun.active)
        return;
    
    // Get current animation frame
    frame = &g->gun.frames[g->gun.current_frame];
    
    // Size and position (bottom center of screen)
    gun_w = 480;  // Adjust to your preference
    gun_h = 480;  // Keep aspect ratio
    x = (WIN_WIDTH - gun_w) / 2;
    y = WIN_HEIGHT - gun_h;
    
    // Draw gun sprite
    draw_gun_sprite(g, frame, x, y, gun_w, gun_h);
}

// Optional: Draw ammo counter
void    render_gun_hud(t_game *g)
{
    char    *ammo_str;
    char    *timer_str;
    int     timer_int;
        
    if (!g->gun.active)
        return;
    
    ammo_str = ft_itoa(g->gun.ammo);
    if (!ammo_str)
    {
        printf("ft_itoa failed for ammo!\n");
        return;
    }
        
    mlx_string_put(g->mlx, g->win, WIN_WIDTH - 150, WIN_HEIGHT - 30,
        0xFFFFFF, "AMMO: ");
    mlx_string_put(g->mlx, g->win, WIN_WIDTH - 80, WIN_HEIGHT - 30,
        0xFFFF00, ammo_str);
    
    timer_int = (int)g->gun.timer;
    timer_str = ft_itoa(timer_int);
    
    mlx_string_put(g->mlx, g->win, 20, WIN_HEIGHT - 30,
        0xFFFFFF, "TIME: ");
    mlx_string_put(g->mlx, g->win, 90, WIN_HEIGHT - 30,
        0x00FF00, timer_str);
    
    free(ammo_str);
    free(timer_str);
}
