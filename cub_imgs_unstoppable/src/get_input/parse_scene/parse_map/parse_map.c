#include "../../../../include/get_input.h"

void	parse_map(t_parsing *parsing, int i)
{
	parsing->map_first_line = i;
	all_chars_legal(parsing, i);
	count_players(parsing, i);
	illegal_empty_lines(parsing, i);
	map_enclosed(parsing, i);
}
