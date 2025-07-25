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
#define  PLAYER_SIZE 	7
# define WALL_COLOR 	0xBFFF00  // lime
# define FLOOR_COLOR 	0xB48E8E // favorite
#define PLAYER_COLOR    0x0d0832ff // dark blue

typedef struct s_player {
	double x;
	double y;
	double angle;
	double delta_x;
	double delta_y;
} t_player;

typedef struct s_data {
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bpp; // bits per pixel
	int			line_length;
	int			endian;
	char		**map;
	t_player 	*player;
}	t_data;

int 	init_player (t_player *player, int x, int y, char dir);
int		init_data(t_data *d, t_player *player);
void	draw_maze(t_data *d);
void	cast_rays(t_data *d);
void	player_control(t_data *d, int keycode);

#endif
