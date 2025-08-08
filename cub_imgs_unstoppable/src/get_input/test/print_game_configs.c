#include "../../includes/get_input.h"

static void	print_textures(t_game_configs *game_configs)
{
	printf("NO: %s\n", game_configs->no);
	printf("EA: %s\n", game_configs->ea);
	printf("SO: %s\n", game_configs->so);
	printf("WE: %s\n", game_configs->we);
	printf("\n");
}

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


static void	print_fc(t_parsing *parsing, t_game_configs *game_configs)
{
	printf("F (hex): %s\n", game_configs->floor);
	print_hex_control(parsing->floor);
	printf("C (hex): %s\n", game_configs->ceiling);
	print_hex_control(parsing->ceiling);
	printf("\n");
}

static void	print_bits(int trgb)
{
	unsigned int	mask;
	int				i;

	mask = 1;
	mask <<= 31;
	i = 0;
	while (i < 32)
	{
		if (mask & trgb)
			printf("%d", 1);
		else
			printf("%d", 0);
		mask >>= 1;
		i++;
	}
	printf("\n");
}

static void	print_trgb(t_game_configs *game_configs)
{
	printf("F (trgb int, bits): ");
	print_bits(game_configs->floor_trgb);
	printf("C (trgb int, bits): ");
	print_bits(game_configs->ceiling_trgb);
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
	printf("player_start_orientation: %c\n", game_configs->player_start_orientation);
}

void	print_game_configs(t_parsing *parsing, t_game_configs *game_configs)
{
	printf("\n*****     PRINTING GAME CONFIGS START     *****\n\n");
	print_textures(game_configs);
	print_fc(parsing, game_configs);
	print_trgb(game_configs);
	print_map(game_configs);
	print_map_data(game_configs);
	printf("\n*****     PRINTING GAME CONFIGS END       *****\n");
}