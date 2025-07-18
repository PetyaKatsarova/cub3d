#include "MLX42/MLX42.h"
#include <stdlib.h>

#define WIDTH  1800
#define HEIGHT 1200
#define TILE_SIZE 50
#define COLOR 0x00FF00FF // RGBA (Green + full alpha)

typedef struct s_game {
	mlx_t*			mlx;
	mlx_image_t*	img;
	int 			x;
	int 			y;
}	t_game;

void	move_square(mlx_key_data_t keydata, void *param)
{
	t_game *g = (t_game *)param;

	if (keydata.action != MLX_PRESS && keydata.action != MLX_REPEAT)
		return;

	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(g->mlx);
	else if (keydata.key == MLX_KEY_RIGHT && g->x + TILE_SIZE + TILE_SIZE/2 < WIDTH)
		g->x += TILE_SIZE;
	else if (keydata.key == MLX_KEY_LEFT && g->x - TILE_SIZE >= 0)
		g->x -= TILE_SIZE;
	else if (keydata.key == MLX_KEY_UP && g->y - TILE_SIZE >= 0)
		g->y -= TILE_SIZE;
	else if (keydata.key == MLX_KEY_DOWN && g->y + TILE_SIZE + TILE_SIZE/2 < HEIGHT)
		g->y += TILE_SIZE;

	g->img->instances[0].x = g->x;
	g->img->instances[0].y = g->y;
}

/** working **
 * cc -Wall -Wextra -Werror -g \
   main.c \
  ../../cub3/lib/MLX42/build/libmlx42.a \
  -I../../cub3/lib/MLX42/include \
  -ldl -lglfw -lm -pthread \
  -o play && ./play
 */

int	main(void)
{
	t_game g;

	g.x = WIDTH / 2 - TILE_SIZE / 2;
	g.y = HEIGHT / 2 - TILE_SIZE / 2;

	g.mlx = mlx_init(WIDTH, HEIGHT, "PLAY", true);
	if (!g.mlx)
		return (1);

	g.img = mlx_new_image(g.mlx, TILE_SIZE, TILE_SIZE);
	if (!g.img)
		return (1);

	for (int y = 0; y < TILE_SIZE; y++)
		for (int x = 0; x < TILE_SIZE; x++)
			mlx_put_pixel(g.img, x, y, COLOR);

	mlx_image_to_window(g.mlx, g.img, g.x, g.y);
	mlx_key_hook(g.mlx, move_square, &g);
	mlx_loop(g.mlx);
	mlx_terminate(g.mlx);
	return (0);
}
