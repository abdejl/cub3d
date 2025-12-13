/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils_v2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abjellal <abjellal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 17:53:28 by yael-bar          #+#    #+#             */
/*   Updated: 2025/12/10 14:50:14 by abjellal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	initialize_data(int i)
{
	t_control	*main;

	main = control_memo();
	main->ray.rayAngle = main->player.playerAngle - (FOV / 2) + (i * FOV
			/ WIDTH);
	main->raydir.x = cos(main->ray.rayAngle);
	main->raydir.y = sin(main->ray.rayAngle);
	main->ray.is_facing_down = 0;
	main->ray.is_facing_up = 0;
	main->ray.is_facing_right = 0;
	main->ray.is_facing_left = 0;
	main->ray.xStep_v = 0;
	main->ray.yStep_h = 0;
}

void	set_facing_hit(void)
{
	t_control	*main;

	main = control_memo();
	if (main->raydir.y > 0.0)
	{
		main->ray.yStep_h = 1;
		main->ray.is_facing_down = 1;
	}
	else if (main->raydir.y < 0.0)
	{
		main->ray.is_facing_up = 1;
		main->ray.yStep_h = -1;
	}
	if (main->raydir.x > 0.0)
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

void	find_horizontal_wall(int x, int y)
{
	t_control	*main;

	main = control_memo();
	while (map_cell_state(main, x, y) == 0)
	{
		main->ray.next_h_x += main->ray.xStep_h;
		main->ray.next_h_y += main->ray.yStep_h;
		x = (int)floor(main->ray.next_h_x);
		y = (int)floor(main->ray.next_h_y);
		if (main->ray.is_facing_up && y > 0)
			y--;
	}
}

void	find_vertical_wall(int x, int y)
{
	t_control	*main;

	main = control_memo();
	while (map_cell_state(main, x, y) == 0)
	{
		main->ray.next_v_x += main->ray.xStep_v;
		main->ray.next_v_y += main->ray.yStep_v;
		x = (int)floor(main->ray.next_v_x);
		y = (int)floor(main->ray.next_v_y);
		if (main->ray.is_facing_left && x > 0)
			x--;
	}
}

void	draw_wall_line(int i, int side)
{
	t_control	*main;

	main = control_memo();
	paint_line(i, 0, main->drawstart, main->ceiling_color);
	paint_line(i, main->drawend, HEIGHT, main->floor_color);
	if (side == 0)
	{
		if (main->raydir.x > 0)
			paint_texture_line(main, i, &main->east_tex);
		else
			paint_texture_line(main, i, &main->west_tex);
	}
	else
	{
		if (main->raydir.y > 0)
			paint_texture_line(main, i, &main->south_tex);
		else
			paint_texture_line(main, i, &main->north_tex);
	}
}
