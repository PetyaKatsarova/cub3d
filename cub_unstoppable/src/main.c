/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: petya <petya@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/23 15:13:27 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/08/02 17:04:53 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

//static int key_hook(int keycode, t_data *d)
//{
//	pl_control(d, keycode);
//	return (0);
//}

//static int	close_window(void *param)
//{
//	(void)param;
//	exit(0);
//}

//int	main(void)
//{
//	t_data	data;
//	t_pl 	pl;

//	if (init_data(&data, &pl)) 
//		return (1);
//	mlx_loop_hook(data.mlx, render_frame, &data);
//	mlx_key_hook(data.win, key_hook, &data);
//	mlx_hook(data.win, 17, 0, close_window, &data); // event code: 17 for x
//	mlx_loop(data.mlx);
//	// todo: clean more
//	return (0);
//}

static int key_hook(int keycode, t_data *d)
{
    handle_arrow_keys(d, keycode);
    return (0);
}

static int close_window(void *param)
{
    (void)param;
    exit(0);
}

int main(void)
{
    t_data data;
    t_pl pl;
    t_btns btns;

    // Initialize btns to all zeros
    btns.w = 0;
    btns.a = 0;
    btns.s = 0;
    btns.d = 0;
	btns.left_arrow = 0;
    btns.right_arrow = 0;
    
    data.btns = &btns;  // Connect btns to data structure

    if (init_data(&data, &pl)) 
        return (1);
    
    // Set up event hooks
    mlx_loop_hook(data.mlx, render_frame, &data);
    mlx_key_hook(data.win, key_hook, &data);  // For arrow keys
    mlx_hook(data.win, 2, 1L<<0, key_press, &data);    // KeyPress event
    mlx_hook(data.win, 3, 1L<<1, key_release, &data);  // KeyRelease event
    mlx_hook(data.win, 17, 0, close_window, &data);    // Close window event
    
    mlx_loop(data.mlx);
    return (0);
}