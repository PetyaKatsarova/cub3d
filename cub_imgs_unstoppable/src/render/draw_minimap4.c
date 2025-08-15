#include "../../include/cub3D.h"

void setup_viewport_minimap(t_data *d, t_minimap_params *params)
{
    // If map is huge, show viewport around player instead of whole map
    if (d->map_cols > 20 || d->map_rows > 20)
    {
        int tiles_radius = 6;  // Show 12x12 area around player
        int player_tile_x = d->pl->x / TILE_SIZE;
        int player_tile_y = d->pl->y / TILE_SIZE;
        
        // Calculate what map area to show
        params->start_x = player_tile_x - tiles_radius;
        params->start_y = player_tile_y - tiles_radius;
        params->end_x = player_tile_x + tiles_radius;
        params->end_y = player_tile_y + tiles_radius;
        
        // Clamp to map boundaries
        if (params->start_x < 0) params->start_x = 0;
        if (params->start_y < 0) params->start_y = 0;
        if (params->end_x >= d->map_cols) params->end_x = d->map_cols - 1;
        if (params->end_y >= d->map_rows) params->end_y = d->map_rows - 1;
        
        // Calculate scale for visible area only
        int visible_cols = params->end_x - params->start_x + 1;
        int visible_rows = params->end_y - params->start_y + 1;
        int larger = (visible_cols > visible_rows) ? visible_cols : visible_rows;
        params->scale = (float)MINIMAP_SIZE / (larger * TILE_SIZE);
    }
    else
    {
        // Small map - show everything
        params->start_x = 0;
        params->start_y = 0;
        params->end_x = d->map_cols - 1;
        params->end_y = d->map_rows - 1;
        params->scale = (float)MINIMAP_SIZE / (d->map_cols * TILE_SIZE);
    }
}
