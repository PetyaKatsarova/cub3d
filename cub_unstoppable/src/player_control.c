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

//static int ft_strlen(const char *s)
//{
//	int len = 0;
//	while (s[len])
//		len++;
//	return len;
//}	



//void pl_control(t_data *d, int keycode) {
//    if (keycode == 'q' || keycode == 65307) // ESC or Q
//        exit(0);
//    else if (keycode == KEY_LEFT) // LEFT ARROW - rotate left
//    {
//        d->pl->angle -= 0.1;
//        if (d->pl->angle < 0)
//            d->pl->angle += 2 * M_PI;
//        d->pl->delta_x = cos(d->pl->angle) * 5;
//        d->pl->delta_y = sin(d->pl->angle) * 5;
//    }
//    else if (keycode == KEY_RIGHT) // RIGHT ARROW - rotate right
//    {
//        d->pl->angle += 0.1;
//        if (d->pl->angle > 2 * M_PI)
//            d->pl->angle -= 2 * M_PI;
//        d->pl->delta_x = cos(d->pl->angle) * 5;
//        d->pl->delta_y = sin(d->pl->angle) * 5;
//    }
//    else if (keycode == 'w') // move forward
//    {
//        d->pl->x += d->pl->delta_x;
//        d->pl->y += d->pl->delta_y;
//    }
//    else if (keycode == 's') // move backward
//    {
//        d->pl->x -= d->pl->delta_x;
//        d->pl->y -= d->pl->delta_y;
//    }
//    else if (keycode == 'a') // strafe left
//    {
//        d->pl->x += d->pl->delta_y;  // perpendicular to forward
//        d->pl->y -= d->pl->delta_x;
//    }
//    else if (keycode == 'd') // strafe right
//    {
//        d->pl->x -= d->pl->delta_y;  // perpendicular to forward
//        d->pl->y += d->pl->delta_x;
//    }
//}




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

// Continuous movement handler - called every frame
void pl_control(t_data *d)
{
    // Player movement based on button states (slower speed)
    if (d->btns->w) // Move forward
    {
        d->pl->x += d->pl->delta_x * 0.2;  // Much slower
        d->pl->y += d->pl->delta_y * 0.2;
    }
    if (d->btns->s) // Move backward
    {
        d->pl->x -= d->pl->delta_x * 0.2;
        d->pl->y -= d->pl->delta_y * 0.2;
    }
    if (d->btns->a) // Strafe left
    {
        d->pl->x += d->pl->delta_y * 0.2;  // perpendicular to forward
        d->pl->y -= d->pl->delta_x * 0.2;
    }
    if (d->btns->d) // Strafe right
    {
        d->pl->x -= d->pl->delta_y * 0.2;  // perpendicular to forward
        d->pl->y += d->pl->delta_x * 0.2;
    }
    
    // Continuous rotation (slower speed)
    if (d->btns->left_arrow) // Rotate left continuously
    {
        d->pl->angle -= 0.03;  // Much slower rotation
        if (d->pl->angle < 0)
            d->pl->angle += 2 * M_PI;
        d->pl->delta_x = cos(d->pl->angle) * 5;
        d->pl->delta_y = sin(d->pl->angle) * 5;
    }
    if (d->btns->right_arrow) // Rotate right continuously
    {
        d->pl->angle += 0.03;  // Much slower rotation
        if (d->pl->angle > 2 * M_PI)
            d->pl->angle -= 2 * M_PI;
        d->pl->delta_x = cos(d->pl->angle) * 5;
        d->pl->delta_y = sin(d->pl->angle) * 5;
    }
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