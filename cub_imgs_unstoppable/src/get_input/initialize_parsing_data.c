#include "../../include/get_input.h"

void	initialize_parsing_data(t_parsing *parsing)
{
	int	i;

	parsing->scene = NULL;
	parsing->no = NULL;
	parsing->ea = NULL;
	parsing->so = NULL;
	parsing->we = NULL;
	i = 0;
	while (i < 3)
	{
		parsing->floor[i] = -1;
		parsing->ceiling[i] = -1;
		i++;
	}
	parsing->map_first_line = 0;
	parsing->map_last_line = 0;
	parsing->map_first_col = INT_MAX;
	parsing->map_last_col = 0;
	parsing->map_rows = 0;
	parsing->map_columns = 0;
	parsing->test_map = NULL;
	parsing->test_rows = 0;
	parsing->test_columns = 0;
}
