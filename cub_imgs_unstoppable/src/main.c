/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/15 20:01:49 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/08/23 14:50:20 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static int	close_window(void *param)
{
	t_data	*d;

	d = (t_data *)param;
	clean_mlx(d);
	free_game_configs(d->game_configs);
	exit(0);
}

/*
2: keyPress, 3: keyRelease, 17: DestroyNotify(x btn, window close)
The third argument is the event mask (which bits to listen for).
Example:
1L<<0 = KeyPress
1L<<1 = KeyRelease
1L<<6 = MotionNotify (mouse move)
1L<<21 = FocusIn/FocusOut
0 = No mask needed (for DestroyNotify, event 17)
*/
int	main(int argc, char **argv)
{
	t_data			data;
	t_pl			pl;
	t_game_configs	*game_configs;

    game_configs = get_input(argc, argv);
    if (init_data(&data, &pl, game_configs))
    {
        free_game_configs(game_configs);
        return (1);
    }
    mlx_loop_hook(data.mlx, render_frame, &data);
    mlx_hook(data.win, 2, 1L<<0, key_press, &data); // 
    mlx_hook(data.win, 3, 1L<<1, key_release, &data); 
    mlx_hook(data.win, 17, 0, close_window, &data);
    //mlx_hook(data.win, 6, 1L<<6, mouse_handler, &data);
    //mlx_hook(data.win, 9, 1L<<21, focus_in, &data);
    //mlx_hook(data.win, 10, 1L<<21, focus_out, &data);
    mlx_loop(data.mlx);
    return (0);
}
