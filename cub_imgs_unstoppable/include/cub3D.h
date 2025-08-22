#ifndef cub3D_H
# define cub3D_H

# include "../lib/minilibx_linux/mlx.h"
# include "get_input.h"
# include "get_next_line.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h> // for uint32_t
# define _USE_MATH_DEFINES // M_PI
# include <math.h>
# include <stdio.h> // printf

# define WIN_WIDTH      	1600
# define WIN_HEIGHT     	1000
# define TILE_SIZE  		64 // px width and heightdraw_minimap_backg
# define MINIMAP_SIZE		350
# define PL_SIZE 			7
# define STEP_SIZE 			5
# define VECTOR_LEN			20 // px
# define MOVE_FACTOR			1 //0.4
# define ROTATION_FACTOR	0.05
# define RAYS_NUM			1600
# define DEG_RAD			0.0174533 // one degree in radians

# define MINIMAP_WALL 		0x800080
# define PL_COLOR    		0x0d0832ff
//# define BACKGROUND_COLOR 	0xD3D3D3
# define PURPLE_RAY			0x800080
# define BLACK				0x000000
# define WALL_BUFFER		1

# define KEY_LEFT   		65361
# define KEY_RIGHT  		65363
# define ESC				65307

typedef struct  s_btns
{
	int w;
	int a;
	int d;
	int s;
	int	left_arrow;
	int	right_arrow;
} t_btns;

typedef struct s_wall_info { // for visible wall
	float distance;    // How far away is the wall from pl (in pixels)
	float ray_angle;   // What direction are we looking at (in radians - like degrees but different
	int hit_vertical;  // Is this a vertical wall (1=yes, 0=horizontal wall)
	float hit_x;       // X coordinate where ray hit the wall
	float hit_y;       // Y coordinate where ray hit the wall
	float line_h;      // How tall should we draw this wall on screen?
	float wall_offset; // Which part of the texture to use? (0-64 pixels)
	int wall_top;      // Top pixel of wall on screen
	int wall_bottom;   // Bottom pixel of wall on screen
	uint32_t color;    // What color/texture pixel to draw
} t_wall_info;

typedef struct s_pl {
	double x;
	double y;
	double angle;    // Which direction is player facing? (0 = east, π/2 = north)
	double delta_x;  // How much X changes when moving forward
	double delta_y;  // How much Y changes when moving forward
	double fov;      // How wide can player see? (field of view)
} t_pl;

typedef struct s_ray { // vision ray from pl eye
	double 	angle; // ray angle
	double 	distance; // distance to wall
	int		hit_vertical; // 1 if hit vertical wall
	double	radian;
	double	x;
	double	y;
} t_ray;

typedef struct s_ray_params { // math helper for calc rays
	float h_tan;  // Math value for horizontal calculations (-1/tan)
	float v_tan;  // Math value for vertical calculations (-tan)
	int dof;      // "Depth of field" - how many steps ray took
	float xo;     // How much X changes each step
	float yo;     // How much Y changes each step
	float hx;     // X where ray hit horizontal grid line
	float hy;     // Y where ray hit horizontal grid line
	float vx;     // X where ray hit vertical grid line
	float vy;     // Y where ray hit vertical grid line
} t_ray_params;

typedef struct s_texture {
    void    *img;
    char    *addr;
    int     width;
    int     height;
    int     bpp;  // "Bits per pixel" - how much data per pixel
    int     line_length;
    int     endian; // Byte order
} t_texture;

typedef struct s_line_info {
	float 		x0;
	float 		y0;
	float 		x1;
	float 		y1;
	uint32_t	color;
} t_line_info;

typedef struct s_minimap_params {
	int offset_x;   // X position where minimap starts on screen
	int offset_y;   // Y position where minimap starts on screen
	float scale;    // How much to shrink the big map (0.1 = 10x smaller)
	int start_x;    // Left edge of minimap area
	int start_y;    // Top edge of minimap area
	int end_x;      // Right edge of minimap area
	int end_y;      // Bottom edge of minimap area
	int player_x;
	int player_y;
} t_minimap_params;

typedef struct s_data {
	void			*mlx;
	void			*win;
	void			*img;
	char			*addr;
	int				bpp; // bits per pixel
	int				line_length;
	int				endian;
	int				map_cols;
	int				map_rows;
	int				floor;
	int			    ceiling;
	char			**map;
	t_pl 			*pl;
	t_game_configs *game_configs;
	t_btns			btns;
	t_texture 		north_tex;
    t_texture 		south_tex;
    t_texture 		east_tex;
	t_texture   	west_tex;
	bool			focus;
}	t_data;

  typedef struct s_helper
{
	float	distance_x;
	float	distance_y;
	float	x_increment;
	float	y_increment;
} t_helper;

int 		init_pl (t_pl *pl, t_game_configs *game_configs);
int			init_data(t_data *d, t_pl *pl, t_game_configs *game_configs);
void		init_ray_params(t_ray_params *params);
void 		set_px(t_data *d, int x, int y, uint32_t color);
void 		horizontal_check(t_ray *ray, t_data *d, t_ray_params *ray_params);
void 		vertical_check(t_ray *ray, t_data *d, t_ray_params *ray_params);
void		draw_line(t_data *data, t_line_info *line_info, t_helper *data_placeholder);
double 		normalize_angle(double angle);
void		draw_minimap_background(t_data *d, int offset_x, int offset_y, t_minimap_params *params);
void		draw_minimap_walls(t_data *d, int offset_x, int offset_y, float scale);
void 		draw_minimap(t_data *d);
int			render_frame(t_data *data);
int     	key_press(int keycode, t_data *d);
int     	key_release(int keycode, t_data *d);
int			mouse_handler(int x, int y, t_data *d);
int			focus_in(t_data *d);
int			focus_out(t_data *d);
void    	pl_control(t_data *d);
// src/manipulate_textures.c
int         load_texture(t_data *d, t_texture *tex, char *path);
void 		init_textures(t_data *d, t_game_configs *game_configs);
uint32_t    get_texture_pixel(t_texture *tex, int x, int y);
void        draw_textured_wall(t_data *d, int screen_x, int wall_height, t_texture *tex);
int 		clean_mlx(t_data *d);
// src/render/draw_minimap2.c && 3
void		draw_single_ray(t_data *d, float ray_angle, t_minimap_params *params, int player_x, int player_y);
void		draw_player_dot(t_data *d, int player_x, int player_y, t_minimap_params *params);
void		draw_player_direction(t_data *d, int player_x, int player_y);
// src/render draw_3dmap and 2.c
void		calculate_distances(t_data *d, t_ray_params *params, double *hdist, double *vdist);
void		draw_3d_wall_slice(t_data *d, int x, t_wall_info *wall);
void		setup_viewport_minimap(t_data *d, t_minimap_params *params);

#endif
