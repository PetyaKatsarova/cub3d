/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   parse_floor_ceiling.c                               :+:    :+:           */
/*                                                      +:+                   */
/*   By: jstuhrin <jstuhrin@student.codam.nl>          +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/08/20 12:43:55 by jstuhrin       #+#    #+#                */
/*   Updated: 2025/08/20 12:43:58 by jstuhrin       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/get_input.h"

static int	parse_rgb(t_parsing *parsing, int i, int j, int *rgb)
{
	int	res;

	if (parsing->scene[i][j] == '0'
		&& (parsing->scene[i][j + 1] >= '0' && parsing->scene[i][j + 1] <= '9'))
	{
		exit_error_parsing(LEADING_ZERO, parsing);
	}
	if (parsing->scene[i][j] < '0' || parsing->scene[i][j] > '9')
	{
		exit_error_parsing(INV_CHAR_FC, parsing);
	}
	res = 0;
	while (parsing->scene[i][j] >= '0' && parsing->scene[i][j] <= '9')
	{
		res = res * 10 + (parsing->scene[i][j] - '0');
		if (res > 255)
			exit_error_parsing(OVERFLOW, parsing);
		j++;
	}
	*rgb = res;
	return (j);
}

static int	traverse_delim(t_parsing *parsing, int i, int j)
{
	j = traverse_space(parsing, i, j);
	if (parsing->scene[i][j] == ',')
	{
		j++;
	}
	else if (parsing->scene[i][j] >= '0' && parsing->scene[i][j] <= '9')
	{
		exit_error_parsing(COMMA, parsing);
	}
	else
	{
		exit_error_parsing(INV_CHAR_FC, parsing);
	}
	j = traverse_space(parsing, i, j);
	return (j);
}

static int	set_up_parsing(t_parsing *parsing, int **rgb_arr, int i, int j)
{
	if (parsing->scene[i][j] == 'C')
	{
		if (parsing->ceiling[0] != -1)
		{
			exit_error_parsing(FC_REDEF, parsing);
		}
		*rgb_arr = parsing->ceiling;
	}
	else if (parsing->scene[i][j] == 'F')
	{
		if (parsing->floor[0] != -1)
		{
			exit_error_parsing(FC_REDEF, parsing);
		}
		*rgb_arr = parsing->floor;
	}
	j++;
	return (j);
}

void	parse_floor_ceiling(t_parsing *parsing, int i, int j)
{
	int	*rgb_arr;

	j = set_up_parsing(parsing, &rgb_arr, i, j);
	if (is_space(parsing->scene[i][j]) == false)
	{
		exit_error_parsing(FC_SPACE, parsing);
	}
	j = traverse_space(parsing, i, j);
	j = parse_rgb(parsing, i, j, &rgb_arr[0]);
	j = traverse_delim(parsing, i, j);
	j = parse_rgb(parsing, i, j, &rgb_arr[1]);
	j = traverse_delim(parsing, i, j);
	j = parse_rgb(parsing, i, j, &rgb_arr[2]);
	j = traverse_space(parsing, i, j);
	if (parsing->scene[i][j] != '\0')
	{
		exit_error_parsing(INV_CHAR_FC, parsing);
	}
}
