#include "../include/so_long_bonus.h"

void ft_init_vars(t_game *game)
{
    game->mlx_ptr = NULL;
    game->win_ptr = NULL;
    game->movements = 0;
    game->player_sprite = FRONT;
    game->enemy_frame = 1;
    game->frame_count = 0;
    game->map_alloc = false;
    game->map.full = NULL;
    game->map.rows = 0;
    game->map.columns = 0;
    game->map.coins = 0;
    game->map.exit = 0;
    game->map.players = 0;
    game->map.player.x = 0;
    game->map.player.y = 0;
}

void ft_init_mlx(t_game *game)
{
    game->mlx_ptr = mlx_init();
    if (!game->mlx_ptr)
        ft_error_msg("Error\nFailed to initialize MLX", game);

    game->win_ptr = mlx_new_window(game->mlx_ptr, 
                                  game->map.columns * IMG_WIDTH,
                                  game->map.rows * IMG_HEIGHT,
                                  "Space Explorer");
    if (!game->win_ptr)
        ft_error_msg("Error\nFailed to create window", game);
}

t_image ft_new_sprite(void *mlx, char *path, t_game *game)
{
    t_image sprite;

    ft_printf("Loading sprite: %s\n", path);
    sprite.xpm_ptr = mlx_xpm_file_to_image(mlx, path, &sprite.x, &sprite.y);
    if (!sprite.xpm_ptr)
        ft_error_msg("Error\nFailed to load sprite", game);
    return (sprite);
}

void ft_init_sprites(t_game *game)
{
    game->wall = ft_new_sprite(game->mlx_ptr, WALL_XPM, game);
    game->floor = ft_new_sprite(game->mlx_ptr, FLOOR_XPM, game);
    game->coins = ft_new_sprite(game->mlx_ptr, COINS_XPM, game);
    game->open_exit = ft_new_sprite(game->mlx_ptr, OPEN_EXIT_XPM, game);
    game->exit_closed = ft_new_sprite(game->mlx_ptr, EXIT_CLOSED_XPM, game);
    game->player_front = ft_new_sprite(game->mlx_ptr, PLAYER_FRONT_XPM, game);
    game->player_left = ft_new_sprite(game->mlx_ptr, PLAYER_LEFT_XPM, game);
    game->player_right = ft_new_sprite(game->mlx_ptr, PLAYER_RIGHT_XPM, game);
    game->player_back = ft_new_sprite(game->mlx_ptr, PLAYER_BACK_XPM, game);
    game->enemy = ft_new_sprite(game->mlx_ptr, ENEMY_1_XPM, game);
    game->enemy_1 = ft_new_sprite(game->mlx_ptr, ENEMY_1_XPM, game);
    game->enemy_2 = ft_new_sprite(game->mlx_ptr, ENEMY_2_XPM, game);
    game->enemy_3 = ft_new_sprite(game->mlx_ptr, ENEMY_3_XPM, game);
    game->enemy_4 = ft_new_sprite(game->mlx_ptr, ENEMY_4_XPM, game);
}

void ft_check_command_line_arguments(int argc, char **argv, t_game *game)
{
    int len;

    (void)game;
    if (argc != 2)
        ft_error_msg("Error\nUsage: ./so_long_bonus [map.ber]", game);

    len = ft_strlen(argv[1]);
    if (len < 4)
        ft_error_msg("Error\nInvalid map file", game);

    if (ft_strncmp(argv[1] + len - 4, ".ber", 4) != 0)
        ft_error_msg("Error\nMap file must have .ber extension", game);
}
