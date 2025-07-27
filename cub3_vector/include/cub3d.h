#ifndef CUB3D_H
# define CUB3D_H

# include <../lib/minilibx_linux/mlx.h>
# include <stdlib.h>
# include <unistd.h>
#include <stdint.h> // for uint32_t
#define _USE_MATH_DEFINES // M_PI
#include <math.h>
#include <stdio.h> // printf

// rows and columns, will be taken from the map
// # define WIDTH      	1800
// # define HEIGHT     	1200
# define COLS			24
# define ROWS			34 // chars len(width)
# define TILE_SIZE  	64
#define  pl_SIZE 	7
# define WALL_COLOR 	0xBFFF00  // lime
# define FLOOR_COLOR 	0xB48E8E // favorite
#define pl_COLOR    0x0d0832ff // dark blue

typedef struct s_pl {
	double x;
	double y;
	double angle; // pl viewing angle in radians
	double delta_x; // x component of direction vector
	double delta_y;
	double fov; // field of view
} t_pl;

typedef struct s_ray {
	double 	angle; // ray angle
	double 	distance; // distance to wall
	int		hit_vertical; // 1 if hit vertical wall
	double	x;
	double	y;
} t_ray;

typedef struct s_data {
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bpp; // bits per pixel
	int			line_length;
	int			endian;
	char		**map; // or int?
	t_pl 	*pl;
}	t_data;

int 	init_pl (t_pl *pl, int x, int y, char dir);
int		init_ray();
int		init_data(t_data *d, t_pl *pl);
void	draw_maze(t_data *d);
int		draw_vector(t_data *data);
void	pl_control(t_data *d, int keycode);

#endif
