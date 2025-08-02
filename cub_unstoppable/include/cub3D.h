#ifndef cub3D_H
# define cub3D_H

# include <../lib/minilibx_linux/mlx.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h> // for uint32_t
# define _USE_MATH_DEFINES // M_PI
# include <math.h>
# include <stdio.h> // printf

// rows and columns, will be taken from the map
# define WIN_WIDTH      	800 //2000 //800
# define WIN_HEIGHT     	600 //1200 // 600
# define COLS				8 // map with: hardcoded, todo: use form parser!!
# define ROWS				8 // map height
# define TILE_SIZE  		64 // px width and height: balanced performance, fixed
# define MINIMAP_SIZE		350
# define PL_SIZE 			7
# define RAYS_NUM			30
# define DEG_RAD			0.0174533 // one degree in radians

# define WALL_COLOR 		0x800080 // purple 0xBFFF55  // lime
# define EAST_COLOR			0xFFFF00 // yellow 
# define WEST_COLOR			0x0000FF  // blue
# define NORTH_COLOR		0x00FF00  // green
# define SOUTH_COLOR		0xFF0000  // red
# define FLOOR_COLOR 		0xB48E8E // favorite
# define CEILING_COLOR  	0x87CEEB // sky blue
# define PL_COLOR    		0x0d0832ff // dark blue
# define BACKGROUND_COLOR 	0xD3D3D3
# define PURPLE 			0x800080
# define LIME_YELLOW   		0xBFFF00 

# define KEY_LEFT   		65361
# define KEY_RIGHT  		65363

typedef struct  s_btns
{
	int w;
	int a;
	int d;
	int s;
	int	left_arrow;
	int	right_arrow;
} t_btns;


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
	double	radian;
	double	x;
	double	y;
} t_ray;

typedef struct s_texture {
    void    *img;
    char    *addr;
    int     width;
    int     height;
    int     bpp;
    int     line_length;
    int     endian;
} t_texture;

typedef struct s_data {
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bpp; // bits per pixel
	int			line_length;
	int			endian;
	char		**map; // or int?
	t_pl 		*pl;
	t_btns		*btns;
	t_texture 	north_tex;
    t_texture 	south_tex;
    t_texture 	east_tex;
	t_texture   west_tex;
}	t_data;


//void 		button_down(unsigned char key, t_btns *btns);
//void 		button_up(unsigned char key, t_btns *bnts);
int 		init_pl (t_pl *pl, int x, int y, char dir);
int			init_data(t_data *d, t_pl *pl);
void 		set_px(t_data *d, int x, int y, uint32_t color);
void 		horizontal_check(t_ray *ray, t_data *d, float *hx, float *hy);
void 		vertical_check(t_ray *ray, t_data *d, float *vx, float *vy);
void		draw_maze(t_data *d);
void 		draw_minimap(t_data *d);
int			render_frame(t_data *data);
int     	key_press(int keycode, t_data *d);
int     	key_release(int keycode, t_data *d);
void    	pl_control(t_data *d);  // Changed signature - no keycode parameter
void    	handle_arrow_keys(t_data *d, int keycode);
void 		init_textures(t_data *d);
uint32_t 	get_texture_pixel(t_texture *tex, int x, int y);
#endif
