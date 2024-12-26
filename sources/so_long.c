#include "../include/so_long.h"

void	clean_exit(t_game *game, int status)
{
	if (game)
	{
		if (game->map)
			free_map(game->map);
		if (game->mlx && game->win)
		{
			if (game->img_wall)
				mlx_destroy_image(game->mlx, game->img_wall);
			if (game->img_floor)
				mlx_destroy_image(game->mlx, game->img_floor);
			if (game->img_player_right)
				mlx_destroy_image(game->mlx, game->img_player_right);
			if (game->img_player_left)
				mlx_destroy_image(game->mlx, game->img_player_left);
			if (game->img_collectible)
				mlx_destroy_image(game->mlx, game->img_collectible);
			if (game->img_exit)
				mlx_destroy_image(game->mlx, game->img_exit);
			mlx_destroy_window(game->mlx, game->win);
		}
		if (game->mlx)
		{
			mlx_destroy_display(game->mlx);
			free(game->mlx);
		}
	}
	exit(status);
}

void	init_game(t_game *game)
{
	ft_memset(game, 0, sizeof(t_game));
	game->player_direction = 1;
}

void	check_game_over(t_game *game)
{
	if (game->collected_count == game->collectibles_count &&
		game->map[game->player_y][game->player_x] == 'E')
	{
		ft_printf("\nCongratulations! You've won in %d moves!\n", game->moves);
		clean_exit(game, EXIT_SUCCESS);
	}
}

void	find_player_position(t_game *game)
{
    int x;
    int y;

    y = 0;
    while (y < game->map_height)
    {
        x = 0;
        while (x < game->map_width)
        {
            if (game->map[y][x] == 'P')
            {
                game->player_x = x;
                game->player_y = y;
                return;
            }
            x++;
        }
        y++;
    }
}

void	close_window(t_game *game)
{
    if (game->img_wall)
        mlx_destroy_image(game->mlx, game->img_wall);
    if (game->img_floor)
        mlx_destroy_image(game->mlx, game->img_floor);
    if (game->img_player_right)
        mlx_destroy_image(game->mlx, game->img_player_right);
    if (game->img_player_left)
        mlx_destroy_image(game->mlx, game->img_player_left);
    if (game->img_collectible)
        mlx_destroy_image(game->mlx, game->img_collectible);
    if (game->img_exit)
        mlx_destroy_image(game->mlx, game->img_exit);
    
    if (game->win)
        mlx_destroy_window(game->mlx, game->win);
    if (game->mlx)
    {
        mlx_destroy_display(game->mlx);
        free(game->mlx);
    }
    if (game->map)
        free_map(game->map);
    exit(0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc == 1)
	{
		ft_printf("Error\n");
		return (EXIT_FAILURE);
	}
	if (argc > 2)
	{
		ft_printf("Error\n");
		return (EXIT_FAILURE);
	}
	if (!check_file_extension(argv[1]))
	{
		ft_printf("Error\nInvalid file extension (must be .ber)\n");
		return (EXIT_FAILURE);
	}

	init_game(&game);

	if (!read_map(&game, argv[1]))
	{
		clean_exit(&game, EXIT_FAILURE);
		return (EXIT_FAILURE);
	}

	if (!validate_map(&game))
	{
		clean_exit(&game, EXIT_FAILURE);
		return (EXIT_FAILURE);
	}

	game.mlx = mlx_init();
	if (!game.mlx)
	{
		ft_printf("Error\nFailed to initialize MLX\n");
		clean_exit(&game, EXIT_FAILURE);
	}

	game.win = mlx_new_window(game.mlx, game.map_width * TILE_SIZE,
			game.map_height * TILE_SIZE, "So Long");
	if (!game.win)
	{
		ft_printf("Error\nFailed to create window\n");
		clean_exit(&game, EXIT_FAILURE);
	}

	if (!load_textures(&game))
		clean_exit(&game, EXIT_FAILURE);

	find_player_position(&game);

	mlx_hook(game.win, 2, 1L << 0, handle_keypress, &game);
	mlx_hook(game.win, 17, 0, handle_close_button, &game);
	mlx_loop_hook(game.mlx, render_game, &game);

	mlx_loop(game.mlx);
	return (EXIT_SUCCESS);
}
