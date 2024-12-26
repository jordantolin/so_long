#include "../include/so_long_bonus.h"

void ft_free_map(t_game *game)
{
    int i;

    if (game->map_alloc)
    {
        i = 0;
        while (i < game->map.rows)
        {
            if (game->map.full[i])
                free(game->map.full[i]);
            i++;
        }
        if (game->map.full)
            free(game->map.full);
    }
}

void ft_destroy_images(t_game *game)
{
    if (game->mlx_ptr && game->wall.xpm_ptr)
        mlx_destroy_image(game->mlx_ptr, game->wall.xpm_ptr);
    if (game->mlx_ptr && game->floor.xpm_ptr)
        mlx_destroy_image(game->mlx_ptr, game->floor.xpm_ptr);
    if (game->mlx_ptr && game->coins.xpm_ptr)
        mlx_destroy_image(game->mlx_ptr, game->coins.xpm_ptr);
    if (game->mlx_ptr && game->open_exit.xpm_ptr)
        mlx_destroy_image(game->mlx_ptr, game->open_exit.xpm_ptr);
    if (game->mlx_ptr && game->exit_closed.xpm_ptr)
        mlx_destroy_image(game->mlx_ptr, game->exit_closed.xpm_ptr);
    if (game->mlx_ptr && game->player_front.xpm_ptr)
        mlx_destroy_image(game->mlx_ptr, game->player_front.xpm_ptr);
    if (game->mlx_ptr && game->player_left.xpm_ptr)
        mlx_destroy_image(game->mlx_ptr, game->player_left.xpm_ptr);
    if (game->mlx_ptr && game->player_right.xpm_ptr)
        mlx_destroy_image(game->mlx_ptr, game->player_right.xpm_ptr);
    if (game->mlx_ptr && game->player_back.xpm_ptr)
        mlx_destroy_image(game->mlx_ptr, game->player_back.xpm_ptr);
    if (game->mlx_ptr && game->enemy.xpm_ptr)
        mlx_destroy_image(game->mlx_ptr, game->enemy.xpm_ptr);
    if (game->mlx_ptr && game->enemy_1.xpm_ptr)
        mlx_destroy_image(game->mlx_ptr, game->enemy_1.xpm_ptr);
    if (game->mlx_ptr && game->enemy_2.xpm_ptr)
        mlx_destroy_image(game->mlx_ptr, game->enemy_2.xpm_ptr);
    if (game->mlx_ptr && game->enemy_3.xpm_ptr)
        mlx_destroy_image(game->mlx_ptr, game->enemy_3.xpm_ptr);
    if (game->mlx_ptr && game->enemy_4.xpm_ptr)
        mlx_destroy_image(game->mlx_ptr, game->enemy_4.xpm_ptr);
}

void ft_free_all_allocated_memory(t_game *game)
{
    ft_destroy_images(game);
    ft_free_map(game);
    if (game->win_ptr && game->mlx_ptr)
        mlx_destroy_window(game->mlx_ptr, game->win_ptr);
    if (game->mlx_ptr)
    {
        mlx_destroy_display(game->mlx_ptr);
        free(game->mlx_ptr);
    }
}

int ft_close_game(t_game *game)
{
    ft_free_all_allocated_memory(game);
    exit(0);
    return (0);
}

int ft_victory(t_game *game)
{
    ft_printf("\n%sVictory! You collected all coins and reached the exit!%s\n", GREEN, RESET);
    ft_printf("%sTotal moves: %d%s\n\n", CYAN, game->movements, RESET);
    ft_close_game(game);
    return (0);
}

int ft_loss(t_game *game)
{
    ft_printf("\n%sGame Over! You were caught by an enemy!%s\n", RED, RESET);
    ft_printf("%sTotal moves: %d%s\n\n", GREY, game->movements, RESET);
    ft_close_game(game);
    return (0);
}

int ft_error_msg(char *message, t_game *game)
{
    ft_printf("%s\n", message);
    ft_free_all_allocated_memory(game);
    exit(-1);
    return (-1);
}
