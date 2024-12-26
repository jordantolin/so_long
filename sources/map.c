#include "../include/so_long.h"

int	is_valid_char(char c)
{
	return (c == EMPTY || c == WALL || c == COLLECTIBLE ||
			c == EXIT || c == PLAYER);
}

int	check_file_extension(char *filename)
{
	size_t len;

	if (!filename)
		return (0);
	len = ft_strlen(filename);
	if (len < 4)
		return (0);
	return (ft_strncmp(filename + len - 4, ".ber", 4) == 0);
}

void	free_map(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
		free(map[i++]);
	free(map);
}

static int	flood_fill_recursive(char **map, int x, int y, int *collectibles)
{
	int	found_exit;

	found_exit = 0;
	if (!map[y] || map[y][x] == WALL || map[y][x] == 'V')
		return (0);
	if (map[y][x] == EXIT)
	{
		found_exit = 1;
		ft_printf("Debug: Found exit at (%d, %d)\n", x, y);
	}
	if (map[y][x] == COLLECTIBLE)
	{
		(*collectibles)++;
		ft_printf("Debug: Found collectible at (%d, %d), total: %d\n", x, y, *collectibles);
	}
	map[y][x] = 'V';
	found_exit |= flood_fill_recursive(map, x + 1, y, collectibles);
	found_exit |= flood_fill_recursive(map, x - 1, y, collectibles);
	found_exit |= flood_fill_recursive(map, x, y + 1, collectibles);
	found_exit |= flood_fill_recursive(map, x, y - 1, collectibles);
	return (found_exit);
}

int	check_path(t_game *game)
{
	char	**map_copy;
	int		i;
	int		collectibles;
	int		has_exit;

	map_copy = (char **)malloc(sizeof(char *) * (game->map_height + 1));
	if (!map_copy)
		return (0);
	i = -1;
	while (++i < game->map_height)
	{
		map_copy[i] = ft_strdup(game->map[i]);
		if (!map_copy[i])
		{
			free_map(map_copy);
			return (0);
		}
	}
	map_copy[i] = NULL;
	collectibles = 0;
	ft_printf("Debug: Starting flood fill from player position (%d, %d)\n", game->player_x, game->player_y);
	ft_printf("Debug: Total collectibles in map: %d\n", game->collectibles_count);
	has_exit = flood_fill_recursive(map_copy, game->player_x, game->player_y, &collectibles);
	ft_printf("Debug: Found path to exit: %s\n", has_exit ? "yes" : "no");
	ft_printf("Debug: Found collectibles: %d/%d\n", collectibles, game->collectibles_count);
	free_map(map_copy);
	if (!has_exit)
	{
		ft_printf("Error\nNo valid path to exit\n");
		return (0);
	}
	if (collectibles != game->collectibles_count)
	{
		ft_printf("Error\nCannot reach all collectibles\n");
		return (0);
	}
	return (1);
}

int	check_walls(t_game *game)
{
	int	i;
	int	j;

	i = -1;
	while (++i < game->map_height)
	{
		j = -1;
		while (++j < game->map_width)
		{
			if ((i == 0 || i == game->map_height - 1 ||
				j == 0 || j == game->map_width - 1) &&
				game->map[i][j] != WALL)
			{
				ft_printf("Error\n");
				return (0);
			}
		}
	}
	return (1);
}

int	check_components(t_game *game)
{
	int	i;
	int	j;
	int	player_count;
	int	exit_count;

	player_count = 0;
	exit_count = 0;
	game->collectibles_count = 0;
	i = -1;
	while (++i < game->map_height)
	{
		j = -1;
		while (++j < game->map_width)
		{
			if (!is_valid_char(game->map[i][j]))
			{
				ft_printf("Error\n");
				return (0);
			}
			player_count += (game->map[i][j] == PLAYER);
			exit_count += (game->map[i][j] == EXIT);
			game->collectibles_count += (game->map[i][j] == COLLECTIBLE);
		}
	}
	if (player_count != 1 || exit_count != 1 || game->collectibles_count < 1)
	{
		ft_printf("Error\n");
		return (0);
	}
	return (1);
}

int	validate_map(t_game *game)
{
	return (check_walls(game) && check_components(game) && check_path(game));
}

int	read_map(t_game *game, char *filename)
{
	int		fd;
	char	*line;
	char	*temp;
	char	*map_str;
	int		i;
	int		j;

	if (!check_file_extension(filename))
	{
		ft_printf("Error\n");
		return (0);
	}
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Error\n");
		return (0);
	}
	map_str = ft_strdup("");
	while ((line = get_next_line(fd)))
	{
		temp = map_str;
		map_str = ft_strjoin(map_str, line);
		free(temp);
		free(line);
	}
	close(fd);
	game->map = ft_split(map_str, '\n');
	free(map_str);
	if (!game->map)
		return (0);

	game->map_height = 0;
	while (game->map[game->map_height])
	{
		if (game->map_height == 0)
			game->map_width = ft_strlen(game->map[game->map_height]);
		else if ((int)ft_strlen(game->map[game->map_height]) != game->map_width)
		{
			ft_printf("Error\n");
			return (0);
		}
		game->map_height++;
	}

	// Find player position
	i = -1;
	while (++i < game->map_height)
	{
		j = -1;
		while (++j < game->map_width)
		{
			if (game->map[i][j] == PLAYER)
			{
				game->player_x = j;
				game->player_y = i;
				ft_printf("Debug: Found player at (%d, %d)\n", j, i);
				break;
			}
		}
	}

	return (game->map_height > 0);
}

int	load_map(t_game *game, char *filename)
{
	if (!read_map(game, filename))
		return (0);

	if (!validate_map(game))
		return (0);
	return (1);
}