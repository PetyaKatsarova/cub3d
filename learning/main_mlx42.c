#include "MLX42/MLX42.h"
#include <stdlib.h>
#include <stdio.h>

#define WIDTH 800
#define HEIGHT 600
#define SQUARE_SIZE 50
#define COLOR 0x00FF00FF // ARGB format

typedef struct s_data {
	mlx_t		*mlx;
	mlx_image_t	*img;
	int			x;
	int			y;
}	t_data;

void	draw_square(t_data *data)
{
	for (int i = 0; i < SQUARE_SIZE; i++)
		for (int j = 0; j < SQUARE_SIZE; j++)
		{
			int px = data->x + j;
			int py = data->y + i;
			if (px >= 0 && px < WIDTH && py >= 0 && py < HEIGHT)
				mlx_put_pixel(data->img, px, py, COLOR);
		}
}

void	clear_image(mlx_image_t *img)
{
	for (uint32_t y = 0; y < img->height; ++y)
		for (uint32_t x = 0; x < img->width; ++x)
			mlx_put_pixel(img, x, y, 0x000000FF); // black
}

void	handle_keys(t_data *data)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT) && data->x - 20 >= 0)
		data->x -= 20;
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT) && data->x + 20 + SQUARE_SIZE <= WIDTH)
		data->x += 20;
	if (mlx_is_key_down(data->mlx, MLX_KEY_UP) && data->y - 20 >= 0)
		data->y -= 20;
	if (mlx_is_key_down(data->mlx, MLX_KEY_DOWN) && data->y + 20 + SQUARE_SIZE <= HEIGHT)
		data->y += 20;
}

void	render(void *param)
{
	t_data *data = (t_data *)param;
	clear_image(data->img);
	handle_keys(data);
	draw_square(data);
}

int	main(void)
{
	t_data	data;

	data.mlx = mlx_init(WIDTH, HEIGHT, "Square", true);
	if (!data.mlx)
		return (EXIT_FAILURE);
	data.img = mlx_new_image(data.mlx, WIDTH, HEIGHT);
	if (!data.img || mlx_image_to_window(data.mlx, data.img, 0, 0) < 0)
		return (EXIT_FAILURE);
	data.x = WIDTH / 2 - SQUARE_SIZE / 2;
	data.y = HEIGHT / 2 - SQUARE_SIZE / 2;

	mlx_loop_hook(data.mlx, render, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	return (EXIT_SUCCESS);
}
