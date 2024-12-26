#include "../include/so_long.h"

int handle_keypress(int keycode, t_game *game)
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

int handle_close_button(t_game *game)
{
    clean_exit(game, EXIT_SUCCESS);
    return (0);
}
