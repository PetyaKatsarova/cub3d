/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   manipulate_textures.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/02 18:03:51 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/09/11 17:54:31 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	clean_texture(t_data *d, t_texture *tex)
{
	(void)d;
	(void)tex;
	if (tex->img)
	{
		mlx_destroy_image(d->mlx, tex->img);
		tex->img = NULL;
		tex->addr = NULL;
	}
	write(2, "Error: Failed to load texture\n", 30);
}

int	load_texture(t_data *d, t_texture *tex, char *path)
{
	(void)path;
	(void)d;
	(void)path;
	tex->img = mlx_xpm_file_to_image(d->mlx,
			path, &tex->width, &tex->height);
	if (!tex->img)
		return (1);
	tex->addr = mlx_get_data_addr(tex->img,
			&tex->bpp, &tex->line_length, &tex->endian);
	if (!tex->addr)
		return (1);
	return (0);
}

int	init_textures(t_data *d, t_game_configs *game_configs)
{
	if (load_texture(d, &d->north_tex, game_configs->no))
		return (clean_texture(d, &d->north_tex), 1);
	if (load_texture(d, &d->south_tex, game_configs->so))
	{
		clean_texture(d, &d->north_tex);
		return (clean_texture(d, &d->south_tex), 1);
	}
	if (load_texture(d, &d->east_tex, game_configs->ea))
	{
		clean_texture(d, &d->north_tex);
		clean_texture(d, &d->south_tex);
		return (clean_texture(d, &d->east_tex), 1);
	}
	if (load_texture(d, &d->west_tex, game_configs->we))
	{
		clean_texture(d, &d->north_tex);
		clean_texture(d, &d->south_tex);
		clean_texture(d, &d->east_tex);
		return (clean_texture(d, &d->west_tex), 1);
	}
	return (0);
}

/*
	tex->addr is the start of the texture’s pixel data in memory.
	Each row of the image is tex->line_length bytes long.
	To find the pixel at (x, y):
	Move down y rows: y * tex->line_length bytes.
	Move right x columns: x * (tex->bpp / 8) bytes.
	tex->bpp is bits per pixel, so divide by 8 to get bytes per pixel.
	Add these together to get the memory address of the pixel.
*/
uint32_t	get_texture_pixel(t_texture *tex, int x, int y)
{
	char	*pixel;

	if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
		return (0);
	pixel = tex->addr + (y * tex->line_length + x * (tex->bpp / 8));
	return (*(uint32_t *)pixel);
}

void	draw_textured_wall(t_data *d, int screen_x,
			int wall_height, t_texture *tex)
{
	int			wall_start;
	int			y;
	int			tex_y;
	int			tex_x;
	uint32_t	color;

	wall_start = (WIN_HEIGHT - wall_height) / 2;
	tex_x = screen_x % tex->width;
	y = wall_start;
	while (y < wall_start + wall_height)
	{
		tex_y = ((y - wall_start) * tex->height) / wall_height;
		color = get_texture_pixel(tex, tex_x, tex_y);
		set_px(d, screen_x, y, color);
		y++;
	}
}
