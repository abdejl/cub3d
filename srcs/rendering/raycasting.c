/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-bar <yael-bar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 17:51:48 by yael-bar          #+#    #+#             */
/*   Updated: 2025/12/09 16:16:20 by yael-bar         ###   ########.fr       */
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
		/ tan(main->ray.rayAngle);
	main->ray.xStep_h = main->ray.yStep_h / tan(main->ray.rayAngle);
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
		* tan(main->ray.rayAngle);
	main->ray.yStep_v = main->ray.xStep_v * tan(main->ray.rayAngle);
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
		main->perpWallDist = main->h_distance;
		main->wallX = main->ray.next_h_x / 1.0;
		*side = 1;
	}
	else
	{
		main->perpWallDist = main->v_distance;
		main->wallX = main->ray.next_v_y / 1.0;
		*side = 0;
	}
	main->wallX = main->wallX - floor(main->wallX);
	main->perpWallDist *= cos(main->ray.rayAngle - main->player.playerAngle);
	if (main->perpWallDist < 0.001)
		main->perpWallDist = 0.001;
	main->lineHeight = (int)(HEIGHT / main->perpWallDist);
}

void	get_draw_start_end(t_control *main)
{
	main->drawstart = (HEIGHT / 2) - (main->lineHeight / 2);
	main->drawend = (HEIGHT / 2) + (main->lineHeight / 2);
	if (main->drawstart < 0)
		main->drawstart = 0;
	if (main->drawend >= HEIGHT)
		main->drawend = HEIGHT - 1;
}

void	calculate_ray_to_wall(t_control *main)
{
	int	i;
	int	side;

	main->player.playerAngle = atan2(main->dir.y, main->dir.x);
	i = 0;
	while (i < WIDTH)
	{
		initialize_data(i);
		set_facing_hit();
		find_horizontal_intersection();
		find_vertical_intersection();
		get_wall_hit_and_distance_and_height(&side);
		get_draw_start_end(main);
		main->texx = (int)(main->wallX * textureWidth);
		if ((side == 0 && main->raydir.x > 0) || (side == 1
				&& main->raydir.y < 0))
			main->texx = textureWidth - main->texx - 1;
		main->steP = (double)((double)textureHeight / (double)main->lineHeight);
		main->texPos = 0;
		if (main->lineHeight > HEIGHT)
			main->texPos = ((main->lineHeight - HEIGHT) / 2) * main->steP;
		draw_wall_line(i, side);
		i++;
	}
}
