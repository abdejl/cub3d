/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-bar <yael-bar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 11:53:47 by abjellal          #+#    #+#             */
/*   Updated: 2025/12/10 21:46:07 by yael-bar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	destroy_images(t_control *main)
{
	if (main->east_tex.img_ptr)
		mlx_destroy_image(main->mlx_ptr, main->east_tex.img_ptr);
	if (main->south_tex.img_ptr)
		mlx_destroy_image(main->mlx_ptr, main->south_tex.img_ptr);
	if (main->north_tex.img_ptr)
		mlx_destroy_image(main->mlx_ptr, main->north_tex.img_ptr);
	if (main->west_tex.img_ptr)
		mlx_destroy_image(main->mlx_ptr, main->west_tex.img_ptr);
}

void	cleanup_game(t_control *control)
{
	destroy_images(control);
	if (control->mlx_win)
	{
		mlx_destroy_window(control->mlx_ptr, control->mlx_win);
	}
	if (control->mlx_ptr)
	{
		mlx_destroy_display(control->mlx_ptr);
		free(control->mlx_ptr);
	}
	// if (control->map) i free him in free_all();
	// 	free(control->map);
}

int	close_game(t_control *control)
{
	cleanup_game(control);
	free_all(); // free my data
	return (0);
}
