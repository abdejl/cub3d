// #include "cub3d.h"


// static void	make_ray_position(t_control *main_control)
// {
// 	main_control->Map.x = ((int)main_control->player.x);
// 	main_control->Map.y = ((int)main_control->player.y);
// }

// static void	calculate_delta_distance(t_control *main_control) // if raydir.y/x == 0 !!!!!
// {
// 	if(main_control->raydir.x == 0)
// 		main_control->delta_dist.x = INFINITY;
// 	else
// 		main_control->delta_dist.x = fabs(1 / main_control->raydir.x);
// 	if(main_control->raydir.y == 0)
// 		main_control->delta_dist.y = INFINITY;
// 	else
// 		main_control->delta_dist.y = fabs(1 / main_control->raydir.y);
// }

// static void	make_step(t_control *main_control)
// {
// 	if(main_control->raydir.x > 0)
// 		main_control->step.x = 1;
// 	else
// 		main_control->step.x = -1;
// 	if(main_control->raydir.y > 0)
// 		main_control->step.y = 1;
// 	else
// 		main_control->step.y = -1;
// }

// static void	make_side_distance(t_control *main_control)
// {
//     if(main_control->step.x < 0)
//         main_control->side_dist.x = (main_control->player.x - main_control->Map.x) * main_control->delta_dist.x;
//     else
//         main_control->side_dist.x = (main_control->Map.x + 1.0 - main_control->player.x) * main_control->delta_dist.x;
//     if(main_control->step.y < 0)
//         main_control->side_dist.y = (main_control->player.y - main_control->Map.y) * main_control->delta_dist.y;
//     else
//         main_control->side_dist.y = (main_control->Map.y + 1.0 - main_control->player.y) * main_control->delta_dist.y;
// }

// void	calculate_ray_to_wall(t_control *main_control)
// {
// 	int i;
// 	int	x;
// 	int	y;
// 	int side = -1;

// 	i = 0;
// 	while(i < WIDTH)
// 	{
// 		main_control->current_x = i;
// 		main_control->camerax = 2.0 * i / (double)WIDTH - 1.0;
// 		calculate_ray_direction(main_control);
// 				//  DDA to find wall
// 		make_ray_position(main_control);
// 		calculate_delta_distance(main_control);
// 		make_step(main_control);
// 		make_side_distance(main_control);
//         x = (int)main_control->Map.x;
// 		y = (int)main_control->Map.y;
// 		while(main_control->map_grid[y][x] != '1')
// 		{

// 			if (x < 0 || x >= 53 || y < 0 || y >= 33) 
// 				break;
// 			if(main_control->side_dist.x < main_control->side_dist.y)
// 			{
// 				x += main_control->step.x;
// 				main_control->side_dist.x += main_control->delta_dist.x;
// 				side = 0;
// 			}
// 			else
// 			{
// 				y += main_control->step.y;
// 				main_control->side_dist.y += main_control->delta_dist.y;
// 				side = 1;
// 			}
// 		}
// 		if(side == 0)
// 			main_control->perpWallDist = (main_control->side_dist.x - main_control->delta_dist.x);
// 		else
// 			main_control->perpWallDist = (main_control->side_dist.y - main_control->delta_dist.y);
// 			// Add safety check:
// 		if (main_control->perpWallDist <= 0.0)
//     		main_control->perpWallDist = 0.1;  // Small safe value`
// 		main_control->lineHeight = HEIGHT / main_control->perpWallDist;
// 		main_control->drawstart = (HEIGHT/ 2) -  (main_control->lineHeight / 2);
// 		if(main_control->drawstart < 0)
// 			main_control->drawstart = 0;
// 		main_control->drawend = (HEIGHT/ 2) +  (main_control->lineHeight / 2);
// 		if(main_control->drawend >= HEIGHT)
// 			main_control->drawend = HEIGHT - 1;
// 		if(side == 0)
// 			main_control->wallX = main_control->player.y + main_control->perpWallDist * main_control->raydir.y;
// 		else
// 			main_control->wallX = main_control->player.x + main_control->perpWallDist * main_control->raydir.x;
// 		main_control->wallX -= floor(main_control->wallX);
// 		main_control->texx = (int) (main_control->wallX * (double) textureWidth);
// 		if ((side == 0 && main_control->raydir.x > 0) || (side == 1 && main_control->raydir.y < 0))
//     		main_control->texx = textureWidth - main_control->texx - 1;
// 		main_control->steP = (double) ((double) textureHeight / (double) main_control->lineHeight);
// 		main_control->texPos = (main_control->drawstart - HEIGHT / 2 + main_control->lineHeight / 2) * main_control->steP;

// 		//part diali li zedt!!!!
// 		paint_line(main_control, 0, main_control->drawstart, main_control->ceiling_color);
// 		paint_line(main_control, main_control->drawend, HEIGHT, main_control->floor_color);
// 		if (side == 0) 
// 		{
//     		if (main_control->raydir.x > 0)
//         		paint_texture_line(main_control, &main_control->east_tex);
//     		else
//         		paint_texture_line(main_control, &main_control->west_tex);
// 		}
// 		else
// 		{
//     		if (main_control->raydir.y > 0)
//         		paint_texture_line(main_control, &main_control->south_tex);
//     		else
//         		paint_texture_line(main_control, &main_control->north_tex);
// 		}
// 		i++;
// 	}
// }


// new code   :> 

#include "cub3d.h"

double distance_between_2(double x1, double y1, double x2, double y2)
{
	double dx = x2 - x1;
	double dy = y2 - y1;
	return sqrt(dx*dx + dy*dy);
}



static int	map_cell_state(t_control *main, int grid_x, int grid_y)
{
	size_t	row_len;

	if (grid_y < 0 || grid_y >= main->map_height || grid_x < 0 || grid_x >= main->map_width)
		return (-1);
	if (main->map_grid[grid_y][grid_x] == '1')
		return (1);
	return (0);
}


void	initialize_data(int i)
{
	t_control *main;

	main = control_memo();
	main->ray.rayAngle = main->player.playerAngle - (FOV / 2) + (i * FOV / WIDTH);
	main->raydir.x = cos(main->ray.rayAngle);
    main->raydir.y = sin(main->ray.rayAngle);
}

void	set_facing_hit()
{
	t_control *main;

	main = control_memo();
	main->ray.is_facing_down = 0;
	main->ray.is_facing_up = 0;
	main->ray.is_facing_right = 0;
	main->ray.is_facing_left = 0;
	main->ray.xStep_v = 0;
	main->ray.yStep_h = 0;
	main->v_distance = INFINITY;
	main->h_distance = INFINITY;

	if(main->raydir.y > 0.0)
	{
		main->ray.yStep_h = 1;
		main->ray.is_facing_down = 1;
	}
	else if(main->raydir.y < 0.0)
	{
		main->ray.is_facing_up = 1;
		main->ray.yStep_h = -1;
	}
	if(main->raydir.x > 0.0)
	{
		main->ray.is_facing_right = 1;
		main->ray.xStep_v = 1;
	}
	else if (main->raydir.x < 0.0)
	{
		main->ray.is_facing_left = 1;
		main->ray.xStep_v = -1;
	}
}

void	find_horizontal_intersection()
{
	t_control	*main;
	int			x;
	int			y;
	int			cell_state;

	main = control_memo();
	if (fabs(main->raydir.y) < 1e-9)
	{
		main->h_distance = INFINITY;
		return ;
	}
	if(main->ray.is_facing_down)
		main->ray.next_h_y = floor(main->player.y) + 1.0;
	else
		main->ray.next_h_y = floor(main->player.y);
	
	main->ray.next_h_x = main->player.x + (main->ray.next_h_y - main->player.y) / tan(main->ray.rayAngle);
	main->ray.xStep_h = main->ray.yStep_h / tan(main->ray.rayAngle);
	
	x = (int)floor(main->ray.next_h_x);
	y = (int)floor(main->ray.next_h_y);
	if (main->ray.is_facing_up && y > 0) // -1 in y about check y up :> if dont - in y you check here in y to plyer 
		y--;
	
	cell_state = map_cell_state(main, x, y);
	while (cell_state == 0)
	{
		main->ray.next_h_x += main->ray.xStep_h;
		main->ray.next_h_y += main->ray.yStep_h;
		x = (int)floor(main->ray.next_h_x);
		y = (int)floor(main->ray.next_h_y);
		if (main->ray.is_facing_up && y > 0)
			y--;
		cell_state = map_cell_state(main, x, y);
	}
	main->h_distance = distance_between_2(main->player.x, main->player.y, main->ray.next_h_x, main->ray.next_h_y);
}

void	find_vertical_intersection()
{
	t_control	*main;
	int			x;
	int			y;
	int			cell_state;
	double		xStep;
	double		yStep;

	main = control_memo();
	if (fabs(main->raydir.x) < 1e-9)
	{
		main->v_distance = INFINITY;
		return ;
	}
	if(main->ray.is_facing_right)
		main->ray.next_v_x = floor(main->player.x) + 1.0;
	else
		main->ray.next_v_x = floor(main->player.x);
	
	main->ray.next_v_y = main->player.y + (main->ray.next_v_x - main->player.x) * tan(main->ray.rayAngle);
	main->ray.yStep_v = main->ray.xStep_v * tan(main->ray.rayAngle);
	
	x = (int)floor(main->ray.next_v_x);
	y = (int)floor(main->ray.next_v_y);
	if (main->ray.is_facing_left && x > 0) // // -1 in x about check y up :> if dont - in x you check here in x to plyer 
		x--;
	
	cell_state = map_cell_state(main, x, y);
	while (cell_state == 0)
	{
		main->ray.next_v_x += main->ray.xStep_v;
		main->ray.next_v_y += main->ray.yStep_v;
		x = (int)floor(main->ray.next_v_x);
		y = (int)floor(main->ray.next_v_y);
		if (main->ray.is_facing_left && x > 0)
			x--;
		cell_state = map_cell_state(main, x, y);
	}
	main->v_distance = distance_between_2(main->player.x, main->player.y, main->ray.next_v_x, main->ray.next_v_y);
}

void	calculate_ray_to_wall(t_control *main)
{
	int	i;
	int	side;
	t_texture *tex;
	static int debug_once = 0;

	if (!main || !main->map_grid)
		return;
	main->player.playerAngle = atan2(main->dir.y, main->dir.x);// CONVERTS MOTAJIHA L ZAWIYA 
	i = 0;
	while (i < WIDTH)
	{
		main->perpWallDist = INFINITY;
		initialize_data(i);
		set_facing_hit();
		find_horizontal_intersection();
		find_vertical_intersection();
		
		if (main->h_distance < main->v_distance)
		{
			main->perpWallDist = main->h_distance;
			side = 1;

			main->wallX = main->ray.next_h_x / 1.0;
			main->wallX = main->wallX - floor(main->wallX);
		}
		else
		{
			main->perpWallDist = main->v_distance;
			side = 0;
			main->wallX = main->ray.next_v_y / 1.0;
			main->wallX = main->wallX - floor(main->wallX);
		}	
		main->perpWallDist *= cos(main->ray.rayAngle - main->player.playerAngle);
		main->lineHeight = HEIGHT / main->perpWallDist;
		
		main->drawstart = (HEIGHT / 2) - (main->lineHeight / 2);
		main->drawend = (HEIGHT / 2) + (main->lineHeight / 2);
		if (main->drawstart < 0)
			main->drawstart = 0;
		if (main->drawend >= HEIGHT)
			main->drawend = HEIGHT - 1;
		
		main->texx = (int)(main->wallX * textureWidth);
		main->steP = (double) ((double) textureHeight / (double) main->lineHeight);
		main->texPos = (main->drawstart - HEIGHT / 2 + main->lineHeight / 2) * main->steP;

		//part diali li zedt!!!!
		paint_line(main, i, 0, main->drawstart, main->ceiling_color);
		paint_line(main, i, main->drawend, HEIGHT, main->floor_color);
		if (side == 0) 
		{
    		if (main->raydir.x > 0)
        		paint_texture_line(main, i, main->drawstart, main->drawend, &main->east_tex);
    		else
        		paint_texture_line(main, i, main->drawstart, main->drawend, &main->west_tex);
		}
		else
		{
    		if (main->raydir.y > 0)
        		paint_texture_line(main, i, main->drawstart, main->drawend, &main->south_tex);
    		else
        		paint_texture_line(main, i, main->drawstart, main->drawend, &main->north_tex);
		}
		i++;
	}
}