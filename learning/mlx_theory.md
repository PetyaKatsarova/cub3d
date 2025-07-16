mlx_init() → initialize the connection to X11.

mlx_new_window() → create a new window.

mlx_new_image() → draw an image in memory.

mlx_put_image_to_window() → display image.

mlx_loop() → main loop to keep window open and respond to events.

typedef struct s_data {
    void    *mlx;        // MLX context (needed for everything)
    void    *win;        // Window pointer
    void    *img_wall;   // Wall image
    void    *img_floor;  // Floor image
} t_data;
So data.mlx just holds the pointer returned by mlx_init().