#include "../../../../include/get_input.h"

static bool	has_line_only_spaces(char *line)
{
	int		i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] != ' ')
		{
			return (false);
		}
		i++;
	}
	return (true);
}

static void	find_first_line(t_parsing *parsing, int i)
{
	while (parsing->scene[i] != NULL && parsing->scene[i][0] != '\0')
	{
		if (has_line_only_spaces(parsing->scene[i]) == false)
		{
			parsing->map_first_line = i;
			break ;
		}
		i++;
	}
}

static void	find_last_line(t_parsing *parsing)
{
	int	i;

	i = parsing->map_first_line;
	while (parsing->scene[i] != NULL && parsing->scene[i][0] != '\0')
	{
		if (has_line_only_spaces(parsing->scene[i]) == false)
		{
			parsing->map_last_line = i;
		}
		i++;
	}
}

static void	find_first_last_col(t_parsing *parsing)
{
	int	i;
	int	j;

	i = parsing->map_first_line;
	while (i <= parsing->map_last_line)
	{
		j = 0;
		while (parsing->scene[i][j] != '\0')
		{
			if (parsing->scene[i][j] != ' ')
			{
				if (j < parsing->map_first_col)
				{
					parsing->map_first_col = j;
				}
				if (j > parsing->map_last_col)
				{
					parsing->map_last_col = j;
				}
			}
			j++;
		}
		//printf("%s\n", parsing->scene[i]);
		i++;
	}
}

void	measure_map(t_parsing *parsing, int i)
{
	find_first_line(parsing, i);
	find_last_line(parsing);
	parsing->map_rows = parsing->map_last_line - parsing->map_first_line + 1;
	//printf("first line: %d\nlast line: %d\nnum rows: %d\n", parsing->map_first_line, parsing->map_last_line, parsing->map_rows);
	find_first_last_col(parsing);
	parsing->map_columns = parsing->map_last_col - parsing->map_first_col + 1;
	//printf("first col: %d\nlast col: %d\nnum cols: %d\n", parsing->map_first_col, parsing->map_last_col, parsing->map_columns);
	parsing->test_rows = parsing->map_rows + 2;
	parsing->test_columns = parsing->map_columns + 2;
}