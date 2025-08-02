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

#include "../include/cub3D.h"


// Key press handler - sets button state to pressed
int key_press(int keycode, t_data *d)
{
    if (keycode == 'q' || keycode == 65307) // ESC or Q
        exit(0);
    
    if (keycode == 'w')
        d->btns->w = 1;
    else if (keycode == 'a')
        d->btns->a = 1;
    else if (keycode == 's')
        d->btns->s = 1;
    else if (keycode == 'd')
        d->btns->d = 1;
	else if (keycode == KEY_LEFT)
        d->btns->left_arrow = 1;
    else if (keycode == KEY_RIGHT)
        d->btns->right_arrow = 1;
    
    return (0);
}

// Key release handler - sets button state to released
int key_release(int keycode, t_data *d)
{
    if (keycode == 'w')
        d->btns->w = 0;
    else if (keycode == 'a')
        d->btns->a = 0;
    else if (keycode == 's')
        d->btns->s = 0;
    else if (keycode == 'd')
        d->btns->d = 0;
	else if (keycode == KEY_LEFT)
        d->btns->left_arrow = 0;
    else if (keycode == KEY_RIGHT)
        d->btns->right_arrow = 0;
    
    return (0);
}

int check_collision(t_data *d, double new_x, double new_y)
{
    float buffer = 8.0; // Stop 8 pixels before wall: hardcoded: todo: in header
    
    // Check multiple points around the player position with buffer
    int map_x1 = (int)((new_x - buffer) / TILE_SIZE);
    int map_y1 = (int)((new_y - buffer) / TILE_SIZE);
    int map_x2 = (int)((new_x + buffer) / TILE_SIZE);
    int map_y2 = (int)((new_y + buffer) / TILE_SIZE);

    // Check bounds with buffer
    if (map_x1 < 0 || map_x2 >= COLS || map_y1 < 0 || map_y2 >= ROWS)
        return 1; // Out of bounds

    // Check all four corners of the player's buffered area
    if (d->map[map_y1][map_x1] == '1' || 
        d->map[map_y1][map_x2] == '1' ||
        d->map[map_y2][map_x1] == '1' ||
        d->map[map_y2][map_x2] == '1')
        return 1; // Wall detected

    return 0;
}

// Continuous movement handler - called every frame
void pl_control(t_data *d)
{
    float move_x = 0;
    float move_y = 0;

    // Player movement based on button states (slower speed)
    if (d->btns->w) // Move forward
    {
        move_x = d->pl->delta_x * 0.2;
        move_y = d->pl->delta_y * 0.2;
    }
    if (d->btns->s) // Move backward
    {
        move_x = -d->pl->delta_x * 0.2;
        move_y = -d->pl->delta_y * 0.2;
    }
    if (d->btns->a) // Strafe left
    {
        move_x = d->pl->delta_y * 0.2;
        move_y = -d->pl->delta_x * 0.2;
    }
    if (d->btns->d) // Strafe right
    {
        move_x = -d->pl->delta_y * 0.2;
        move_y = d->pl->delta_x * 0.2;
    }

    // Check for collisions before moving
    if (!check_collision(d, d->pl->x + move_x, d->pl->y + move_y))
    {
        d->pl->x += move_x;
        d->pl->y += move_y;
    }

    // Continuous rotation (slower speed)
    if (d->btns->left_arrow) // Rotate left continuously
    {
        d->pl->angle -= 0.02;  // Much slower rotation
        if (d->pl->angle < 0)
            d->pl->angle += 2 * M_PI;
    }
    if (d->btns->right_arrow) // Rotate right continuously
    {
        d->pl->angle += 0.02;  // Much slower rotation
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