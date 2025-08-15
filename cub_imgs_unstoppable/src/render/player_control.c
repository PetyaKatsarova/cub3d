/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   player_control.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: petya <petya@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/23 15:22:20 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/08/15 20:00:33 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

int	check_collision(t_data *d, double new_x, double new_y)
{
	int	step_x_left;
	int	step_y_up;
	int	step_x_right;
	int	step_y_down;

	step_x_left = (int)((new_x - WALL_BUFFER) / TILE_SIZE);
	step_y_up = (int)((new_y - WALL_BUFFER) / TILE_SIZE);
	step_x_right = (int)((new_x + WALL_BUFFER) / TILE_SIZE);
	step_y_down = (int)((new_y + WALL_BUFFER) / TILE_SIZE);
	if (step_x_left < 0 || step_x_right >= d->map_cols
		|| step_y_up < 0 || step_y_down >= d->map_rows)
		return (1);
	if (d->map[step_y_up][step_x_left] == '1'
		|| d->map[step_y_up][step_x_right] == '1'
		|| d->map[step_y_down][step_x_left] == '1'
		|| d->map[step_y_down][step_x_right] == '1')
		return (1);
	return (0);
}

static int	calc_move(t_data *d, float *move_x, float *move_y)
{
	if (d->btns.w)
	{
		*move_x = d->pl->delta_x * SLOW_MOVE;
		*move_y = d->pl->delta_y * SLOW_MOVE;
	}
	if (d->btns.s)
	{
		*move_x = -d->pl->delta_x * SLOW_MOVE;
		*move_y = -d->pl->delta_y * SLOW_MOVE;
	}
	if (d->btns.a)
	{
		*move_x = d->pl->delta_y * SLOW_MOVE;
		*move_y = -d->pl->delta_x * SLOW_MOVE;
	}
	if (d->btns.d)
	{
		*move_x = -d->pl->delta_y * SLOW_MOVE;
		*move_y = d->pl->delta_x * SLOW_MOVE;
	}
	return (0);
}

static int	calc_arrow_btns(t_data *d)
{
	if (d->btns.left_arrow)
	{
		d->pl->angle -= 0.01;
		if (d->pl->angle < 0)
			d->pl->angle += 2 * M_PI;
	}
	if (d->btns.right_arrow)
	{
		d->pl->angle += 0.01;
		if (d->pl->angle > 2 * M_PI)
			d->pl->angle -= 2 * M_PI;
	}
	return (0);
}

void	pl_control(t_data *d)
{
	float	move_x;
	float	move_y;

	move_x = 0;
	move_y = 0;
	calc_move(d, &move_x, &move_y);
	if (!check_collision(d, d->pl->x + move_x, d->pl->y + move_y))
	{
		d->pl->x += move_x;
		d->pl->y += move_y;
	}
	calc_arrow_btns(d);
	d->pl->delta_x = cos(d->pl->angle) * 5;
	d->pl->delta_y = sin(d->pl->angle) * 5;
}

void	handle_arrow_keys(t_data *d, int keycode)
{
	if (keycode == KEY_LEFT)
	{
		d->pl->angle -= 0.1;
		if (d->pl->angle < 0)
			d->pl->angle += 2 * M_PI;
	}
	else if (keycode == KEY_RIGHT)
	{
		d->pl->angle += 0.1;
		if (d->pl->angle > 2 * M_PI)
			d->pl->angle -= 2 * M_PI;
	}
	d->pl->delta_x = cos(d->pl->angle) * 5;
	d->pl->delta_y = sin(d->pl->angle) * 5;
}
