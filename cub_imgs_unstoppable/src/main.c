/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: petya <petya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 15:13:27 by pekatsar          #+#    #+#             */
/*   Updated: 2025/08/10 16:22:57 by petya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static int close_window(void *param)
{
    t_data *d;

    d = (t_data *)param;
    clean_mlx(d);
    free_game_configs(d->game_configs);
    exit(0);
}

int main(int argc, char **argv)
{
    t_data data;
    t_pl    pl;
    t_game_configs *game_configs;

    game_configs = get_input(argc, argv);
    if (init_data(&data, &pl, game_configs)) 
        return (1); // todo: did we free all here??
    mlx_loop_hook(data.mlx, render_frame, &data);
    mlx_hook(data.win, 2, 1L<<0, key_press, &data); // 
    mlx_hook(data.win, 3, 1L<<1, key_release, &data); 
    mlx_hook(data.win, 17, 0, close_window, &data);
    mlx_hook(data.win, 6, 1L<<6, mouse_handler, &data);
    mlx_hook(data.win, 9, 1L<<21, focus_in, &data);
    mlx_hook(data.win, 10, 1L<<21, focus_out, &data);
    mlx_loop(data.mlx);
    return (0);
}


/**
 * int mlx_hook(void *win_ptr, int x_event, int x_mask, int (*funct)(), void *param);
Only detects key press (not release)
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

Frame = one complete 2000x1200 image of the 3D world.
 */