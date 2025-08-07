///* ************************************************************************** */
///*                                                                            */
///*                                                        ::::::::            */
///*   manipulate_textures.c                              :+:    :+:            */
///*                                                     +:+                    */
///*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
///*                                                   +#+                      */
///*   Created: 2025/08/02 18:03:51 by pekatsar      #+#    #+#                 */
///*   Updated: 2025/08/06 14:26:31 by pekatsar      ########   odam.nl         */
///*                                                                            */
///* ************************************************************************** */

//#include "../include/cub3D.h"

//int load_texture(t_data *d, t_texture *tex, char *filename)
//{
//    printf("Loading texture: %s\n", filename); // Debug print
    
//    tex->img = mlx_xpm_file_to_image(d->mlx, filename, &tex->width, &tex->height);
//    if (!tex->img)
//    {
//        printf("Failed to load texture: %s\n", filename);
//        return (1);
//    }
    
//    printf("Texture loaded: %dx%d\n", tex->width, tex->height); // Debug print
    
//    tex->addr = mlx_get_data_addr(tex->img, &tex->bpp, &tex->line_length, &tex->endian);
//    if (!tex->addr)
//    {
//        printf("Failed to get texture data addr\n");
//        return (1);
//    }
    
//    return (0);
//}

//// void init_textures(t_data *d)
//// {
////     load_texture(d, &d->north_tex, "../textures/north_wall.xpm");
////     load_texture(d, &d->south_tex, "../textures/south_wall.xpm");
////     load_texture(d, &d->east_tex, "../textures/east_wall.xpm");
////     load_texture(d, &d->west_tex, "../textures/west_wall.xpm");
//// }

//void init_textures(t_data *d)
//{
//    if (load_texture(d, &d->north_tex, "../textures/north_wall.xpm"))
//        printf("ERROR: Failed to load north texture\n");
//    else
//        printf("SUCCESS: North texture loaded\n");
        
//    if (load_texture(d, &d->south_tex, "../textures/south_wall.xpm"))
//        printf("ERROR: Failed to load south texture\n");
//    else
//        printf("SUCCESS: South texture loaded\n");
        
//    if (load_texture(d, &d->east_tex, "../textures/east_wall.xpm"))
//        printf("ERROR: Failed to load east texture\n");
//    else
//        printf("SUCCESS: East texture loaded\n");
        
//    if (load_texture(d, &d->west_tex, "../textures/west_wall.xpm"))
//        printf("ERROR: Failed to load west texture\n");
//    else
//        printf("SUCCESS: West texture loaded\n");
//}

//uint32_t get_texture_pixel(t_texture *tex, int x, int y)
//{
//    if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
//        return (0);
    
//    char *pixel = tex->addr + (y * tex->line_length + x * (tex->bpp / 8));
//    return (*(uint32_t*)pixel);
//}


#include "../include/cub3D.h"

// Load texture from file (return int for error checking)
int load_texture(t_data *d, t_texture *tex, char *path)
{
    tex->img = mlx_xpm_file_to_image(d->mlx, path, &tex->width, &tex->height);
    if (!tex->img)
        return (1);
    tex->addr = mlx_get_data_addr(tex->img, &tex->bpp, &tex->line_length, &tex->endian);
    return (0);
}

void init_textures(t_data *d)
{
    load_texture(d, &d->north_tex, "textures/north_wall.xpm");
    load_texture(d, &d->south_tex, "textures/south_wall.xpm");
    load_texture(d, &d->east_tex, "textures/east_wall.xpm");
    load_texture(d, &d->west_tex, "textures/west_wall.xpm");
}

/**
 * Find the pixel in memory:char *pixel = tex->addr + (calculation);
 * example: Texture is a 64x64 brick wall image
get_texture_pixel(brick_texture, 10, 20) Returns: 0x8B4513 (brown color of that brick pixel)
Texture = big box of colored pixels
Function = "go to box, find pixel at position (x,y), tell me what color it is"
Return value = the actual color (red, blue, brown, etc.) as a number
 */
uint32_t get_texture_pixel(t_texture *tex, int x, int y)
{
    if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
        return (0);
    char *pixel = tex->addr + (y * tex->line_length + x * (tex->bpp / 8));
    return *(uint32_t*)pixel;
}

/**
 *  get the px val of the texture(xmp file) and display that color on the given location on the screen
 */
void	draw_textured_wall(t_data *d, int screen_x, int wall_height, t_texture *tex)
{
    int			wall_start;
    int			y;
    int			tex_y;
    int			tex_x;
    uint32_t	color;

    wall_start = (WIN_HEIGHT - wall_height) / 2;
    tex_x = screen_x % tex->width;  // Simple texture mapping
    y = wall_start;
    while (y < wall_start + wall_height)
    {
        tex_y = ((y - wall_start) * tex->height) / wall_height;
        color = get_texture_pixel(tex, tex_x, tex_y);
        set_px(d, screen_x, y, color);
        y++;
    }
}
