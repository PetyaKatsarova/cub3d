/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: petya <petya@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/23 15:13:27 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/08/06 14:57:22 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

// for free game, destroy mls?
static int close_window(void *param)
{
    (void)param;
    exit(0);
}

/**
 * int mlx_hook(void *win_ptr, int x_event, int x_mask, int (*funct)(), void *param);
 * mlx_key_hook:

Only detects key press (not release)
Simpler: 3 arguments
Good for basic key handling

mlx_hook:

Can handle any X11 event (press, release, mouse, etc.)
More arguments: event type + mask
Better for continuous movement (press/release)
mlx_hook parameters:

win_ptr - Your window
x_event - Event type number:

2 = KeyPress
3 = KeyRelease
17 = Window close


x_mask - Event mask (which events to listen for):

1 = KeyPress mask
2 = KeyRelease mask
0 = No mask (for window close)


funct - Your callback function
param - Data passed to callback

mlx_loop_hook(data.mlx, render_frame, &data);  // Called ~60 times/second
Each frame cycle:

Input handling - Check keys pressed
Update game state - Move player, rotate camera
Clear screen - Fill with black pixels
Render 3D world - Cast rays, draw walls
Render UI - Draw minimap
Display frame - Show completed image
Frame rate = how many complete images per second

60 FPS = smooth
30 FPS = acceptable
Lower = choppy

Your approach:

Continuous rendering - Always drawing new frames
Double buffering - Draw to d->img (invisible), then display all at once
Real-time - Immediate response to input

Frame = one complete 2000x1200 image of your 3D world.
 */
int main(void)
{
    t_data data;
    t_pl    pl;

    if (init_data(&data, &pl)) 
        return (1);
    mlx_loop_hook(data.mlx, render_frame, &data);
    mlx_hook(data.win, 2, 1, key_press, &data); // 
    mlx_hook(data.win, 3, 2, key_release, &data); 
    mlx_hook(data.win, 17, 0, close_window, &data);
    
    mlx_loop(data.mlx);
    return (0);
}