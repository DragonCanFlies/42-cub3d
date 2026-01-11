#include "cub3d.h"


/*
 * close_window - Clean up and exit
 */
int	close_window(t_game *game)
{
	mlx_destroy_image(game->mlx, game->img.img);
	mlx_destroy_window(game->mlx, game->win);
	exit(0);
	return (0);
}

void	init_map(t_game *game)
{
	int map_data[] = {
		1,1,1,1,1,1,1,1,  // Row 0: Top boundary wall
		1,0,1,0,0,0,0,1,  // Row 1: Interior with vertical wall at x=2
		1,0,1,0,0,0,0,1,  // Row 2
		1,0,1,0,0,0,0,1,  // Row 3
		1,0,0,0,0,0,0,1,  // Row 4: Open space
		1,0,0,0,0,1,0,1,  // Row 5: Wall at x=5
		1,0,0,0,0,0,0,1,  // Row 6
		1,1,1,1,1,1,1,1   // Row 7: Bottom boundary wall
	};
	int i;

	i = 0;
	while (i < MAP_X * MAP_Y)
	{
		game->map[i] = map_data[i];
		i++;
	}
}
/*
 * ============================================================================
 * PLAYER MOVEMENT
 * ============================================================================
 */

/*
 * update_player - Handle smooth player movement
 * 
 * Called every frame to check key states and update player position
 * 
 * Features:
 * - Rotation (A/D keys)
 * - Forward/backward movement (W/S keys)
 * - Collision detection
 */
void	update_player(t_game *game)
{
	float	new_x;
	float	new_y;
	int		mx, my, mp;

	// Start with current position
	new_x = game->player.x;
	new_y = game->player.y;

	/*
	 * ROTATION
	 * When rotating, we need to recalculate the direction vector
	 */
	if (game->keys.a)
	{
		// Rotate left (increase angle)
		game->player.angle += ROT_SPEED;
		game->player.angle = fix_angle(game->player.angle);
		
		// Recalculate direction vector from angle
		// dx = adjacent side of unit circle
		// dy = opposite side (negative because screen Y increases downward)
		game->player.dx = cos(deg_to_rad(game->player.angle));
		game->player.dy = -sin(deg_to_rad(game->player.angle));
	}
	if (game->keys.d)
	{
		// Rotate right (decrease angle)
		game->player.angle -= ROT_SPEED;
		game->player.angle = fix_angle(game->player.angle);
		game->player.dx = cos(deg_to_rad(game->player.angle));
		game->player.dy = -sin(deg_to_rad(game->player.angle));
	}
	
	/*
	 * FORWARD/BACKWARD MOVEMENT
	 * Move along the direction vector (dx, dy)
	 */
	if (game->keys.w)
	{
		// Move forward: add direction vector × speed
		new_x += game->player.dx * MOVE_SPEED;
		new_y += game->player.dy * MOVE_SPEED;
	}
	if (game->keys.s)
	{
		// Move backward: subtract direction vector × speed
		new_x -= game->player.dx * MOVE_SPEED;
		new_y -= game->player.dy * MOVE_SPEED;
	}

	/*
	 * COLLISION DETECTION
	 * Before moving, check if new position would be inside a wall
	 */
	
	// Convert world coordinates to grid coordinates
	mx = (int)(new_x) >> 6;  // Divide by 64 using bit shift
	my = (int)(new_y) >> 6;
	mp = my * MAP_X + mx;    // Array index
	
	// Only move if:
	// 1. Position is within map bounds
	// 2. Destination cell is empty (not a wall)
	if (mp >= 0 && mp < MAP_X * MAP_Y && game->map[mp] == 0)
	{
		game->player.x = new_x;
		game->player.y = new_y;
	}
	// If collision detected, player stays at old position
}

/*
 * ============================================================================
 * MAIN RENDER LOOP
 * ============================================================================
 */

/*
 * render - Main rendering function called every frame
 * 
 * Order of operations:
 * 1. Clear screen (fill with gray)
 * 2. Update player position based on input
 * 3. Draw 2D map view
 * 4. Draw 3D raycasted view
 * 5. Draw player on 2D map
 * 6. Display the final image
 */
int	render(t_game *game)
{
	int	i;

	// Clear the image buffer (gray background)
	i = 0;
	while (i < WIN_WIDTH * WIN_HEIGHT)
	{
		((int *)game->img.buffer)[i] = 0x4C4C4C;  // Medium gray
		i++;
	}

	// Update game state
	update_player(game);
	
	// Draw everything
	//draw_map_2d(game);      // 2D top-down map (left side)
	ray_caster(game);     // 3D raycasted view (right side)
	//draw_player_2d(game);   // Player indicator on 2D map

	// Display the image buffer to the window
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	
	return (0);
}

/*
 * ============================================================================
 * INPUT HANDLING
 * ============================================================================
 */

/*
 * key_press - Called when a key is pressed down
 * 
 * Sets the corresponding flag to 1 (key is held)
 */
int	key_press(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		close_window(game);
	if (keycode == KEY_W)
		game->keys.w = 1;
	if (keycode == KEY_A)
		game->keys.a = 1;
	if (keycode == KEY_S)
		game->keys.s = 1;
	if (keycode == KEY_D)
		game->keys.d = 1;
	return (0);
}

/*
 * key_release - Called when a key is released
 * 
 * Sets the corresponding flag to 0 (key is not held)
 */
int	key_release(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		game->keys.w = 0;
	if (keycode == KEY_A)
		game->keys.a = 0;
	if (keycode == KEY_S)
		game->keys.s = 0;
	if (keycode == KEY_D)
		game->keys.d = 0;
	return (0);
}



int	main(void)
{
	t_game	g;

	// Initialize MinilibX
	g.mlx = mlx_init();
	if (!g.mlx)
		return (1);
	
	// Create window
	g.win = mlx_new_window(g.mlx, WIN_WIDTH, WIN_HEIGHT, "Raycaster MLX");
	if (!g.win)
		return (1);

	// Create image buffer for fast rendering
	g.img.img = mlx_new_image(g.mlx, WIN_WIDTH, WIN_HEIGHT);
	g.img.buffer = mlx_get_data_addr(g.img.img, &g.img.bpp,
		&g.img.line_len, &g.img.endian);

	// Initialize game g
	init_map(&g);
	g.px_per_ray = (WIN_WIDTH * RAY_ACC) / FOV;
	if ((WIN_WIDTH * RAY_ACC) % FOV)
		write(10, "warning PIXELS_PER_RAY is not an integer", 40);
	// Set starting player position and angle
	g.player.x = 150;      // World coordinates (pixels)
	g.player.y = 400;
	g.player.angle = 90;   // Facing right (90 degrees)
	
	// Calculate initial direction vector
	g.player.dx = cos(deg_to_rad(g.player.angle));
	g.player.dy = -sin(deg_to_rad(g.player.angle));
	
	// Initialize key states (all keys not pressed)
	g.keys.w = 0;
	g.keys.a = 0;
	g.keys.s = 0;
	g.keys.d = 0;

	// Set up event hooks
	mlx_hook(g.win, 2, 1L << 0, key_press, &g);     // Key down
	mlx_hook(g.win, 3, 1L << 1, key_release, &g);   // Key up
	mlx_hook(g.win, 17, 0, close_window, &g);       // Window close
	mlx_loop_hook(g.mlx, render, &g);                // Render loop

	// Start the event loop
	mlx_loop(g.mlx);

	return (0);
}