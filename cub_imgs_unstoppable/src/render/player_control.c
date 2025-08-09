/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pl_control.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: petya <petya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 15:22:20 by pekatsar          #+#    #+#             */
/*   Updated: 2025/07/27 20:27:45 by petya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

int check_collision(t_data *d, double new_x, double new_y)
{
    float buffer = 10.0; // hardcoded: todo: in header
    
    int step_x_left = (int)((new_x - buffer) / TILE_SIZE);
    int step_y_up = (int)((new_y - buffer) / TILE_SIZE); // start from 0,0: top left
    int step_x_right = (int)((new_x + buffer) / TILE_SIZE);
    int step_y_down = (int)((new_y + buffer) / TILE_SIZE);

    if (step_x_left < 0 || step_x_right >= d->map_cols || step_y_up < 0 || step_y_down >= d->map_rows)
        return 1;

    if (d->map[step_y_up][step_x_left] == '1' || 
        d->map[step_y_up][step_x_right] == '1' ||
        d->map[step_y_down][step_x_left] == '1' ||
        d->map[step_y_down][step_x_right] == '1')
        return 1;

    return 0;
}

// Continuous movement handler - called every frame
void pl_control(t_data *d)
{
    float move_x = 0;
    float move_y = 0;

    if (d->btns.w) // Move forward
    {
        move_x = d->pl->delta_x * SLOW_MOVE;
        move_y = d->pl->delta_y * SLOW_MOVE;
    }
    if (d->btns.s) // Move backward
    {
        move_x = -d->pl->delta_x * SLOW_MOVE;
        move_y = -d->pl->delta_y * SLOW_MOVE;
    }
    if (d->btns.a) // Strafe left
    {
        move_x = d->pl->delta_y * SLOW_MOVE;
        move_y = -d->pl->delta_x * SLOW_MOVE;
    }
    if (d->btns.d) // Strafe right
    {
        move_x = -d->pl->delta_y * SLOW_MOVE;
        move_y = d->pl->delta_x * SLOW_MOVE;
    }

    if (!check_collision(d, d->pl->x + move_x, d->pl->y + move_y))
    {
        d->pl->x += move_x;
        d->pl->y += move_y;
    }

    // Continuous rotation (slower speed)
    if (d->btns.left_arrow) // Rotate left continuously
    {
        d->pl->angle -= 0.01;  // Much slower rotation
        if (d->pl->angle < 0)
            d->pl->angle += 2 * M_PI;
    }
    if (d->btns.right_arrow) // Rotate right continuously
    {
        d->pl->angle += 0.01;  // Much slower rotation
        if (d->pl->angle > 2 * M_PI)
            d->pl->angle -= 2 * M_PI;
    }

    // Update player movement vectors after rotation
    d->pl->delta_x = cos(d->pl->angle) * 5;
    d->pl->delta_y = sin(d->pl->angle) * 5;
}


// Arrow key handler for rotation (can be immediate response)
void handle_arrow_keys(t_data *d, int keycode)
{
    if (keycode == KEY_LEFT) // LEFT ARROW - rotate left
    {
        d->pl->angle -= 0.1;
        if (d->pl->angle < 0)
            d->pl->angle += 2 * M_PI;
        d->pl->delta_x = cos(d->pl->angle) * 5;
        d->pl->delta_y = sin(d->pl->angle) * 5;
    }
    else if (keycode == KEY_RIGHT) // RIGHT ARROW - rotate right
    {
        d->pl->angle += 0.1;
        if (d->pl->angle > 2 * M_PI)
            d->pl->angle -= 2 * M_PI;
        d->pl->delta_x = cos(d->pl->angle) * 5;
        d->pl->delta_y = sin(d->pl->angle) * 5;
    }
}
