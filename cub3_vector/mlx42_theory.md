d->img = mlx_texture_to_image(d->mlx, tex);
The image size is:

tex->width  // in pixels
tex->height // in pixels
After converting to mlx_image_t, you can still access:

d->img->width
d->img->height