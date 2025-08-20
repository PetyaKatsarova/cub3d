/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   make_game_configs.c                                 :+:    :+:           */
/*                                                      +:+                   */
/*   By: jstuhrin <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/08/20 12:42:43 by jstuhrin       #+#    #+#                */
/*   Updated: 2025/08/20 12:42:45 by jstuhrin       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

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
				game_configs->player_start_orientation
					= game_configs->map[i][j];
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
