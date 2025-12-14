/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-bar <yael-bar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 17:51:48 by yael-bar          #+#    #+#             */
/*   Updated: 2025/12/14 10:36:20 by yael-bar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	find_horizontal_intersection(void)
{
	t_control	*main;
	int			x;
	int			y;

	main = control_memo();
	if (fabs(main->raydir.y) < 1e-9)
	{
		main->h_distance = INFINITY;
		return ;
	}
	if (main->ray.is_facing_down)
		main->ray.next_h_y = floor(main->player.y) + 1.0;
	else
		main->ray.next_h_y = floor(main->player.y);
	main->ray.next_h_x = main->player.x + (main->ray.next_h_y - main->player.y)
		/ tan(main->ray.rayangle);
	main->ray.xstep_h = main->ray.ystep_h / tan(main->ray.rayangle);
	x = (int)floor(main->ray.next_h_x);
	y = (int)floor(main->ray.next_h_y);
	if (main->ray.is_facing_up && y > 0)
		y--;
	find_horizontal_wall(x, y);
	main->h_distance = distance_between_2(main->player.x, main->player.y,
			main->ray.next_h_x, main->ray.next_h_y);
}

void	find_vertical_intersection(void)
{
	t_control	*main;
	int			x;
	int			y;

	main = control_memo();
	if (fabs(main->raydir.x) < 1e-9)
	{
		main->v_distance = INFINITY;
		return ;
	}
	if (main->ray.is_facing_right)
		main->ray.next_v_x = floor(main->player.x) + 1.0;
	else
		main->ray.next_v_x = floor(main->player.x);
	main->ray.next_v_y = main->player.y + (main->ray.next_v_x - main->player.x)
		* tan(main->ray.rayangle);
	main->ray.ystep_v = main->ray.xstep_v * tan(main->ray.rayangle);
	x = (int)floor(main->ray.next_v_x);
	y = (int)floor(main->ray.next_v_y);
	if (main->ray.is_facing_left && x > 0)
		x--;
	find_vertical_wall(x, y);
	main->v_distance = distance_between_2(main->player.x, main->player.y,
			main->ray.next_v_x, main->ray.next_v_y);
}

void	get_wall_hit_and_distance_and_height(int *side)
{
	t_control	*main;

	main = control_memo();
	if (main->h_distance < main->v_distance)
	{
		main->perpwalldist = main->h_distance;
		main->wallx = main->ray.next_h_x / 1.0;
		*side = 1;
	}
	else
	{
		main->perpwalldist = main->v_distance;
		main->wallx = main->ray.next_v_y / 1.0;
		*side = 0;
	}
	main->wallx = main->wallx - floor(main->wallx);
	main->perpwalldist *= cos(main->ray.rayangle - main->player.playerangle);
	if (main->perpwalldist < 0.001)
		main->perpwalldist = 0.001;
	main->lineheight = (int)(HEIGHT / main->perpwalldist);
}

void	get_draw_start_end(t_control *main)
{
	main->drawstart = (HEIGHT / 2) - (main->lineheight / 2);
	main->drawend = (HEIGHT / 2) + (main->lineheight / 2);
	if (main->drawstart < 0)
		main->drawstart = 0;
	if (main->drawend >= HEIGHT)
		main->drawend = HEIGHT - 1;
}

void	calculate_ray_to_wall(t_control *main)
{
	int	i;
	int	side;

	main->player.playerangle = atan2(main->dir.y, main->dir.x);
	i = 0;
	while (i < WIDTH)
	{
		initialize_data(i);
		set_facing_hit();
		find_horizontal_intersection();
		find_vertical_intersection();
		get_wall_hit_and_distance_and_height(&side);
		get_draw_start_end(main);
		main->texx = (int)(main->wallx * TEXTUREWIDTH);
		if ((side == 0 && main->raydir.x > 0) || (side == 1
				&& main->raydir.y < 0))
			main->texx = TEXTUREWIDTH - main->texx - 1;
		main->step = (double)((double)TEXTUREHEIGHT / (double)main->lineheight);
		main->texpos = 0;
		if (main->lineheight > HEIGHT)
			main->texpos = ((main->lineheight - HEIGHT) / 2) * main->step;
		draw_wall_line(i, side);
		i++;
	}
}
