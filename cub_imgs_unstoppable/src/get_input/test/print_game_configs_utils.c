/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   print_game_configs_utils.c                          :+:    :+:           */
/*                                                      +:+                   */
/*   By: jstuhrin <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/08/20 13:13:00 by jstuhrin       #+#    #+#                */
/*   Updated: 2025/08/20 13:13:03 by jstuhrin       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/get_input.h"

static void	print_hex_num(int num)
{
	if (num < 16)
	{
		printf("0%X", num);
	}
	else
	{
		printf("%X", num);
	}
}

static void	print_hex_control(int *rgb_arr)
{
	int	i;

	printf("control: ");
	printf("0x00");
	i = 0;
	while (i < 3)
	{
		print_hex_num(rgb_arr[i]);
		i++;
	}
	printf("\n");
}

void	print_fc(t_parsing *parsing, t_game_configs *game_configs)
{
	printf("F (hex): %s\n", game_configs->floor);
	print_hex_control(parsing->floor);
	printf("C (hex): %s\n", game_configs->ceiling);
	print_hex_control(parsing->ceiling);
	printf("\n");
}

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
