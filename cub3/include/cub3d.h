#ifndef CUB3D_H
# define CUB3D_H

# include <../lib/minilibx_linux/mlx.h>
# include <stdlib.h>
# include <unistd.h>
#include <stdint.h> // for uint32_t
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h> // printf

# define WIDTH      	1800
# define HEIGHT     	1200
# define TILE_SIZE  	50
# define  PL_SIZE 	7
# define WALL_COLOR 	0xBFFF00  // lime
# define FLOOR_COLOR 	0xB48E8E // favorite
# define pl_COLOR    0x0d0832ff // dark blue
# define KEY_ESC    65307
# define KEY_LEFT   65361
# define KEY_RIGHT  65363
# define KEY_UP     65362
# define KEY_DOWN   65364

typedef struct s_pl {
	double x;
	double y;
	double angle;
	double delta_x;
	double delta_y;
} t_pl;

typedef struct s_data {
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bpp; // bits per pixel
	int			line_length;
	int			endian;
	char		**map;
	t_pl 	*pl;
}	t_data;

int 	init_pl (t_pl *pl, int x, int y, char dir);
int		init_data(t_data *d, t_pl *pl);
void	draw_maze(t_data *d);
void	cast_rays(t_data *d);
void	pl_control(t_data *d, int keycode);

#endif
