/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   free_game_configs.c                                 :+:    :+:           */
/*                                                      +:+                   */
/*   By: jstuhrin <jstuhrin@student.codam.nl>          +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/08/20 12:49:08 by jstuhrin       #+#    #+#                */
/*   Updated: 2025/09/11 12:49:10 by jstuhrin       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/get_input.h"

void	free_game_configs(t_game_configs *game_configs)
{
	int	i;

	if (game_configs->map != NULL)
	{
		i = 0;
		while (game_configs->map[i] != NULL)
		{
			free(game_configs->map[i]);
			i++;
		}
		free(game_configs->map);
	}
	free(game_configs->no);
	free(game_configs->ea);
	free(game_configs->so);
	free(game_configs->we);
	free(game_configs);
}
