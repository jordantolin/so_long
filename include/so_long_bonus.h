#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H

# include <unistd.h>
# include <fcntl.h>
# include <mlx.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include "../libraries/libft/libft.h"
# include "../libraries/ft_printf/ft_printf.h"

# define IMG_HEIGHT          32
# define IMG_WIDTH           32

# define WALL               '1'
# define FLOOR              '0'
# define COINS              'C'
# define PLAYER             'P'
# define MAP_EXIT           'E'
# define ENEMY              'X'

# define KEY_W              119
# define KEY_A              97
# define KEY_S              115
# define KEY_D              100

# define KEY_UP             65362
# define KEY_LEFT           65361
# define KEY_RIGHT          65363
# define KEY_DOWN           65364

# define KEY_Q              113
# define KEY_ESC            65307

# define FRONT              1
# define LEFT               2
# define RIGHT              3
# define BACK               4

# define WALL_XPM           "assets/wall.xpm"
# define FLOOR_XPM          "assets/floor.xpm"
# define COINS_XPM          "assets/collectible.xpm"
# define PLAYER_FRONT_XPM   "assets/mandatory_player.xpm"
# define PLAYER_LEFT_XPM    "assets/mandatory_player.xpm"
# define PLAYER_RIGHT_XPM   "assets/mandatory_player.xpm"
# define PLAYER_BACK_XPM    "assets/mandatory_player.xpm"
# define OPEN_EXIT_XPM      "assets/exit.xpm"
# define EXIT_CLOSED_XPM    "assets/exit.xpm"
# define ENEMY_XPM          "assets/enemy.xpm"
# define ENEMY_1_XPM        "assets/enemy_1.xpm"
# define ENEMY_2_XPM        "assets/enemy_2.xpm"
# define ENEMY_3_XPM        "assets/enemy_3.xpm"
# define ENEMY_4_XPM        "assets/enemy_4.xpm"

# define GREEN              "\033[0;32m"
# define RED               "\033[1;31m"
# define GREY              "\033[0;90m"
# define CYAN              "\033[1;96m"
# define RESET             "\033[0m"

# define MAX_ENEMIES 10
# define ENEMY_MOVE_DELAY 50

typedef enum e_bool
{
    false,
    true
}   t_bool;

typedef struct s_position
{
    int x;
    int y;
}   t_position;

typedef struct s_enemy
{
    int x;
    int y;
    int direction;  // 0: up, 1: right, 2: down, 3: left
} t_enemy;

typedef struct s_image
{
    void    *xpm_ptr;
    int     x;
    int     y;
}   t_image;

typedef struct s_map
{
    char        **full;
    int         rows;
    int         columns;
    int         coins;
    int         exit;
    int         players;
    int         num_enemies;
    t_position  player;
    t_enemy     enemies[MAX_ENEMIES];
}   t_map;

typedef struct s_game
{
    void        *mlx_ptr;
    void        *win_ptr;
    int         movements;
    int         player_sprite;
    int         enemy_frame;
    int         frame_count;
    t_map       map;
    t_bool      map_alloc;
    t_image     wall;
    t_image     floor;
    t_image     coins;
    t_image     open_exit;
    t_image     exit_closed;
    t_image     player_front;
    t_image     player_left;
    t_image     player_right;
    t_image     player_back;
    t_image     enemy;
    t_image     enemy_1;
    t_image     enemy_2;
    t_image     enemy_3;
    t_image     enemy_4;
}   t_game;

// Game initialization
void    ft_check_command_line_arguments(int argc, char **argv, t_game *game);
void    ft_init_map(t_game *game, char *argv);
void    ft_init_vars(t_game *game);
void    ft_init_mlx(t_game *game);
void    ft_init_sprites(t_game *game);
t_image ft_new_sprite(void *mlx, char *path, t_game *game);

// Map validation and handling
void    ft_check_map(t_game *game);
void    ft_check_rows(t_game *game);
void    ft_check_columns(t_game *game);
void    ft_count_map_parameters(t_game *game);
void    ft_verify_map_parameters(t_game *game);
void    ft_check_for_empty_line(char *map, t_game *game);

// Rendering functions
int     ft_render_map(t_game *game);
void    ft_identify_sprite(t_game *game, int x, int y);
void    ft_render_player(t_game *game, int x, int y);
void    ft_render_sprite(t_game *game, t_image sprite, int column, int line);
void    ft_print_movements(t_game *game);

// Input handling
int     ft_handle_input(int keysym, t_game *game);
void    ft_player_move(t_game *game, int x, int y, int player_sprite);

// Game state
int     ft_victory(t_game *game);
int     ft_loss(t_game *game);
int     ft_error_msg(char *message, t_game *game);
int     ft_close_game(t_game *game);

// Memory management
void    ft_free_all_allocated_memory(t_game *game);
void    ft_destroy_images(t_game *game);
void    ft_free_map(t_game *game);

// Utility functions
char    *ft_strappend(char **s1, const char *s2);

#endif
