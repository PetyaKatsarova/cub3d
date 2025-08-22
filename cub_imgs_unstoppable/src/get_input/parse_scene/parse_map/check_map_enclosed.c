/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   check_map_enclosed.c                                :+:    :+:           */
/*                                                      +:+                   */
/*   By: jstuhrin <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/08/20 12:44:33 by jstuhrin       #+#    #+#                */
/*   Updated: 2025/08/20 12:44:35 by jstuhrin       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/get_input.h"

static bool	floor_or_player(char c)
{
	char	*not_wall;
	int		i;

	not_wall = "0NESW";
	i = 0;
	while (not_wall[i] != '\0')
	{
		if (not_wall[i] == c)
		{
			return (true);
		}
		i++;
	}
	return (false);
}

static void	check_neighbors(t_parsing *parsing, int i, int j)
{
	bool	error;

	error = false;
	if (parsing->test_map[i - 1][j] == ' ')
		error = true;
	if (parsing->test_map[i][j + 1] == ' ')
		error = true;
	if (parsing->test_map[i + 1][j] == ' ')
		error = true;
	if (parsing->test_map[i][j - 1] == ' ')
		error = true;
	if (error == true)
		exit_error_parsing(NOT_ENCLOSED, parsing);
}

void	check_test_map_enclosed(t_parsing *parsing)
{
	int	i;
	int	j;

	i = 1;
	while (i < parsing->test_rows - 1)
	{
		j = 1;
		while (j < parsing->test_columns - 1)
		{
			if (floor_or_player(parsing->test_map[i][j]) == true)
			{
				check_neighbors(parsing, i, j);
			}
			j++;
		}
		i++;
	}
}
