#include "../include/so_long_bonus.h"

void ft_player_move(t_game *game, int x, int y, int player_sprite)
{
    int new_x;
    int new_y;

    new_x = game->map.player.x + x;
    new_y = game->map.player.y + y;

    if (game->map.full[new_y][new_x] != WALL)
    {
        if (game->map.full[new_y][new_x] == ENEMY)
            ft_loss(game);
        else if (game->map.full[new_y][new_x] == MAP_EXIT && game->map.coins == 0)
            ft_victory(game);
        else if (game->map.full[new_y][new_x] == COINS)
            game->map.coins--;

        if (game->map.full[new_y][new_x] != MAP_EXIT)
        {
            game->map.full[game->map.player.y][game->map.player.x] = FLOOR;
            game->map.full[new_y][new_x] = PLAYER;
            game->map.player.x = new_x;
            game->map.player.y = new_y;
            game->movements++;
            ft_printf("Moves: %d\n", game->movements);
        }
    }
    game->player_sprite = player_sprite;
}

int ft_handle_input(int keysym, t_game *game)
{
    if (keysym == KEY_W || keysym == KEY_UP)
        ft_player_move(game, 0, -1, BACK);
    else if (keysym == KEY_S || keysym == KEY_DOWN)
        ft_player_move(game, 0, 1, FRONT);
    else if (keysym == KEY_A || keysym == KEY_LEFT)
        ft_player_move(game, -1, 0, LEFT);
    else if (keysym == KEY_D || keysym == KEY_RIGHT)
        ft_player_move(game, 1, 0, RIGHT);
    else if (keysym == KEY_Q || keysym == KEY_ESC)
        ft_close_game(game);
    return (0);
}
