/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   parse_map.c                                         :+:    :+:           */
/*                                                      +:+                   */
/*   By: jstuhrin <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/08/20 12:45:32 by jstuhrin       #+#    #+#                */
/*   Updated: 2025/08/20 12:45:35 by jstuhrin       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/get_input.h"

void	parse_map(t_parsing *parsing, int i)
{
	parsing->map_first_line = i;
	all_chars_legal(parsing, i);
	count_players(parsing, i);
	illegal_empty_lines(parsing, i);
	map_enclosed(parsing, i);
}
