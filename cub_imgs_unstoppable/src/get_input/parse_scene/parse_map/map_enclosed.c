#include "../../../../includes/get_input.h"

static void	alloc_test_map(t_parsing *parsing)
{
	int	i;

	parsing->test_map = malloc((parsing->test_rows + 1) * sizeof(char *));
	if (parsing->test_map == NULL)
	{
		exit_error_parsing(ALLOC_FAILED, parsing);
	}
	i = 0;
	while (i < parsing->test_rows)
	{
		parsing->test_map[i] = malloc((parsing->test_columns + 1) * sizeof(char));
		if (parsing->test_map[i] == NULL)
		{
			exit_error_parsing(ALLOC_FAILED, parsing);
		}
		i++;
	}
	parsing->test_map[i] = NULL;
}

static void	initialize_test_map(t_parsing *parsing)
{
	int	i;
	int	j;

	i = 0;
	while (i < parsing->test_rows)
	{
		j = 0;
		while (j < parsing->test_columns)
		{
			parsing->test_map[i][j] = ' ';
			j++;
		}
		parsing->test_map[i][j] = '\0';
		i++;
	}
}

static void	copy_line(t_parsing *parsing, int scene_i, int test_i)
{
	int	scene_j;
	int	test_j;

	scene_j = parsing->map_first_col;
	test_j = 1;
	while (parsing->scene[scene_i][scene_j] != '\0'
		&& scene_j <= parsing->map_last_col)
	{
		parsing->test_map[test_i][test_j] = parsing->scene[scene_i][scene_j];
		scene_j++;
		test_j++;
	}
}

static void	copy_map(t_parsing *parsing)
{
	int	test_i;
	int	scene_i;

	test_i = 1;
	scene_i = parsing->map_first_line;
	while (scene_i <= parsing->map_last_line)
	{
		copy_line(parsing, scene_i, test_i);
		scene_i++;
		test_i++;
	}
}

void	map_enclosed(t_parsing *parsing, int i)
{
	measure_map(parsing, i);
	alloc_test_map(parsing);
	initialize_test_map(parsing);
	copy_map(parsing);
	check_test_map_enclosed(parsing);
}
