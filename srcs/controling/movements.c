/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abjellal <abjellal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 12:01:39 by abjellal          #+#    #+#             */
/*   Updated: 2025/12/04 14:54:30 by abjellal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_player_forward(t_control *main)
{
	t_move	move;

	move.x_step = main->dir.x * MOVE_SPEED;
	move.y_step = main->dir.y * MOVE_SPEED;
	move.new_x = main->player.x + move.x_step;
	move.new_y = main->player.y + move.y_step;
	if (move.x_step > 0)
		move.buffer = 0.2;
	else
		move.buffer = -0.2;
	if (main->map_grid[(int)main->player.y][(int)
		(move.new_x + move.buffer)] != '1')
	{
		main->player.x = move.new_x;
	}
	if (move.y_step > 0)
		move.buffer = 0.2;
	else
		move.buffer = -0.2;
	if (main->map_grid[(int)
			(move.new_y + move.buffer)][(int)main->player.x] != '1')
	{
		main->player.y = move.new_y;
	}
}

void	move_player_backward(t_control *main)
{
	t_move	move;

	move.x_step = main->dir.x * MOVE_SPEED;
	move.y_step = main->dir.y * MOVE_SPEED;
	move.new_x = main->player.x - move.x_step;
	move.new_y = main->player.y - move.y_step;
	if (move.new_x > main->player.x)
		move.buffer = 0.2;
	else
		move.buffer = -0.2;
	if (main->map_grid[(int)main->player.y][(int)
		(move.new_x + move.buffer)] != '1')
	{
		main->player.x = move.new_x;
	}
	if (move.new_y > main->player.y)
		move.buffer = 0.2;
	else
		move.buffer = -0.2;
	if (main->map_grid[(int)
			(move.new_y + move.buffer)][(int)main->player.x] != '1')
	{
		main->player.y = move.new_y;
	}
}

void	move_player_right(t_control *main)
{
	t_move	move;

	move.x_step = main->plane.x * MOVE_SPEED;
	move.y_step = main->plane.y * MOVE_SPEED;
	move.new_x = main->player.x + move.x_step;
	move.new_y = main->player.y + move.y_step;
	if (move.new_x > main->player.x)
		move.buffer = 0.2;
	else
		move.buffer = -0.2;
	if (main->map_grid[(int)main->player.y][(int)
		(move.new_x + move.buffer)] != '1')
	{
		main->player.x = move.new_x;
	}
	if (move.new_y > main->player.y)
		move.buffer = 0.2;
	else
		move.buffer = -0.2;
	if (main->map_grid[(int)
			(move.new_y + move.buffer)][(int)main->player.x] != '1')
	{
		main->player.y = move.new_y;
	}
}

void	move_player_left(t_control *main)
{
	t_move	move;

	move.x_step = main->plane.x * MOVE_SPEED;
	move.y_step = main->plane.y * MOVE_SPEED;
	move.new_x = main->player.x - move.x_step;
	move.new_y = main->player.y - move.y_step;
	if (move.new_x > main->player.x)
		move.buffer = 0.2;
	else
		move.buffer = -0.2;
	if (main->map_grid[(int)main->player.y][(int)
		(move.new_x + move.buffer)] != '1')
	{
		main->player.x = move.new_x;
	}
	if (move.new_y > main->player.y)
		move.buffer = 0.2;
	else
		move.buffer = -0.2;
	if (main->map_grid[(int)
			(move.new_y + move.buffer)][(int)main->player.x] != '1')
	{
		main->player.y = move.new_y;
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
