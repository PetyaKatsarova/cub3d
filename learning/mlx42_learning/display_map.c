#include "MLX42/MLX42.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define TILE_SIZE 64
#define MAP_WIDTH 6
#define MAP_HEIGHT 5
#define WIDTH (MAP_WIDTH * TILE_SIZE)
#define HEIGHT (MAP_HEIGHT * TILE_SIZE)

typedef struct s_data {
	mlx_t* 			mlx;
	mlx_image_t* 	wall_img;
	mlx_image_t* 	floor_img;
	char 			**map;
} t_data;

char **load_map_from_file(const char *filename)
{
	FILE *file = fopen(filename, "r");
	if (!file)
		return NULL;

	char **map = malloc(sizeof(char *) * (MAP_HEIGHT + 1));
	if (!map)
		return NULL;

	char line[1024];
	int i = 0;
	while (fgets(line, sizeof(line), file) && i < MAP_HEIGHT)
	{
		line[strcspn(line, "\n")] = '\0';
		map[i++] = strdup(line);
	}
	map[i] = NULL;
	fclose(file);
	return map;
}

void load_textures(t_data *d)
{
	mlx_texture_t* wall = mlx_load_png("../../cub3/resources/brickWall.png");
	mlx_texture_t* floor = mlx_load_png("../../cub3/resources/dungeonFloor.png");

	if (!wall || !floor)
	{
		fprintf(stderr, "Failed to load .png textures\n");
		exit(EXIT_FAILURE);
	}

	d->wall_img = mlx_texture_to_image(d->mlx, wall);
	d->floor_img = mlx_texture_to_image(d->mlx, floor);

	mlx_delete_texture(wall);
	mlx_delete_texture(floor);

	if (!d->wall_img || !d->floor_img)
	{
		fprintf(stderr, "Failed to convert textures to images\n");
		exit(EXIT_FAILURE);
	}
}

void clean_exit(t_data *d)
{
	if (d->wall_img)
		mlx_delete_image(d->mlx, d->wall_img);
	if (d->floor_img)
		mlx_delete_image(d->mlx, d->floor_img);
	if (d->mlx)
		mlx_terminate(d->mlx);
	if (d->map)
	{
		for (int i = 0; d->map[i]; i++)
			free(d->map[i]);
		free(d->map);
	}
	exit(0);
}

void key_hook(mlx_key_data_t keydata, void *param)
{
	t_data *d = (t_data *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		clean_exit(d);
}

void draw_map(t_data *d)
{
	for (int y = 0; d->map[y]; y++)
	{
		for (int x = 0; d->map[y][x]; x++)
		{
			mlx_image_t *img = (d->map[y][x] == '1') ? d->wall_img : d->floor_img;
			mlx_image_to_window(d->mlx, img, x * TILE_SIZE, y * TILE_SIZE);
		}
	}
}

/**
 * cc -Wall -Wextra -Werror -g \
  display_map.c ../../cub3/lib/MLX42/build/libmlx42.a \
  -I../../cub3/lib/MLX42/include \
  -ldl -lglfw -lm -pthread \
  -o play && ./play

 */
int main(void)
{
	t_data d = {0};

	d.map = load_map_from_file("../map.cub");
	if (!d.map)
		return (1);

	d.mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
	if (!d.mlx)
	{
		free(d.map);
		return (1);
	}

	load_textures(&d);
	draw_map(&d);
	mlx_key_hook(d.mlx, key_hook, &d);
	mlx_loop(d.mlx);
	clean_exit(&d); // fallback in case window closes from outside

	return 0;
}
