/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   make_game_configs_utils.c                           :+:    :+:           */
/*                                                      +:+                   */
/*   By: jstuhrin <jstuhrin@student.codam.nl>          +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/08/20 13:02:25 by jstuhrin       #+#    #+#                */
/*   Updated: 2025/09/11 13:02:27 by jstuhrin       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/get_input.h"

static void	convert_rgb_to_argb(int *rgb_arr, int *trgb)
{
	*trgb = 0;
	*trgb += rgb_arr[0] << 16;
	*trgb += rgb_arr[1] << 8;
	*trgb += rgb_arr[2];
}

void	get_rgb_vals(t_parsing *parsing, t_game_configs *game_configs)
{
	convert_rgb_to_argb(parsing->floor, &game_configs->floor_argb);
	convert_rgb_to_argb(parsing->ceiling, &game_configs->ceiling_argb);
}
