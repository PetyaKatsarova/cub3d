/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_manip.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: petya <petya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 13:05:26 by pekatsar          #+#    #+#             */
/*   Updated: 2025/08/10 16:19:00 by petya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"


/* sets button state to pressed */
int key_press(int keycode, t_data *d)
{
    if (keycode == 'q' || keycode == ESC)
    { 
        clean_mlx(d);
        free_game_configs(d->game_configs);
        exit(0);
    }
    if (keycode == 'w')
        d->btns.w = 1;
    else if (keycode == 'a')
        d->btns.a = 1;
    else if (keycode == 's')
        d->btns.s = 1;
    else if (keycode == 'd')
        d->btns.d = 1;
	else if (keycode == KEY_LEFT)
        d->btns.left_arrow = 1;
    else if (keycode == KEY_RIGHT)
        d->btns.right_arrow = 1;
    handle_arrow_keys(d, keycode); 
    return (0);
}

/* sets button state to released */
int key_release(int keycode, t_data *d)
{
    if (keycode == 'w')
        d->btns.w = 0;
    else if (keycode == 'a')
        d->btns.a = 0;
    else if (keycode == 's')
        d->btns.s = 0;
    else if (keycode == 'd')
        d->btns.d = 0;
	else if (keycode == KEY_LEFT)
        d->btns.left_arrow = 0;
    else if (keycode == KEY_RIGHT)
        d->btns.right_arrow = 0;
    return (0);
}