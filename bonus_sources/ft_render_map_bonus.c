#include "../include/so_long_bonus.h"

void ft_render_sprite(t_game *game, t_image sprite, int column, int line)
{
    mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, sprite.xpm_ptr,
                           column * IMG_WIDTH, line * IMG_HEIGHT);
}

void ft_render_player(t_game *game, int x, int y)
{
    if (game->player_sprite == FRONT)
        ft_render_sprite(game, game->player_front, x, y);
    else if (game->player_sprite == LEFT)
        ft_render_sprite(game, game->player_left, x, y);
    else if (game->player_sprite == RIGHT)
        ft_render_sprite(game, game->player_right, x, y);
    else if (game->player_sprite == BACK)
        ft_render_sprite(game, game->player_back, x, y);
}

void ft_render_enemy(t_game *game, int x, int y)
{
    if (game->enemy_frame == 1)
        ft_render_sprite(game, game->enemy_1, x, y);
    else if (game->enemy_frame == 2)
        ft_render_sprite(game, game->enemy_2, x, y);
    else if (game->enemy_frame == 3)
        ft_render_sprite(game, game->enemy_3, x, y);
    else if (game->enemy_frame == 4)
        ft_render_sprite(game, game->enemy_4, x, y);

    // Update animation frame every 10 frames
    game->frame_count++;
    if (game->frame_count >= 10)
    {
        game->frame_count = 0;
        game->enemy_frame = (game->enemy_frame % 4) + 1;
    }
}

void ft_identify_sprite(t_game *game, int x, int y)
{
    if (game->map.full[y][x] == WALL)
        ft_render_sprite(game, game->wall, x, y);
    else if (game->map.full[y][x] == FLOOR)
        ft_render_sprite(game, game->floor, x, y);
    else if (game->map.full[y][x] == COINS)
        ft_render_sprite(game, game->coins, x, y);
    else if (game->map.full[y][x] == MAP_EXIT && game->map.coins == 0)
        ft_render_sprite(game, game->open_exit, x, y);
    else if (game->map.full[y][x] == MAP_EXIT)
        ft_render_sprite(game, game->exit_closed, x, y);
    else if (game->map.full[y][x] == ENEMY)
        ft_render_enemy(game, x, y);
    else if (game->map.full[y][x] == PLAYER)
        ft_render_player(game, x, y);
}

void ft_move_enemy(t_game *game, int enemy_index)
{
    t_enemy *enemy = &game->map.enemies[enemy_index];
    int new_x = enemy->x;
    int new_y = enemy->y;

    // Try to move in current direction
    if (enemy->direction == 0) // up
        new_y--;
    else if (enemy->direction == 1) // right
        new_x++;
    else if (enemy->direction == 2) // down
        new_y++;
    else if (enemy->direction == 3) // left
        new_x--;

    char current_tile = game->map.full[new_y][new_x];

    // Check if move is valid (don't move onto walls, other enemies, exits, or collectibles)
    if (current_tile != WALL && current_tile != ENEMY && 
        current_tile != MAP_EXIT && current_tile != COINS)
    {
        // Check for player collision
        if (current_tile == PLAYER)
            ft_loss(game);

        // Move enemy
        game->map.full[enemy->y][enemy->x] = FLOOR;
        game->map.full[new_y][new_x] = ENEMY;
        enemy->x = new_x;
        enemy->y = new_y;
    }
    else
    {
        // Change direction if blocked
        enemy->direction = (enemy->direction + 1) % 4;
    }
}

void ft_update_enemies(t_game *game)
{
    static int delay_counter = 0;
    int i;

    delay_counter++;
    if (delay_counter >= ENEMY_MOVE_DELAY)
    {
        delay_counter = 0;
        for (i = 0; i < game->map.num_enemies; i++)
        {
            ft_move_enemy(game, i);
        }
    }
}

int ft_render_map(t_game *game)
{
    int x;
    int y;
    char *moves_str;

    // Update enemy positions
    ft_update_enemies(game);

    y = 0;
    while (y < game->map.rows)
    {
        x = 0;
        while (x < game->map.columns)
        {
            ft_identify_sprite(game, x, y);
            x++;
        }
        y++;
    }
    
    // Display movement count on screen
    moves_str = ft_itoa(game->movements);
    mlx_string_put(game->mlx_ptr, game->win_ptr, 10, 20, 0xFFFFFF, "Moves: ");
    mlx_string_put(game->mlx_ptr, game->win_ptr, 70, 20, 0xFFFFFF, moves_str);
    free(moves_str);
    
    return (0);
}
