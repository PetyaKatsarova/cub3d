/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   free_parsing.c                                      :+:    :+:           */
/*                                                      +:+                   */
/*   By: jstuhrin <jstuhrin@student.codam.nl>          +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/08/20 12:47:39 by jstuhrin       #+#    #+#                */
/*   Updated: 2025/08/20 12:47:41 by jstuhrin       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/get_input.h"

void	free_parsing(t_parsing *parsing)
{
	int	i;

	if (parsing->scene != NULL)
	{
		i = 0;
		while (parsing->scene[i] != NULL)
		{
			free(parsing->scene[i++]);
		}
		free(parsing->scene);
	}
	if (parsing->test_map != NULL)
	{
		i = 0;
		while (parsing->test_map[i] != NULL)
		{
			free(parsing->test_map[i++]);
		}
		free(parsing->test_map);
	}
	free(parsing->no);
	free(parsing->ea);
	free(parsing->so);
	free(parsing->we);
}
