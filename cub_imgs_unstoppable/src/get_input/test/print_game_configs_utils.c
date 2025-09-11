/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   print_game_configs_utils.c                          :+:    :+:           */
/*                                                      +:+                   */
/*   By: jstuhrin <jstuhrin@student.codam.nl>          +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/08/20 13:13:00 by jstuhrin       #+#    #+#                */
/*   Updated: 2025/08/20 13:13:03 by jstuhrin       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/get_input.h"

static void	print_bits(int argb)
{
	unsigned int	mask;
	int				i;

	mask = 1;
	mask <<= 31;
	i = 0;
	while (i < 32)
	{
		if (mask & argb)
			printf("%d", 1);
		else
			printf("%d", 0);
		mask >>= 1;
		i++;
	}
	printf("\n");
}

void	print_argb(t_game_configs *game_configs)
{
	printf("F (argb int, bits): ");
	print_bits(game_configs->floor_argb);
	printf("C (argb int, bits): ");
	print_bits(game_configs->ceiling_argb);
}
