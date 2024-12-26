#include "../include/so_long.h"

void update_player_position(t_game *game, int new_x, int new_y)
{
    char next = game->map[new_y][new_x];

    if (next == WALL || (next == EXIT && game->collected_count < game->collectibles_count))
        return;

    game->map[game->player_y][game->player_x] = EMPTY;
    if (next == COLLECTIBLE)
    {
        game->collected_count++;
    }
    else if (next == EXIT && game->collected_count == game->collectibles_count)
    {
        game->game_over = 1;
        ft_printf("\nCongratulations! You've won in %d moves!\n", game->moves);
        clean_exit(game, EXIT_SUCCESS);
    }

    game->map[new_y][new_x] = PLAYER;
    game->player_x = new_x;
    game->player_y = new_y;
    game->moves++;
    ft_printf("Moves: %d\n", game->moves);
}

void handle_movement(t_game *game, int new_x, int new_y)
{
    if (new_x < 0 || new_x >= game->map_width || 
        new_y < 0 || new_y >= game->map_height)
        return;

    update_player_position(game, new_x, new_y);
}

int key_press(int keycode, t_game *game)
{
    if (keycode == KEY_ESC)
        clean_exit(game, EXIT_SUCCESS);
    else if (keycode == KEY_W || keycode == KEY_UP)
        handle_movement(game, game->player_x, game->player_y - 1);
    else if (keycode == KEY_S || keycode == KEY_DOWN)
        handle_movement(game, game->player_x, game->player_y + 1);
    else if (keycode == KEY_A || keycode == KEY_LEFT)
    {
        game->player_direction = -1;
        handle_movement(game, game->player_x - 1, game->player_y);
    }
    else if (keycode == KEY_D || keycode == KEY_RIGHT)
    {
        game->player_direction = 1;
        handle_movement(game, game->player_x + 1, game->player_y);
    }

    return (0);
}

int key_release(int keycode, t_game *game)
{
    (void)keycode;
    game->key_pressed = 0;
    return (0);
}