#include "MLX42/MLX42.h"
#include <stdlib.h>
#include <unistd.h>

#define WIDTH  		1800
#define HEIGHT 		1200
#define TILE_SIZE	50
#define WALL		#BFFF00FF // lime
#define FLOOR		#B48E8EFF // Mmy fav

typedef struct s_data {
	mlx_t			*mlx;
	char			**map;
	int				player_x;
	int				player_y;
}	t_data;

int init_data(t_data *d);
void draw_maze(t_data *d);
int main();

/**
 * so long tutorial
 * typedef struct s_data
{
	void		*mlx_ptr; // MLX pointer
	void		*win_ptr; // MLX window pointer
	void		*textures[5]; // MLX image pointers (on the stack)
	t_map		*map; // Map pointer (contains map details - preferably kept on the stack)
}	t_data;

int on_destroy(t_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	exit(0);
	return (0);
}
 */