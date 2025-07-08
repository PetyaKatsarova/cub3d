#include "../lib/minilibx_linux/mlx.h"
#include <stdlib.h>

#define WIDTH 800
#define HEIGHT 600
#define SQUARE_SIZE 50
#define COLOR 0x00FF00

typedef struct s_data {
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		x;
	int		y;
}	t_data;

/**
 * data->addr is the start of the image memory buffer (byte pointer).
y * data->line_len:
Moves the pointer to row y (each row is line_len bytes).
x * (bpp / 8):
Moves the pointer x pixels into the row, based on how many bytes per pixel (bpp / 8).
if bpp = 32 → 4 bytes per pixel.
So:
dst = addr + y * row_size + x * pixel_size
→ moves to the memory address of pixel (x, y).
Then:
*(unsigned int*)dst = color;
→ writes 4 bytes (an int) representing the color.
 */
void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;
	dst = data->addr + (y * data->line_len + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
}

void draw_square(t_data *data)
{
    for (int i = 0; i < SQUARE_SIZE; i++)
        for (int j = 0; j < SQUARE_SIZE; j++)
            my_mlx_pixel_put(data, data->x + j, data->y + i, COLOR);
}

int render(t_data *data)
{
    data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
    data->addr = mlx_get_data_addr(data->img, &data->bpp, &data->line_len, &data->endian);
    draw_square(data);
    mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
    mlx_destroy_image(data->mlx, data->img);
    return(0);
}

int	handle_key(int key, t_data *data)
{
	if (key == 65307) // ESC
		exit(0);
	else if (key == 65361)
    {
        if (data->x - 20 >= 0)
            data->x -= 20;
    } // left
	else if (key == 65363)
    {
        if (data->x + 20 + SQUARE_SIZE <= WIDTH)
            data->x += 20;
    } // right
	else if (key == 65362) // up
    {
        if (data->y - 20 >= 0)
            data->y -= 20;
    }
	else if (key == 65364) // down
    {
        if (data->y + 20 + SQUARE_SIZE <= HEIGHT)
            data->y += 20;
    }
	return (0);
}
/**
 *  Use an image buffer for performance
Create an off-screen image (mlx_new_image)
Modify its pixels in memory (mlx_get_data_addr)
Display the image once (mlx_put_image_to_window)
mlx_pixel_put → slow: writes 1 pixel directly
Image buffer → fast: write in memory, then draw all at once
 */

 // export DISPLAY=:0
//  gcc main.c -I ../lib/minilibx_linux -L ../lib/minilibx_linux -lmlx -lX11 -lXext -lm -o my_prog && ./my_prog

int	main(void)
{
	t_data data;

    data.mlx = mlx_init();
    data.win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "Square");
    data.x = WIDTH / 2 - SQUARE_SIZE / 2;
    data.y = HEIGHT / 2 - SQUARE_SIZE / 2;

    mlx_loop_hook(data.mlx, render, &data);
    mlx_key_hook(data.win, handle_key, &data);
    mlx_loop(data.mlx);
	return (0);
}
