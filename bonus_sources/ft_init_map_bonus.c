#include "../include/so_long_bonus.h"
#include "../libraries/get_next_line/get_next_line.h"

static char *read_map_file(int map_fd)
{
    char    *line;
    char    *map_str;
    char    *temp;

    map_str = ft_strdup("");
    if (!map_str)
        ft_error_msg("Error\nMemory allocation failed", NULL);

    while (1)
    {
        line = get_next_line(map_fd);
        if (!line)
            break;
        temp = map_str;
        map_str = ft_strjoin(map_str, line);
        if (!map_str)
        {
            free(line);
            free(temp);
            ft_error_msg("Error\nMemory allocation failed", NULL);
        }
        free(temp);
        free(line);
    }
    return (map_str);
}

void ft_init_enemies(t_game *game)
{
    int i;
    int j;
    int enemy_count;

    enemy_count = 0;
    i = 0;
    while (i < game->map.rows)
    {
        j = 0;
        while (j < game->map.columns)
        {
            if (game->map.full[i][j] == ENEMY && enemy_count < MAX_ENEMIES)
            {
                game->map.enemies[enemy_count].x = j;
                game->map.enemies[enemy_count].y = i;
                game->map.enemies[enemy_count].direction = enemy_count % 4;
                enemy_count++;
            }
            j++;
        }
        i++;
    }
    game->map.num_enemies = enemy_count;
}

void ft_init_map(t_game *game, char *map_path)
{
    int     map_fd;
    char    *map_str;

    map_fd = open(map_path, O_RDONLY);
    if (map_fd == -1)
        ft_error_msg("Error\nFailed to open map file", game);

    map_str = read_map_file(map_fd);
    close(map_fd);

    if (map_str[0] == '\0')
    {
        free(map_str);
        ft_error_msg("Error\nEmpty map file", game);
    }

    ft_check_for_empty_line(map_str, game);
    game->map.full = ft_split(map_str, '\n');
    free(map_str);

    if (!game->map.full)
        ft_error_msg("Error\nMemory allocation failed", game);

    game->map_alloc = true;
    while (game->map.full[game->map.rows])
        game->map.rows++;
    game->map.columns = ft_strlen(game->map.full[0]);

    ft_init_enemies(game);
}

void ft_check_for_empty_line(char *map, t_game *game)
{
    int i;
    int line_start;

    i = 0;
    line_start = 1;
    while (map[i])
    {
        if (map[i] == '\n')
        {
            if (line_start)
            {
                free(map);
                ft_error_msg("Error\nEmpty line in map", game);
            }
            line_start = 1;
        }
        else
            line_start = 0;
        i++;
    }
}
