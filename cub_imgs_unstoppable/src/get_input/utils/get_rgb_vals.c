/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   make_game_configs_utils.c                           :+:    :+:           */
/*                                                      +:+                   */
/*   By: jstuhrin <jstuhrin@student.codam.nl>          +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/08/20 13:02:25 by jstuhrin       #+#    #+#                */
/*   Updated: 2025/08/20 13:02:27 by jstuhrin       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/get_input.h"

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

static void	convert_rgb_to_argb(int *rgb_arr, int *trgb)
{
	*trgb = 0;
	*trgb += rgb_arr[0] << 16;
	*trgb += rgb_arr[1] << 8;
	*trgb += rgb_arr[2];
}

void	get_rgb_vals(t_parsing *parsing, t_game_configs *game_configs)
{
	convert_rgb_to_hex(parsing->floor, game_configs->floor);
	convert_rgb_to_hex(parsing->ceiling, game_configs->ceiling);
	convert_rgb_to_argb(parsing->floor, &game_configs->floor_argb);
	convert_rgb_to_argb(parsing->ceiling, &game_configs->ceiling_argb);
}
