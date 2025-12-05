#include "cub3d.h"


static void	make_ray_position(t_control *main_control)
{
	main_control->Map.x = ((int)main_control->player.x);
	main_control->Map.y = ((int)main_control->player.y);
}

static void	calculate_delta_distance(t_control *main_control) // if raydir.y/x == 0 !!!!!
{
	if(main_control->raydir.x == 0)
		main_control->delta_dist.x = INFINITY;
	else
		main_control->delta_dist.x = fabs(1 / main_control->raydir.x);
	if(main_control->raydir.y == 0)
		main_control->delta_dist.y = INFINITY;
	else
		main_control->delta_dist.y = fabs(1 / main_control->raydir.y);
}

static void	make_step(t_control *main_control)
{
	if(main_control->raydir.x > 0)
		main_control->step.x = 1;
	else
		main_control->step.x = -1;
	if(main_control->raydir.y > 0)
		main_control->step.y = 1;
	else
		main_control->step.y = -1;
}

static void	make_side_distance(t_control *main_control)
{
    if(main_control->step.x < 0)
        main_control->side_dist.x = (main_control->player.x - main_control->Map.x) * main_control->delta_dist.x;
    else
        main_control->side_dist.x = (main_control->Map.x + 1.0 - main_control->player.x) * main_control->delta_dist.x;
    if(main_control->step.y < 0)
        main_control->side_dist.y = (main_control->player.y - main_control->Map.y) * main_control->delta_dist.y;
    else
        main_control->side_dist.y = (main_control->Map.y + 1.0 - main_control->player.y) * main_control->delta_dist.y;
}

void	calculate_ray_to_wall(t_control *main_control)
{
	int i;
	int	x;
	int	y;
	int side = -1;

	i = 0;
	while(i < WIDTH)
	{
		main_control->current_x = i;
		main_control->camerax = 2.0 * i / (double)WIDTH - 1.0;
		calculate_ray_direction(main_control);
				//  DDA to find wall
		make_ray_position(main_control);
		calculate_delta_distance(main_control);
		make_step(main_control);
		make_side_distance(main_control);
        x = (int)main_control->Map.x;
		y = (int)main_control->Map.y;
		while(main_control->map_grid[y][x] != '1')
		{

			if (x < 0 || x >= 53 || y < 0 || y >= 33) 
				break;
			if(main_control->side_dist.x < main_control->side_dist.y)
			{
				x += main_control->step.x;
				main_control->side_dist.x += main_control->delta_dist.x;
				side = 0;
			}
			else
			{
				y += main_control->step.y;
				main_control->side_dist.y += main_control->delta_dist.y;
				side = 1;
			}
		}
		if(side == 0)
			main_control->perpWallDist = (main_control->side_dist.x - main_control->delta_dist.x);
		else
			main_control->perpWallDist = (main_control->side_dist.y - main_control->delta_dist.y);
			// Add safety check:
		if (main_control->perpWallDist <= 0.0)
    		main_control->perpWallDist = 0.1;  // Small safe value`
		main_control->lineHeight = HEIGHT / main_control->perpWallDist;
		main_control->drawstart = (HEIGHT/ 2) -  (main_control->lineHeight / 2);
		if(main_control->drawstart < 0)
			main_control->drawstart = 0;
		main_control->drawend = (HEIGHT/ 2) +  (main_control->lineHeight / 2);
		if(main_control->drawend >= HEIGHT)
			main_control->drawend = HEIGHT - 1;
		if(side == 0)
			main_control->wallX = main_control->player.y + main_control->perpWallDist * main_control->raydir.y;
		else
			main_control->wallX = main_control->player.x + main_control->perpWallDist * main_control->raydir.x;
		main_control->wallX -= floor(main_control->wallX);
		main_control->texx = (int) (main_control->wallX * (double) textureWidth);
		if ((side == 0 && main_control->raydir.x > 0) || (side == 1 && main_control->raydir.y < 0))
    		main_control->texx = textureWidth - main_control->texx - 1;
		main_control->steP = (double) ((double) textureHeight / (double) main_control->lineHeight);
		main_control->texPos = (main_control->drawstart - HEIGHT / 2 + main_control->lineHeight / 2) * main_control->steP;

		//part diali li zedt!!!!
		paint_line(main_control, 0, main_control->drawstart, main_control->ceiling_color);
		paint_line(main_control, main_control->drawend, HEIGHT, main_control->floor_color);
		if (side == 0) 
		{
    		if (main_control->raydir.x > 0)
        		paint_texture_line(main_control, &main_control->east_tex);
    		else
        		paint_texture_line(main_control, &main_control->west_tex);
		}
		else
		{
    		if (main_control->raydir.y > 0)
        		paint_texture_line(main_control, &main_control->south_tex);
    		else
        		paint_texture_line(main_control, &main_control->north_tex);
		}
		i++;
	}
}