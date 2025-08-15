/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_minimap.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: petya <petya@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/01 14:51:30 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/08/15 19:45:20 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

/*
** Connects two points with a straight line made of pixels.
*/
void	draw_line(t_data *data, t_line_info *line_info)
{
	float	distance_x;
	float	distance_y;
	int		steps;
	int		i;

	i = 0;
	distance_x = line_info->x1 - line_info->x0;
	distance_y = line_info->y1 - line_info->y0;
	steps = fabs(distance_y);
	if (fabs(distance_x) > fabs(distance_y))
		steps = fabs(distance_x);
	while (++i < steps)
	{
		if (line_info->x0 >= 0 && line_info->x0 < WIN_WIDTH
			&& line_info->y0 >= 0 && line_info->y0 < WIN_HEIGHT)
			set_px(data, (int)line_info->x0,
				(int)line_info->y0, line_info->color);
		line_info->x0 += distance_x / steps;
		line_info->y0 += distance_y / steps;
	}
}

/* keep it in the range [0, 2*PI] */
double	normalize_angle(double angle)
{
	while (angle < 0)
		angle += 2 * M_PI;
	while (angle >= 2 * M_PI)
		angle -= 2 * M_PI;
	return (angle);
}

/*
** Creates a MINMAP_SIZE×MINMAP_SIZE max of d->map_rows and cols pixel rectangle
** Positioned at top-right corner: offset_x, offset_y
** Fills every pixel with BACKGROUND_COLOR (gray)
*/
void	draw_minimap_background(t_data *d, int offset_x,
			int offset_y, t_minimap_params *params)
{
	int	x;
	int	y;

	y = 0;
	while (y < d->map_rows * TILE_SIZE * params->scale)
	{
		x = 0;
		while (x < d->map_cols * TILE_SIZE * params->scale)
		{
			set_px(d, offset_x + x, offset_y + y, BACKGROUND_COLOR);
			x++;
		}
		y++;
	}
}

/*
** Loop through start/end tile and fill each pixel with wall color
*/
static void	draw_wall_block(t_data *d, t_minimap_params *params)
{
	int	x;
	int	y;

	y = params->start_y;
	while (y < params->end_y)
	{
		x = params->start_x;
		while (x < params->end_x)
		{
			if (x >= params->offset_x && y >= params->offset_y)
				set_px(d, x, y, WALL_COLOR);
			x++;
		}
		y++;
	}
}

void	draw_minimap_walls(t_data *d, int offset_x,
			int offset_y, float scale)
{
	int					map_x;
	int					map_y;
	t_minimap_params	params;

	printf("map_cols: %d, map_rows: %d\n", d->map_cols, d->map_rows);
	map_y = 0;
	while (map_y < d->map_rows)
	{
		map_x = 0;
		while (map_x < d->map_cols)
		{
			if (d->map[map_y][map_x] == '1')
			{
				params.offset_x = offset_x;
				params.offset_y = offset_y;
				params.start_x = offset_x + (map_x * TILE_SIZE * scale);
				params.start_y = offset_y + (map_y * TILE_SIZE * scale);
				params.end_x = params.start_x + (int)ceil(TILE_SIZE * scale);
				params.end_y = params.start_y + (int)ceil(TILE_SIZE * scale);
				draw_wall_block(d, &params);
			}
			map_x++;
		}
		map_y++;
	}
}
