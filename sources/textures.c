#include "../include/so_long.h"

static void	*load_xpm_image(void *mlx, char *path)
{
	void	*img;
	int		width;
	int		height;

	img = mlx_xpm_file_to_image(mlx, path, &width, &height);
	if (!img)
		ft_printf(ERR_TEXTURE, path);
	return (img);
}

int	load_textures(t_game *game)
{
	if (!game || !game->mlx)
		return (0);

	game->img_wall = load_xpm_image(game->mlx, "assets/mandatory_wall.xpm");
	game->img_floor = load_xpm_image(game->mlx, "assets/mandatory_floor.xpm");
	game->img_player_right = load_xpm_image(game->mlx, "assets/mandatory_player.xpm");
	game->img_player_left = load_xpm_image(game->mlx, "assets/mandatory_player.xpm");
	game->img_collectible = load_xpm_image(game->mlx, "assets/mandatory_collectible.xpm");
	game->img_exit = load_xpm_image(game->mlx, "assets/mandatory_exit.xpm");

	if (!game->img_wall || !game->img_floor || !game->img_player_right ||
		!game->img_player_left || !game->img_collectible || !game->img_exit)
		return (0);
	return (1);
}

int	render_game(t_game *game)
{
	int	x;
	int	y;

	if (!game || !game->mlx || !game->win || !game->map)
		return (0);
	y = -1;
	while (++y < game->map_height)
	{
		x = -1;
		while (++x < game->map_width)
		{
			mlx_put_image_to_window(game->mlx, game->win, game->img_floor,
				x * TILE_SIZE, y * TILE_SIZE);
			if (game->map[y][x] == WALL)
				mlx_put_image_to_window(game->mlx, game->win, game->img_wall,
					x * TILE_SIZE, y * TILE_SIZE);
			else if (game->map[y][x] == COLLECTIBLE)
				mlx_put_image_to_window(game->mlx, game->win, game->img_collectible,
					x * TILE_SIZE, y * TILE_SIZE);
			else if (game->map[y][x] == EXIT)
				mlx_put_image_to_window(game->mlx, game->win, game->img_exit,
					x * TILE_SIZE, y * TILE_SIZE);
			else if (game->map[y][x] == PLAYER)
				mlx_put_image_to_window(game->mlx, game->win,
					(game->player_direction == 1) ? game->img_player_right
					: game->img_player_left, x * TILE_SIZE, y * TILE_SIZE);
		}
	}
    // Enhanced HUD with clear font and color
    char hud[128];
    sprintf(hud, "Moves: %d | Collectibles: %d/%d", game->moves, game->collected_count, game->collectibles_count);
    mlx_string_put(game->mlx, game->win, 20, 20, 0x00FF00, hud); // Green color for better visibility

    // Visual feedback for collectibles
    if (game->collected_count > 0) {
        char feedback[64];
        sprintf(feedback, "Collected: %d", game->collected_count);
        mlx_string_put(game->mlx, game->win, 20, 40, 0xFFD700, feedback); // Gold color for collectibles
    }
	return (1);
}