#include "../../includes/get_input.h"

void	initialize_game_configs(t_game_configs *game_configs)
{
	game_configs->map = NULL;
	game_configs->no = NULL;
	game_configs->ea = NULL;
	game_configs->so = NULL;
	game_configs->we = NULL;
	game_configs->floor_trgb = 0;
	game_configs->ceiling_trgb = 0;
}
