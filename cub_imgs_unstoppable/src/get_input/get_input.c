/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   get_input.c                                         :+:    :+:           */
/*                                                      +:+                   */
/*   By: jstuhrin <jstuhrin@student.codam.nl>          +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/08/20 12:41:31 by jstuhrin       #+#    #+#                */
/*   Updated: 2025/08/20 12:41:48 by jstuhrin       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/get_input.h"

t_game_configs	*get_input(int argc, char **argv)
{
	t_parsing		parsing;
	t_game_configs	*game_configs;

	validate_file(argc, argv);
	initialize_parsing_data(&parsing);
	read_file(argv[1], &parsing);
	parse_scene(&parsing);
	game_configs = make_game_configs(&parsing);
	free_parsing(&parsing);
	return (game_configs);
}
