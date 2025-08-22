/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   initialize_game_configs.c                           :+:    :+:           */
/*                                                      +:+                   */
/*   By: jstuhrin <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/08/20 12:42:04 by jstuhrin       #+#    #+#                */
/*   Updated: 2025/08/20 12:42:07 by jstuhrin       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/get_input.h"

void	initialize_game_configs(t_game_configs *game_configs)
{
	game_configs->map = NULL;
	game_configs->no = NULL;
	game_configs->ea = NULL;
	game_configs->so = NULL;
	game_configs->we = NULL;
	game_configs->floor_argb = 0;
	game_configs->ceiling_argb = 0;
}
