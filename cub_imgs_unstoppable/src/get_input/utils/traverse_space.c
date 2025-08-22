/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   traverse_space.c                                    :+:    :+:           */
/*                                                      +:+                   */
/*   By: jstuhrin <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/08/20 12:48:51 by jstuhrin       #+#    #+#                */
/*   Updated: 2025/08/20 12:48:54 by jstuhrin       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/get_input.h"

int	traverse_space(t_parsing *parsing, int i, int j)
{
	while (is_space(parsing->scene[i][j]))
	{
		j++;
	}
	return (j);
}
