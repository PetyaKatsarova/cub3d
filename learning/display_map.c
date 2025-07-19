#include "../cub3/lib/minilibx_linux/mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define TILE_SIZE 64

typedef struct s_data {
    void    *mlx;
    void    *win;
    void    *img_wall;
    void    *img_floor;
} t_data;


// only for file map.cub
char **load_map_from_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) return (NULL);

    char **map = malloc(sizeof(char *) * 6); // 5 lines + NULL
    if (!map) return (NULL);

    char line[1024];
    int i = 0;
    while (fgets(line, sizeof(line), file) && i < 5) {
        //strrcspn(const char *s1, const char *s2S) cspn=complement spanreturns the num of chars from s1 untill it reaches first char of s2
        line[strcspn(line, "\n")] = '\0'; // rmv newline
        map[i] = strdup(line);
        i++;
    }
    map[i] = NULL;
    fclose(file);
    return (map);
}

/** 
 * load images from .xpm file:
 * XPM = X PixMap

It’s a plain text image format used in old X11 systems (like in Linux GUI)
.Designed to be easily read by code and embedded in C files
 * int w, f;
→ Temp variables to store width and height of the loaded image.

mlx_xpm_file_to_image(...)
→ This MiniLibX function:

Reads an .xpm image file (wall.xpm / dungeonFloor.xpm)

Converts it to an internal image object usable in MLX

Stores its pointer in data->img_wall or data->img_floor

Sets w and f to image width/height
If wall.xpm is a 64×64 gray block image, then:

data->img_wall
now points to that image in memory, and you can draw it later with:

mlx_put_image_to_window(..., data->img_wall, ...);
command: realpath wall.xpm
 *  */ 
void load_textures(t_data *data)
{
    FILE *f = fopen("brickWall.xpm", "r");
    if (!f) {
        perror("brickWall.xpm fopen");
        exit(1);
    }
    fclose(f);

    int width, height;
    data->img_wall = mlx_xpm_file_to_image(data->mlx, "brickWall.xpm", &width, &height);
    if (!data->img_wall) {
        fprintf(stderr, "Failed to load brickWall.xpm\n");
        exit(1);
    }

    data->img_floor = mlx_xpm_file_to_image(data->mlx, "dungeonFloor.xpm", &width, &height);
    if (!data->img_floor) {
        fprintf(stderr, "Failed to load dungeonFloor.xpm\n");
        exit(1);
    }
}

void draw_map(t_data *data, char **map)
{
    int x, y;
    
    for (y = 0; map[y]; y++) {
        for (x = 0; map[y][x]; x++) {
            void *img = (map[y][x] == '1') ? data->img_wall : data->img_floor;
            mlx_put_image_to_window(data->mlx, data->win, img, x * TILE_SIZE, y * TILE_SIZE);
        }
    }
}

void handle_keys(int keycode, void *param)
{
    t_data *data = (t_data *)param;

    if (keycode == 65307) // ESC
    {
        mlx_destroy_image(data->mlx, data->img_wall);
        mlx_destroy_image(data->mlx, data->img_floor);
        mlx_destroy_window(data->mlx, data->win);
        exit(0);
    }
}

int handle_exit(t_data *data)
{
	mlx_destroy_image(data->mlx, data->img_wall);
	mlx_destroy_image(data->mlx, data->img_floor);
	mlx_destroy_window(data->mlx, data->win);
	exit(0);
	return (0);
}


//  gcc display_map.c -I ../cub3/lib/minilibx_linux -L ../cub3/lib/minilibx_linux -lmlx -lX11 -lXext -lm && ./a.out

int main() {
    t_data data;
    char **map = load_map_from_file("map.cub");
    if (!map)
        return (1);

    data.mlx = mlx_init();
    data.win = mlx_new_window(data.mlx, 6 * TILE_SIZE, 5 * TILE_SIZE, "2dPlay");

    load_textures(&data);
    draw_map(&data, map);
	mlx_key_hook(data.win, handle_keys, &data);
	mlx_hook(data.win, 17, 0, (void *)handle_exit, &data);
    mlx_loop(data.mlx);
    // do we need to destroy sth here for mem protect?

    for (int i = 0; map[i]; i++)
        free(map[i]);
    free(map);
    mlx_destroy_image(data.mlx, data.img_wall);
    mlx_destroy_image(data.mlx, data.img_floor);
    mlx_destroy_window(data.mlx, data.win);

    return (0);
}