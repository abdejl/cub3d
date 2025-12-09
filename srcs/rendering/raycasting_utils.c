/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-bar <yael-bar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 17:57:05 by yael-bar          #+#    #+#             */
/*   Updated: 2025/12/09 16:02:31 by yael-bar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	make_dir(t_control *main_control)
{
	if (main_control->player.direction == 'N')
	{
		main_control->dir.x = 0;
		main_control->dir.y = -1;
	}
	else if (main_control->player.direction == 'S')
	{
		main_control->dir.x = 0;
		main_control->dir.y = 1;
	}
	else if (main_control->player.direction == 'E')
	{
		main_control->dir.x = 1;
		main_control->dir.y = 0;
	}
	else if (main_control->player.direction == 'W')
	{
		main_control->dir.x = -1;
		main_control->dir.y = 0;
	}
}

void	make_plane(t_control *main_control)
{
	double	planelen;

	planelen = 0.60;
	main_control->plane.x = (main_control->dir.y * -1) * planelen;
	main_control->plane.y = main_control->dir.x * planelen;
}

double	distance_between_2(double x1, double y1, double x2, double y2)
{
	double	dx;
	double	dy;

	dx = x2 - x1;
	dy = y2 - y1;
	return (sqrt(dx * dx + dy * dy));
}

int	map_cell_state(t_control *main, int grid_x, int grid_y)
{
	if (grid_y < 0 || grid_y >= main->map_height || grid_x < 0
		|| grid_x >= main->map_width)
		return (-1);
	if (main->map_grid[grid_y][grid_x] == '1')
		return (1);
	return (0);
}
