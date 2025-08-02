/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   manipulate_textures.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/02 18:03:51 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/08/02 18:08:15 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int load_texture(t_data *d, t_texture *tex, char *filename)
{
    tex->img = mlx_xpm_file_to_image(d->mlx, filename, &tex->width, &tex->height);
    if (!tex->img)
        return (1);
    tex->addr = mlx_get_data_addr(tex->img, &tex->bpp, &tex->line_length, &tex->endian);
    return (0);
}

void init_textures(t_data *d)
{
    load_texture(d, &d->north_tex, "../textures/north_wall.xpm");
    load_texture(d, &d->south_tex, "../textures/south_wall.xpm");
    load_texture(d, &d->east_tex, "../textures/east_wall.xpm");
    load_texture(d, &d->west_tex, "../textures/west_wall.xpm");
}