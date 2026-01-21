#include "cub3d.h"

void	init_sprites(t_game *g)
{
	g->sprites = malloc(sizeof(t_sprite) * MAX_SPRITES);
	if (!g->sprites)
		perror_exit("Sprite allocation failed");
	g->zbuffer = malloc(sizeof(float) * WIN_WIDTH);
	if (!g->zbuffer)
		perror_exit("Zbuffer allocation failed");
	g->sprite_count = 0;
	g->collectibles = 0;
	load_sprite_tex(g);
	parse_sprites(g);
}

void	load_sprite_tex(t_game *g)
{
	if (!load_texture("textures/ghost1.xpm", &g->spr_tex[0], g))
		perror_exit("Ghost1 texture failed");
	if (!load_texture("textures/ghost2.xpm", &g->spr_tex[1], g))
		perror_exit("Ghost2 texture failed");
	if (!load_texture("textures/ghost3.xpm", &g->spr_tex[2], g))
		perror_exit("Ghost3 texture failed");
	if (!load_texture("textures/ghost4.xpm", &g->spr_tex[3], g))
		perror_exit("Ghost4 texture failed");
	if (!load_texture("textures/fruit.xpm", &g->spr_tex[4], g))
		perror_exit("Fruit texture failed");
	if (!load_texture("textures/food.xpm", &g->spr_tex[5], g))
        perror_exit("Food texture failed");
}

void	add_sprite(t_game *g, float x, float y, int type)
{
	t_sprite	*s;

	if (g->sprite_count >= MAX_SPRITES)
		return ;
	s = &g->sprites[g->sprite_count];
	s->x = (x * MAP_S) + (MAP_S >> 1);
	s->y = (y * MAP_S) + (MAP_S >> 1);
	s->type = type;
	s->alive = 1;
    if (type == TYPE_ENEMY)
    {
        s->tex_id = TEX_GHOST1;
        s->health = ENEMY_MAX_HEALTH;
        s->max_health = ENEMY_MAX_HEALTH;
    }
	else if (type == TYPE_FRUIT)
		s->tex_id = TEX_FRUIT;
	else if (type == TYPE_FOOD)
		s->tex_id = TEX_FOOD;
	g->sprite_count++;
}

static int	is_sprite_char(char c)
{
	return (c == 'G' || c == 'F' || c == '.');
}

static void	add_sprite_type(t_game *g, char c, int x, int y)
{
	if (c == 'G')
		add_sprite(g, (float)x, (float)y, TYPE_ENEMY);
	else if (c == 'F')
		add_sprite(g, (float)x, (float)y, TYPE_FRUIT);
	else if (c == '.')
	{
		add_sprite(g, (float)x, (float)y, TYPE_FOOD);
		g->collectibles++;
	}
}

void	parse_sprites(t_game *g)
{
	int		y;
	int		x;
	char	c;

	y = 0;
	while (y < g->map.y)
	{
		x = 0;
		while (x < g->map.x)
		{
			c = g->map.raw_map[y][x];
			if (is_sprite_char(c))
			{
				add_sprite_type(g, c, x, y);
				g->map.raw_map[y][x] = '0';
				g->map.map_data[y * g->map.x + x] = 0;
			}
			x++;
		}
		y++;
	}
}