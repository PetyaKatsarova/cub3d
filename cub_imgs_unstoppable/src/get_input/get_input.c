#include "../../include/get_input.h"

t_game_configs	*get_input(int argc, char **argv)
{
	t_parsing		parsing;
	t_game_configs	*game_configs;

	validate_file(argc, argv);
	initialize_parsing_data(&parsing);
	read_file(argv[1], &parsing);
	parse_scene(&parsing);
	//print_parsing(&parsing);
	game_configs = make_game_configs(&parsing);
	// print_game_configs(&parsing, game_configs);
	free_parsing(&parsing);
	return (game_configs);
}
