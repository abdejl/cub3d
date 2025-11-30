/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abjellal <abjellal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 12:01:39 by abjellal          #+#    #+#             */
/*   Updated: 2025/11/30 12:10:06 by abjellal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_player_forward(t_control *main)
{
	double	x_step;
	double	y_step;
	double	new_x;
	double	new_y;

	x_step = main->dir.x * MOVE_SPEED;
	y_step = main->dir.y * MOVE_SPEED;
	new_x = main->player.x + x_step;
	new_y = main->player.y + y_step;
	if (main->map_grid[(int)main->player.y][(int)new_x] != '1')
	{
		main->player.x = new_x;
	}
	if (main->map_grid[(int)new_y][(int)main->player.x] != '1')
	{
		main->player.y = new_y;
	}
}

void	move_player_backward(t_control *main)
{
	double	x_step;
	double	y_step;
	double	new_x;
	double	new_y;

	x_step = main->dir.x * MOVE_SPEED;
	y_step = main->dir.y * MOVE_SPEED;
	new_x = main->player.x - x_step;
	new_y = main->player.y - y_step;
	if (main->map_grid[(int)main->player.y][(int)new_x] != '1')
	{
		main->player.x = new_x;
	}
	if (main->map_grid[(int)new_y][(int)main->player.x] != '1')
	{
		main->player.y = new_y;
	}
}

void	move_player_right(t_control *main)
{
	double	x_step;
	double	y_step;
	double	new_x;
	double	new_y;

	x_step = main->plane.x * MOVE_SPEED;
	y_step = main->plane.y * MOVE_SPEED;
	new_x = main->player.x + x_step;
	new_y = main->player.y + y_step;
	if (main->map_grid[(int)main->player.y][(int)new_x] != '1')
	{
		main->player.x = new_x;
	}
	if (main->map_grid[(int)new_y][(int)main->player.x] != '1')
	{
		main->player.y = new_y;
	}
}

void	move_player_left(t_control *main)
{
	double	x_step;
	double	y_step;
	double	new_x;
	double	new_y;

	x_step = main->plane.x * MOVE_SPEED;
	y_step = main->plane.y * MOVE_SPEED;
	new_x = main->player.x - x_step;
	new_y = main->player.y - y_step;
	if (main->map_grid[(int)main->player.y][(int)new_x] != '1')
	{
		main->player.x = new_x;
	}
	if (main->map_grid[(int)new_y][(int)main->player.x] != '1')
	{
		main->player.y = new_y;
	}
}

void	rotate_player(t_control *main, int direction)
{
	double	angle;
	double	old_dir_x;
	double	old_plane_x;

	angle = ROT_SPEED * direction;
	old_dir_x = main->dir.x;
	main->dir.x = main->dir.x * cos(angle) - main->dir.y * sin(angle);
	main->dir.y = old_dir_x * sin(angle) + main->dir.y * cos(angle);
	old_plane_x = main->plane.x;
	main->plane.x = main->plane.x * cos(angle) - main->plane.y * sin(angle);
	main->plane.y = old_plane_x * sin(angle) + main->plane.y * cos(angle);
}
