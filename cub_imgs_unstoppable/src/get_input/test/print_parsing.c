/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   print_parsing.c                                     :+:    :+:           */
/*                                                      +:+                   */
/*   By: jstuhrin <jstuhrin@student.codam.nl>          +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/08/20 12:47:03 by jstuhrin       #+#    #+#                */
/*   Updated: 2025/08/20 12:47:05 by jstuhrin       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/get_input.h"

static void	print_scene(t_parsing *parsing)
{
	int	i;

	printf("SCENE:\n");
	i = 0;
	while (parsing->scene[i] != NULL)
	{
		printf("%s%%\n", parsing->scene[i]);
		i++;
	}
}

static void	print_first_line_rows_columns(t_parsing *parsing)
{
	printf("\nmap_first_line: %d\n", parsing->map_first_line);
	printf("map_rows: %d\n", parsing->map_rows);
	printf("map_columns: %d\n", parsing->map_columns);
}

static void	print_floor_ceiling(t_parsing *parsing)
{
	int	i;

	printf("\nFloor: ");
	i = 0;
	while (i < 3)
	{
		printf("%d", parsing->floor[i]);
		if (i < 2)
			printf(", ");
		i++;
	}
	printf("\n");
	printf("Ceiling: ");
	i = 0;
	while (i < 3)
	{
		printf("%d", parsing->ceiling[i]);
		if (i < 2)
			printf(", ");
		i++;
	}
	printf("\n");
}

static void	print_test_map(t_parsing *parsing)
{
	int	i;

	printf("\nTEST MAP:\n");
	i = 0;
	while (parsing->test_map[i] != NULL)
	{
		printf("%s%%\n", parsing->test_map[i]);
		i++;
	}
}

void	print_parsing(t_parsing *parsing)
{
	printf("\n*****     PRINTING PARSING START     *****\n\n");
	print_scene(parsing);
	print_floor_ceiling(parsing);
	print_first_line_rows_columns(parsing);
	print_test_map(parsing);
	printf("\n*****     PRINTING PARSING END       *****\n\n");
}
