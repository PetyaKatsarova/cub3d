////
//#include "../include/cub3d.h"

//static void set_px(t_data *d, int x, int y, uint32_t color)
//{
//	if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
//	{
//		uint32_t *pixels = (uint32_t *)d->addr;
//		int index = y * (d->line_length / 4) + x;
//		pixels[index] = color;
//	}
//}

//static void horizontal_check(t_ray *ray, t_data *d, float *hx, float *hy)
//{
//    float aTan = -1/tan(ray->angle);
//    int dof = 0;
//    float xo, yo; // step offsets
    
//    if (ray->angle > M_PI) { // looking up
//        *hy = (((int)d->pl->y>>6)<<6) - 0.0001;
//        *hx = (d->pl->y - *hy) * aTan + d->pl->x;
//        yo = -TILE_SIZE;
//        xo = -yo * aTan;
//    }
//    else if (ray->angle < M_PI) { // looking down
//        *hy = (((int)d->pl->y>>6)<<6) + TILE_SIZE;
//        *hx = (d->pl->y - *hy) * aTan + d->pl->x;
//        yo = TILE_SIZE;
//        xo = -yo * aTan;
//    }
//    else { // looking straight left/right
//        *hx = d->pl->x;
//        *hy = d->pl->y;
//        dof = COLS; // skip loop
//    }
    
//    // Step through horizontal grid lines
//    while (dof < COLS)
//    {
//        int map_x = (int)(*hx) / TILE_SIZE; 
//        int map_y = (int)(*hy) / TILE_SIZE;
        
//        if (map_x >= 0 && map_x < COLS && map_y >= 0 && map_y < ROWS && 
//            d->map[map_y][map_x] == '1')
//        {
//            break; // hit wall - STOP HERE
//        }
//        else {
//            *hx += xo; // step to next grid line
//            *hy += yo;
//            dof++;
//        }
//    }
//}

//static void vertical_check(t_ray *ray, t_data *d, float *vx, float *vy)
//{
//    float nTan = -tan(ray->angle);
//    int dof = 0;
//    float xo, yo; // step offsets
    
//    if (ray->angle > M_PI/2 && ray->angle < 3*M_PI/2) { // looking left
//        *vx = (((int)d->pl->x>>6)<<6) - 0.0001;
//        *vy = (d->pl->x - *vx) * nTan + d->pl->y;
//        xo = -TILE_SIZE;
//        yo = -xo * nTan;
//    }
//    else if (ray->angle < M_PI/2 || ray->angle > 3*M_PI/2) { // looking right
//        *vx = (((int)d->pl->x>>6)<<6) + TILE_SIZE;
//        *vy = (d->pl->x - *vx) * nTan + d->pl->y;
//        xo = TILE_SIZE;
//        yo = -xo * nTan;
//    }
//    else { // looking straight up/down
//        *vx = d->pl->x;
//        *vy = d->pl->y;
//        dof = COLS; // skip loop
//    }
    
//    // Step through vertical grid lines
//    while (dof < COLS)
//    {
//        int map_x = (int)(*vx) / TILE_SIZE;
//        int map_y = (int)(*vy) / TILE_SIZE;
        
//        if (map_x >= 0 && map_x < COLS && map_y >= 0 && map_y < ROWS && 
//            d->map[map_y][map_x] == '1')
//        {
//            break; // hit wall - STOP HERE
//        }
//        else {
//            *vx += xo; // step to next grid line
//            *vy += yo;
//            dof++;
//        }
//    }
//}

//static void draw_3d_wall_slice(t_data *d, int x, float distance, float ray_angle)
//{
//    // Fix fisheye distortion
//    distance = distance * cos(ray_angle - d->pl->angle);
    
//    // Calculate wall height on screen
//    float lineH = (TILE_SIZE * WIN_HEIGHT / 2) / distance;
    
//    // Calculate wall boundaries
//    int wall_top = (WIN_HEIGHT / 2) - (lineH / 2);
//    int wall_bottom = (WIN_HEIGHT / 2) + (lineH / 2);
    
//    // Clamp to screen bounds
//    if (wall_top < 0) wall_top = 0;
//    if (wall_bottom >= WIN_HEIGHT) wall_bottom = WIN_HEIGHT - 1;
    
//    // Draw vertical line (ceiling, wall, floor)
//    for (int y = 0; y < WIN_HEIGHT; y++)
//    {
//        uint32_t color;
        
//        if (y < wall_top)
//            color = 0x87CEEB;      // Sky blue (ceiling)
//        else if (y > wall_bottom)
//            color = 0x8B4513;      // Brown (floor)
//        else
//            color = WALL_COLOR;    // Wall
            
//        set_px(d, x, y, color);
//    }
//}

//static void draw_rays_3d(t_data *d, t_ray *ray) 
//{
//    // Start angle: player angle minus 30 degrees (half FOV)
//    ray->angle = d->pl->angle - (30.0 * DEG_RAD);
    
//    // Normalize angle
//    if (ray->angle < 0)
//        ray->angle += 2 * M_PI;
//    if (ray->angle > 2 * M_PI)
//        ray->angle -= 2 * M_PI;

//    // Cast one ray per screen column for 3D effect
//    for (int x = 0; x < WIN_WIDTH; x++)
//    {
//        float hx, hy; // horizontal hit point
//        float vx, vy; // vertical hit point
        
//        // Check both horizontal and vertical walls
//        horizontal_check(ray, d, &hx, &hy);
//        vertical_check(ray, d, &vx, &vy);
        
//        // Calculate distances
//        float hdist = sqrt((hx - d->pl->x) * (hx - d->pl->x) + (hy - d->pl->y) * (hy - d->pl->y));
//        float vdist = sqrt((vx - d->pl->x) * (vx - d->pl->x) + (vy - d->pl->y) * (vy - d->pl->y));
        
//        float distance;
        
//        // Use closest wall
//        if (hdist < vdist) {
//            distance = hdist;
//        }
//        else {
//            distance = vdist;
//        }
        
//        // Draw 3D wall slice for this column
//        draw_3d_wall_slice(d, x, distance, ray->angle);
        
//        // Increment ray angle for next column
//        ray->angle += (60.0 * DEG_RAD) / WIN_WIDTH;  // 60 degree FOV spread across screen width
        
//        // Normalize angle
//        if (ray->angle < 0)
//            ray->angle += 2 * M_PI;
//        if (ray->angle > 2 * M_PI)
//            ray->angle -= 2 * M_PI;
//    }
//}

//// Bresenham's line algorithm (for 2D debugging)
//static void draw_line(t_data *data, float x0, float y0, float x1, float y1, uint32_t color)
//{
//    float distance_x = x1 - x0;
//    float distance_y = y1 - y0;
//    int steps = (fabs(distance_x) > fabs(distance_y)) ? fabs(distance_x) : fabs(distance_y);
//    float x_increment = distance_x / steps;
//    float y_increment = distance_y / steps;

//    for (int i = 0; i < steps; i++)
//    {
//        if (x0 >= 0 && x0 < WIN_WIDTH && y0 >= 0 && y0 < WIN_HEIGHT)
//            set_px(data, (int)x0, (int)y0, color);
//        x0 += x_increment;
//        y0 += y_increment;
//    }
//}

//// Optional: 2D minimap version (for debugging)
//static void draw_rays_2d(t_data *d, t_ray *ray)
//{
//    ray->angle = d->pl->angle - DEG_RAD * 30;
//    if (ray->angle < 0)
//        ray->angle += 2 * M_PI;
//    if (ray->angle > 2 * M_PI)
//        ray->angle -= 2 * M_PI;

//    // Draw fewer rays for 2D view (just for visualization)
//    for (int r = 0; r < 60; r++)
//    {
//        float hx, hy;
//        float vx, vy;
        
//        horizontal_check(ray, d, &hx, &hy);
//        vertical_check(ray, d, &vx, &vy);
        
//        float hdist = sqrt((hx - d->pl->x) * (hx - d->pl->x) + (hy - d->pl->y) * (hy - d->pl->y));
//        float vdist = sqrt((vx - d->pl->x) * (vx - d->pl->x) + (vy - d->pl->y) * (vy - d->pl->y));
        
//        if (hdist < vdist) {
//            ray->x = hx;
//            ray->y = hy;
//        }
//        else {
//            ray->x = vx;
//            ray->y = vy;
//        }
        
//        // Draw line from player to wall hit
//        draw_line(d, d->pl->x, d->pl->y, ray->x, ray->y, 0xFF0000);
        
//        ray->angle += DEG_RAD;
//        if (ray->angle < 0)
//            ray->angle += 2 * M_PI;
//        if (ray->angle > 2 * M_PI)
//            ray->angle -= 2 * M_PI;
//    }
//}

//int render_frame(t_data *d)
//{
//    // Clear screen to black
//    for (int i = 0; i < WIN_WIDTH * WIN_HEIGHT; i++)
//        ((uint32_t*)d->addr)[i] = 0x000000;
    
//    t_ray ray;
//    ray.angle = d->pl->angle;
    
//    // Choose rendering mode:
//    draw_rays_3d(d, &ray);    // 3D first-person view
//    // draw_maze(d);          // 2D top-down view (comment out for 3D)
//    // draw_rays_2d(d, &ray); // 2D rays (comment out for 3D)
//    // draw_vector(d);        // Player direction vector (comment out for 3D)
    
//    mlx_put_image_to_window(d->mlx, d->win, d->img, 0, 0);
//    return (0);
//}


#include "../include/cub3d.h"

static void set_px(t_data *d, int x, int y, uint32_t color)
{
	if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
	{
		uint32_t *pixels = (uint32_t *)d->addr;
		int index = y * (d->line_length / 4) + x;
		pixels[index] = color;
	}
}



static void horizontal_check(t_ray *ray, t_data *d, float *hx, float *hy)
{
    float aTan = -1/tan(ray->angle);
    int dof = 0;
    float xo, yo; // step offsets
    
    if (ray->angle > M_PI) { // looking up
        *hy = (((int)d->pl->y>>6)<<6) - 0.0001;
        *hx = (d->pl->y - *hy) * aTan + d->pl->x;
        yo = -TILE_SIZE;
        xo = -yo * aTan;
    }
    else if (ray->angle < M_PI) { // looking down
        *hy = (((int)d->pl->y>>6)<<6) + TILE_SIZE;
        *hx = (d->pl->y - *hy) * aTan + d->pl->x;
        yo = TILE_SIZE;
        xo = -yo * aTan;
    }
    else { // looking straight left/right
        *hx = d->pl->x;
        *hy = d->pl->y;
        dof = COLS; // skip loop
    }
    
    // Step through horizontal grid lines
    while (dof < COLS)
    {
        int map_x = (int)(*hx) / TILE_SIZE; 
        int map_y = (int)(*hy) / TILE_SIZE;
        
        if (map_x >= 0 && map_x < COLS && map_y >= 0 && map_y < ROWS && 
            d->map[map_y][map_x] == '1')
        {
            break; // hit wall - STOP HERE
        }
        else {
            *hx += xo; // step to next grid line
            *hy += yo;
            dof++;
        }
    }
}

static void vertical_check(t_ray *ray, t_data *d, float *vx, float *vy)
{
    float nTan = -tan(ray->angle);
    int dof = 0;
    float xo, yo; // step offsets
    
    if (ray->angle > M_PI/2 && ray->angle < 3*M_PI/2) { // looking left
        *vx = (((int)d->pl->x>>6)<<6) - 0.0001;
        *vy = (d->pl->x - *vx) * nTan + d->pl->y;
        xo = -TILE_SIZE;
        yo = -xo * nTan;
    }
    else if (ray->angle < M_PI/2 || ray->angle > 3*M_PI/2) { // looking right
        *vx = (((int)d->pl->x>>6)<<6) + TILE_SIZE;
        *vy = (d->pl->x - *vx) * nTan + d->pl->y;
        xo = TILE_SIZE;
        yo = -xo * nTan;
    }
    else { // looking straight up/down
        *vx = d->pl->x;
        *vy = d->pl->y;
        dof = COLS; // skip loop
    }
    
    // Step through vertical grid lines
    while (dof < COLS)
    {
        int map_x = (int)(*vx) / TILE_SIZE;
        int map_y = (int)(*vy) / TILE_SIZE;
        
        if (map_x >= 0 && map_x < COLS && map_y >= 0 && map_y < ROWS && 
            d->map[map_y][map_x] == '1')
        {
            break; // hit wall - STOP HERE
        }
        else {
            *vx += xo; // step to next grid line
            *vy += yo;
            dof++;
        }
    }
}

static void draw_3d_wall_slice(t_data *d, int x, float distance, float ray_angle)
{
    // Fix fisheye distortion
    distance = distance * cos(ray_angle - d->pl->angle);
    
    // Calculate wall height on screen
    float lineH = (TILE_SIZE * WIN_HEIGHT / 2) / distance;
    
    // Calculate wall boundaries
    int wall_top = (WIN_HEIGHT / 2) - (lineH / 2);
    int wall_bottom = (WIN_HEIGHT / 2) + (lineH / 2);
    
    // Clamp to screen bounds
    if (wall_top < 0) wall_top = 0;
    if (wall_bottom >= WIN_HEIGHT) wall_bottom = WIN_HEIGHT - 1;
    
    // Draw vertical line (ceiling, wall, floor)
    for (int y = 0; y < WIN_HEIGHT; y++)
    {
        uint32_t color;
        
        if (y < wall_top)
            color = 0x87CEEB;      // Sky blue (ceiling) - could add define for this
        else if (y > wall_bottom)
            color = FLOOR_COLOR;   // Floor color from header
        else
            color = WALL_COLOR;    // Wall color from header
            
        set_px(d, x, y, color);
    }
}

static void draw_rays_3d(t_data *d, t_ray *ray) 
{
    // Start angle: player angle minus 30 degrees (half FOV)
    ray->angle = d->pl->angle - (30.0 * DEG_RAD);
    
    // Normalize angle
    if (ray->angle < 0)
        ray->angle += 2 * M_PI;
    if (ray->angle > 2 * M_PI)
        ray->angle -= 2 * M_PI;

    // Cast one ray per screen column for 3D effect
    for (int x = 0; x < WIN_WIDTH; x++)
    {
        float hx, hy; // horizontal hit point
        float vx, vy; // vertical hit point
        
        // Check both horizontal and vertical walls
        horizontal_check(ray, d, &hx, &hy);
        vertical_check(ray, d, &vx, &vy);
        
        // Calculate distances
        float hdist = sqrt((hx - d->pl->x) * (hx - d->pl->x) + (hy - d->pl->y) * (hy - d->pl->y));
        float vdist = sqrt((vx - d->pl->x) * (vx - d->pl->x) + (vy - d->pl->y) * (vy - d->pl->y));
        
        float distance;
        
        // Use closest wall
        if (hdist < vdist) {
            distance = hdist;
        }
        else {
            distance = vdist;
        }
        
        // Draw 3D wall slice for this column
        draw_3d_wall_slice(d, x, distance, ray->angle);
        
        // Increment ray angle for next column
        ray->angle += (60.0 * DEG_RAD) / WIN_WIDTH;  // 60 degree FOV spread across screen width
        
        // Normalize angle
        if (ray->angle < 0)
            ray->angle += 2 * M_PI;
        if (ray->angle > 2 * M_PI)
            ray->angle -= 2 * M_PI;
    }
}

// Bresenham's line algorithm (for 2D debugging)
static void draw_line(t_data *data, float x0, float y0, float x1, float y1, uint32_t color)
{
    float distance_x = x1 - x0;
    float distance_y = y1 - y0;
    int steps = (fabs(distance_x) > fabs(distance_y)) ? fabs(distance_x) : fabs(distance_y);
    float x_increment = distance_x / steps;
    float y_increment = distance_y / steps;

    for (int i = 0; i < steps; i++)
    {
        if (x0 >= 0 && x0 < WIN_WIDTH && y0 >= 0 && y0 < WIN_HEIGHT)
            set_px(data, (int)x0, (int)y0, color);
        x0 += x_increment;
        y0 += y_increment;
    }
}

// 2D minimap in corner
static void draw_minimap(t_data *d)
{
    int minimap_size = 200;  // 200x200 pixels
    int offset_x = WIN_WIDTH - minimap_size - 10;  // Top right corner
    int offset_y = 10;
    float scale = (float)minimap_size / (COLS * TILE_SIZE);  // Scale factor
    
    // Draw minimap background (semi-transparent)
    for (int y = 0; y < minimap_size; y++)
    {
        for (int x = 0; x < minimap_size; x++)
        {
            set_px(d, offset_x + x, offset_y + y, 0x404040);  // Dark gray background
        }
    }
    
    // Draw map walls
    for (int map_y = 0; map_y < ROWS; map_y++)
    {
        for (int map_x = 0; map_x < COLS; map_x++)
        {
            if (d->map[map_y][map_x] == '1')
            {
                int start_x = offset_x + (map_x * TILE_SIZE * scale);
                int start_y = offset_y + (map_y * TILE_SIZE * scale);
                int end_x = start_x + (TILE_SIZE * scale);
                int end_y = start_y + (TILE_SIZE * scale);
                
                // Draw wall block
                for (int y = start_y; y < end_y && y < offset_y + minimap_size; y++)
                {
                    for (int x = start_x; x < end_x && x < offset_x + minimap_size; x++)
                    {
                        if (x >= offset_x && y >= offset_y)
                            set_px(d, x, y, WALL_COLOR);
                    }
                }
            }
        }
    }
    
    // Draw player position
    int player_x = offset_x + (d->pl->x * scale);
    int player_y = offset_y + (d->pl->y * scale);
    
    // Player dot (3x3 pixels)
    for (int y = -2; y <= 2; y++)
    {
        for (int x = -2; x <= 2; x++)
        {
            if (player_x + x >= offset_x && player_x + x < offset_x + minimap_size &&
                player_y + y >= offset_y && player_y + y < offset_y + minimap_size)
                set_px(d, player_x + x, player_y + y, pl_COLOR);  // Player color
        }
    }
    
    // Draw player direction vector
    int dir_end_x = player_x + (cos(d->pl->angle) * 20);
    int dir_end_y = player_y + (sin(d->pl->angle) * 20);
    draw_line(d, player_x, player_y, dir_end_x, dir_end_y, PURPLE);  // Purple direction line
    
    // Draw some rays for visualization
    float ray_angle = d->pl->angle - (30.0 * DEG_RAD);
    for (int i = 0; i < 5; i++)  // Just 5 rays to avoid clutter
    {
        t_ray ray;
        ray.angle = ray_angle;
        
        float hx, hy, vx, vy;
        horizontal_check(&ray, d, &hx, &hy);
        vertical_check(&ray, d, &vx, &vy);
        
        float hdist = sqrt((hx - d->pl->x) * (hx - d->pl->x) + (hy - d->pl->y) * (hy - d->pl->y));
        float vdist = sqrt((vx - d->pl->x) * (vx - d->pl->x) + (vy - d->pl->y) * (vy - d->pl->y));
        
        float hit_x, hit_y;
        if (hdist < vdist) {
            hit_x = hx;
            hit_y = hy;
        } else {
            hit_x = vx;
            hit_y = vy;
        }
        
        int ray_end_x = offset_x + (hit_x * scale);
        int ray_end_y = offset_y + (hit_y * scale);
        
        // Only draw if within minimap bounds
        if (ray_end_x >= offset_x && ray_end_x < offset_x + minimap_size &&
            ray_end_y >= offset_y && ray_end_y < offset_y + minimap_size)
            draw_line(d, player_x, player_y, ray_end_x, ray_end_y, pl_COLOR);  // Player color for rays
        
        ray_angle += (60.0 * DEG_RAD) / 5;  // Spread 5 rays across FOV
    }
}

int render_frame(t_data *d)
{
    // Clear screen to black
    for (int i = 0; i < WIN_WIDTH * WIN_HEIGHT; i++)
        ((uint32_t*)d->addr)[i] = 0x000000;
    
    t_ray ray;
    ray.angle = d->pl->angle;
    
    // Main 3D view (full screen)
    draw_rays_3d(d, &ray);
    
    // Small 2D minimap in top-right corner
    draw_minimap(d);
    
    mlx_put_image_to_window(d->mlx, d->win, d->img, 0, 0);
    return (0);
}
