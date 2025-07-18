#include "../include/cub3d.h"

// TODO: gets input from parser
char *maze_map[] = {
	"111111",
	"100001",
	"101101",
	"100001",
	"111111",
	NULL
};

int	init_data(t_data *d)
{
	d->mlx = mlx_init(WIDTH, HEIGHT, "COOL_CUB3D", true);
	if (!d->mlx)
		return (1);
	d->wall_img = NULL;
	d->floor_img = NULL;
	d->x = WIDTH / 2;
	d->y = HEIGHT / 2;
	d->map = maze_map;
	return (0);
}


/**
 * The player must have:
Field	Meaning
x, y	current position (in pixels or tile coordinates)
dir_x, dir_y	direction vector (unit vector) — where the player looks
plane_x, plane_y	camera plane — defines FOV for raycasting
angle	(optional) rotation angle in radians
speed	movement speed
turn_speed	rotation speed

✅ Recommended: separate t_player struct
c
Copy
Edit
typedef struct s_player {
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;
And add it inside t_data:

c
Copy
Edit
typedef struct s_data {
	mlx_t			*mlx;
	mlx_image_t		*wall_img;
	mlx_image_t		*floor_img;
	char			**map;
	t_player		player;
}	t_data;
 */