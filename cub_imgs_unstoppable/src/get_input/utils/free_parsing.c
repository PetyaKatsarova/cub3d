#include "../../includes/get_input.h"

void	free_parsing(t_parsing *parsing)
{
	int	i;

	if (parsing->scene != NULL)
	{
		i = 0;
		while (parsing->scene[i] != NULL)
		{
			free(parsing->scene[i]);
			i++;
		}
		free(parsing->scene);
	}
	if (parsing->test_map != NULL)
	{
		i = 0;
		while (parsing->test_map[i] != NULL)
		{
			free(parsing->test_map[i]);
			i++;
		}
		free(parsing->test_map);
	}
	free(parsing->no);
	free(parsing->ea);
	free(parsing->so);
	free(parsing->we);	
}
