#include "../include/so_long_bonus.h"

void ft_check_map(t_game *game)
{
    ft_check_rows(game);
    ft_check_columns(game);
    ft_count_map_parameters(game);
    ft_verify_map_parameters(game);
}

void ft_check_rows(t_game *game)
{
    int i;
    int j;

    i = 0;
    while (i < game->map.rows)
    {
        if (i == 0 || i == game->map.rows - 1)
        {
            j = 0;
            while (j < game->map.columns)
            {
                if (game->map.full[i][j] != WALL)
                    ft_error_msg("Error\nMap must be surrounded by walls", game);
                j++;
            }
        }
        else if (game->map.full[i][0] != WALL || 
                 game->map.full[i][game->map.columns - 1] != WALL)
            ft_error_msg("Error\nMap must be surrounded by walls", game);
        i++;
    }
}

void ft_check_columns(t_game *game)
{
    int i;
    size_t len;

    i = 0;
    while (i < game->map.rows)
    {
        len = ft_strlen(game->map.full[i]);
        if (len != (size_t)game->map.columns)
            ft_error_msg("Error\nMap must be rectangular", game);
        i++;
    }
}

void ft_count_map_parameters(t_game *game)
{
    int i;
    int j;

    i = 0;
    while (i < game->map.rows)
    {
        j = 0;
        while (j < game->map.columns)
        {
            if (game->map.full[i][j] == PLAYER)
            {
                game->map.players++;
                game->map.player.x = j;
                game->map.player.y = i;
            }
            else if (game->map.full[i][j] == COINS)
                game->map.coins++;
            else if (game->map.full[i][j] == MAP_EXIT)
                game->map.exit++;
            else if (game->map.full[i][j] != WALL && 
                     game->map.full[i][j] != FLOOR &&
                     game->map.full[i][j] != ENEMY)
                ft_error_msg("Error\nInvalid character in map", game);
            j++;
        }
        i++;
    }
}

void ft_verify_map_parameters(t_game *game)
{
    if (game->map.players != 1)
        ft_error_msg("Error\nMap must contain exactly one player", game);
    if (game->map.coins < 1)
        ft_error_msg("Error\nMap must contain at least one collectible", game);
    if (game->map.exit != 1)
        ft_error_msg("Error\nMap must contain exactly one exit", game);
}
