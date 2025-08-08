#include "../../includes/get_input.h"

int	traverse_space(t_parsing *parsing, int i, int j)
{
	while (is_space(parsing->scene[i][j]))
	{
		j++;
	}
	return (j);
}
