/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   mouse_handler.c                                        :+:    :+:           */
/*                                                      +:+                   */
/*   By: jstuhrin <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/08/20 15:44:11 by jstuhrin       #+#    #+#                */
/*   Updated: 2025/08/20 15:44:13 by jstuhrin       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

int	mouse_handler(t_data *d)
{
	static int	last_x = -1;
	static int	last_y = -1;
	int			curr_x = 0;
	int			curr_y = 0;
	float		delta_x;

	printf("entered mouse handler\n");
	if (d == NULL)
		printf("d == NULL");
	if (d->mlx == NULL)
		printf("d->mlx == NULL\n");
	if (d->win == NULL)
		printf("d->win == NULL\n");
	if (mlx_mouse_get_pos(d->mlx, d->win, &curr_x, &curr_y) == 1)
	{
		printf("last_x: %d, curr_x: %d\n", last_x, curr_x);
		printf("last_y: %d, curr_y: %d\n", last_y, curr_y);
		last_x = curr_x;
		last_y = curr_y;
	}
	return (0);
}