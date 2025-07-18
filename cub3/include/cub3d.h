#include "MLX42/MLX42.h"
#include <stdlib.h>
#include <unistd.h>

#define WIDTH  1800
#define HEIGHT 1200
#define TILE_SIZE 50
#define COLOR 0x00FF00FF // RGBA (Green + full alpha)

typedef struct s_data {
	mlx_t			*mlx;
	mlx_image_t		*wall_img;
	mlx_image_t		*floor_img;
	char			**map;
	int				x;
	int				y;
}	t_data;

int init_data(t_data *d);
void draw_maze(t_data *d);
int	load_images(t_data *d);
int main();