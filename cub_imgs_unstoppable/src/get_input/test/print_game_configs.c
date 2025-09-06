/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   print_game_configs.c                                :+:    :+:           */
/*                                                      +:+                   */
/*   By: jstuhrin <jstuhrin@student.codam.nl>          +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/08/20 12:46:49 by jstuhrin       #+#    #+#                */
/*   Updated: 2025/08/20 12:46:50 by jstuhrin       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/get_input.h"

static void	print_textures(t_game_configs *game_configs)
{
	printf("NO: %s\n", game_configs->no);
	printf("EA: %s\n", game_configs->ea);
	printf("SO: %s\n", game_configs->so);
	printf("WE: %s\n", game_configs->we);
	printf("\n");
}

static void	print_map(t_game_configs *game_configs)
{
	int	i;

	printf("\nMAP:\n");
	i = 0;
	while (game_configs->map[i] != NULL)
	{
		printf("%s%%\n", game_configs->map[i]);
		i++;
	}
	printf("\n");
}

static void	print_map_data(t_game_configs *game_configs)
{
	printf("rows: %d\n", game_configs->map_rows);
	printf("cols: %d\n", game_configs->map_cols);
	printf("player_start_row: %d\n", game_configs->player_start_row);
	printf("player_start_col: %d\n", game_configs->player_start_col);
	printf("player_start_orientation: %c\n",
		game_configs->player_start_orientation);
}

void	print_game_configs(t_parsing *parsing, t_game_configs *game_configs)
{
	printf("\n*****     PRINTING GAME CONFIGS START     *****\n\n");
	print_textures(game_configs);
	print_fc(parsing, game_configs);
	print_argb(game_configs);
	print_map(game_configs);
	print_map_data(game_configs);
	printf("\n*****     PRINTING GAME CONFIGS END       *****\n");
}
