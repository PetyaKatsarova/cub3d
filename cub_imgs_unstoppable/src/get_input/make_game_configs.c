#include "../../include/get_input.h"

static void	copy_textures(t_parsing *parsing, t_game_configs *game_configs)
{
	game_configs->no = parsing->no;
	game_configs->ea = parsing->ea;
	game_configs->so = parsing->so;
	game_configs->we = parsing->we;
	parsing->no = NULL;
	parsing->ea = NULL;
	parsing->so = NULL;
	parsing->we = NULL;
}

static void	swap(char *hex, int first, int second)
{
	char	temp;

	temp = hex[first];
	hex[first] = hex[second];
	hex[second] = temp;
}

static void	convert_rgb_to_hex(int *rgb_arr, char *hex)
{
	int	i;
	int	j;
	int	current;

	i = 0;
	j = 0;
	hex[j++] = '0';
	hex[j++] = 'x';
	hex[j++] = '0';
	hex[j++] = '0';
	while (i < 3)
	{
		current = rgb_arr[i];
		hex[j] = "0123456789ABCDEF"[current % 16];
		current /= 16;
		j++;
		hex[j] = "0123456789ABCDEF"[current % 16];
		swap(hex, j - 1, j);
		j++;
		i++;
	}
	hex[j] = '\0';
}

static void	convert_rgb_to_trgb(int *rgb_arr, int *trgb)
{
	*trgb = 0;
	*trgb += rgb_arr[0] << 16;
	*trgb += rgb_arr[1] << 8;
	*trgb += rgb_arr[2];
}

static void	get_rgb_vals(t_parsing *parsing, t_game_configs *game_configs)
{
	convert_rgb_to_hex(parsing->floor, game_configs->floor);
	convert_rgb_to_hex(parsing->ceiling, game_configs->ceiling);
	convert_rgb_to_trgb(parsing->floor, &game_configs->floor_trgb);
	convert_rgb_to_trgb(parsing->ceiling, &game_configs->ceiling_trgb);
}

static void	alloc_map(t_parsing *parsing, t_game_configs *game_configs)
{
	int	i;

	game_configs->map = malloc((parsing->map_rows + 1) * sizeof(char *));
	if (game_configs->map == NULL)
	{
		free_game_configs(game_configs);
		exit_error_parsing(ALLOC_FAILED, parsing);
	}
	i = 0;
	while (i < parsing->map_rows)
	{
		game_configs->map[i] = malloc((parsing->map_columns + 1) * sizeof(char));
		if (game_configs->map[i] == NULL)
		{
			free_game_configs(game_configs);
			exit_error_parsing(ALLOC_FAILED, parsing);
		}
		i++;
	}
	game_configs->map[i] = NULL;
}

static void	copy_line(t_parsing *parsing, t_game_configs *game_configs, int scene_i, int map_i)
{
	int	scene_j;
	int	map_j;

	scene_j = parsing->map_first_col;
	map_j = 0;
	while (parsing->scene[scene_i][scene_j] != '\0' && scene_j <= parsing->map_last_col)
	{
		game_configs->map[map_i][map_j] = parsing->scene[scene_i][scene_j];
		map_j++;
		scene_j++;
	}
	while (scene_j <= parsing->map_last_col)
	{
		game_configs->map[map_i][map_j] = ' ';
		map_j++;
		scene_j++;
	}
	game_configs->map[map_i][map_j] = '\0';
}

static void	copy_map(t_parsing *parsing, t_game_configs *game_configs)
{
	int	scene_i;
	int	map_i;

	alloc_map(parsing, game_configs);
	scene_i = parsing->map_first_line;
	map_i = 0;
	while (scene_i <= parsing->map_last_line)
	{
		copy_line(parsing, game_configs, scene_i, map_i);
		scene_i++;
		map_i++;	
	}
}

static bool	is_player(char c)
{
	if (c == 'N')
		return (true);
	if (c == 'E')
		return (true);
	if (c == 'S')
		return (true);
	if (c == 'W')
		return (true);
	return (false);
}

static void	get_map_data(t_parsing *parsing, t_game_configs *game_configs)
{
	int	i;
	int	j;

	game_configs->map_rows = parsing->map_rows;
	game_configs->map_cols = parsing->map_columns;
	i = 0;
	while (i < game_configs->map_rows)
	{
		j = 0;
		while (j < game_configs->map_cols)
		{
			if (is_player(game_configs->map[i][j]) == true)
			{
				game_configs->player_start_row = i;
				game_configs->player_start_col = j;
				game_configs->player_start_orientation = game_configs->map[i][j];
				return ;
			}
			j++;
		}
		i++;
	}
}

t_game_configs	*make_game_configs(t_parsing *parsing)
{
	t_game_configs	*game_configs;

	game_configs = malloc(sizeof(t_game_configs));
	if (game_configs == NULL)
	{
		exit_error_parsing(ALLOC_FAILED, parsing);
	}
	initialize_game_configs(game_configs);
	copy_textures(parsing, game_configs);
	get_rgb_vals(parsing, game_configs);
	copy_map(parsing, game_configs);
	get_map_data(parsing, game_configs);
	return (game_configs);
}
