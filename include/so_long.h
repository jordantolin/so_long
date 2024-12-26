#ifndef SO_LONG_H
# define SO_LONG_H

# include <mlx.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include "../libraries/ft_printf/ft_printf.h"
# include "../libraries/get_next_line/get_next_line.h"
# include "../libraries/libft/libft.h"

/*
** Map components
*/
# define EMPTY '0'
# define WALL '1'
# define COLLECTIBLE 'C'
# define EXIT 'E'
# define PLAYER 'P'

/*
** Window settings
*/
# define TILE_SIZE 32

/*
** Key codes
*/
# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_UP 65362
# define KEY_LEFT 65361
# define KEY_DOWN 65364
# define KEY_RIGHT 65363

/*
** Error messages
*/
# define ERR_USAGE "Error\nUsage: ./so_long <map_file.ber>\n"
# define ERR_MAP "Error\nInvalid map\n"
# define ERR_FILE "Error\nCould not open file\n"
# define ERR_TEXTURE "Error\nFailed to load texture: %s\n"

typedef struct s_game
{
    void    *mlx;
    void    *win;
    void    *img_wall;
    void    *img_floor;
    void    *img_player_right;
    void    *img_player_left;
    void    *img_collectible;
    void    *img_exit;
    char    **map;
    int     map_width;
    int     map_height;
    int     player_x;
    int     player_y;
    int     player_direction;
    int     moves;
    int     collectibles_count;
    int     collected_count;
    int     key_pressed;
    int     game_over;
}   t_game;

/*
** Function prototypes
*/
int     check_file_extension(char *filename);
int     read_map(t_game *game, char *filename);
int     validate_map(t_game *game);
int     load_textures(t_game *game);
void    init_game(t_game *game);
void    find_player_position(t_game *game);
int     handle_keypress(int keycode, t_game *game);
int     handle_close_button(t_game *game);
void    clean_exit(t_game *game, int status);
void    check_game_over(t_game *game);
int     render_game(t_game *game);
void    update_player_position(t_game *game, int new_x, int new_y);
void    smooth_move_player(t_game *game, int new_x, int new_y);
void    handle_movement(t_game *game, int new_x, int new_y);
int     key_press(int keycode, t_game *game);
int     key_release(int keycode, t_game *game);
void    free_map(char **map);
int     check_path(t_game *game);
int     check_walls(t_game *game);
int     check_components(t_game *game);

#endif
