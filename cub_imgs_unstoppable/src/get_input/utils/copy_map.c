/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   copy_map.c                                          :+:    :+:           */
/*                                                      +:+                   */
/*   By: jstuhrin <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/08/20 13:06:01 by jstuhrin       #+#    #+#                */
/*   Updated: 2025/08/20 13:06:03 by jstuhrin       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/get_input.h"

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
		game_configs->map[i] = malloc((parsing->map_columns + 1)
				* sizeof(char));
		if (game_configs->map[i] == NULL)
		{
			free_game_configs(game_configs);
			exit_error_parsing(ALLOC_FAILED, parsing);
		}
		i++;
	}
	game_configs->map[i] = NULL;
}

static void	copy_line(t_parsing *parsing,
	t_game_configs *game_configs,
	int scene_i,
	int map_i)
{
	int	scene_j;
	int	map_j;

	scene_j = parsing->map_first_col;
	map_j = 0;
	while (parsing->scene[scene_i][scene_j] != '\0'
		&& scene_j <= parsing->map_last_col)
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

void	copy_map(t_parsing *parsing, t_game_configs *game_configs)
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
