/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: petya <petya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 15:13:27 by pekatsar          #+#    #+#             */
/*   Updated: 2025/08/04 18:07:11 by petya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static int close_window(void *param)
{
    (void)param;
    exit(0);
}

int main(void)
{
    t_data data;
    t_pl    pl;
    t_btns btns;

    // btns to all zeros
    init_btns(&btns);
    data.btns = &btns;
    if (init_data(&data, &pl)) 
        return (1);
    
    // event hooks
    mlx_loop_hook(data.mlx, render_frame, &data);
    mlx_hook(data.win, 2, 1L<<0, key_press, &data); 
    mlx_hook(data.win, 3, 1L<<1, key_release, &data); 
    mlx_hook(data.win, 17, 0, close_window, &data);
    
    mlx_loop(data.mlx);
    return (0);
}