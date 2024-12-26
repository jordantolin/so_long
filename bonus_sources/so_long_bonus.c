#include "../include/so_long_bonus.h"

int main(int argc, char **argv)
{
    t_game  game;

    ft_check_command_line_arguments(argc, argv, &game);
    ft_init_vars(&game);
    ft_init_map(&game, argv[1]);
    ft_check_map(&game);
    ft_init_mlx(&game);
    ft_init_sprites(&game);

    mlx_hook(game.win_ptr, KeyPress, KeyPressMask, ft_handle_input, &game);
    mlx_hook(game.win_ptr, DestroyNotify, NoEventMask, ft_close_game, &game);
    mlx_loop_hook(game.mlx_ptr, ft_render_map, &game);

    mlx_loop(game.mlx_ptr);

    return (0);
}
