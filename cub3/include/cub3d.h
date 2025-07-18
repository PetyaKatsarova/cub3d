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


int main();