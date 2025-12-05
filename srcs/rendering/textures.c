/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abjellal <abjellal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 15:18:16 by abjellal          #+#    #+#             */
/*   Updated: 2025/12/05 15:08:23 by abjellal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	little_endian_poi(t_control *main, int index, int color)
{
	main->data[index] = color & 0xFF;
	main->data[index + 1] = (color >> 8) & 0xFF;
	main->data[index + 2] = (color >> 16) & 0xFF;
}

static void	big_endian_poi(t_control *main, int index, int color)
{
	main->data[index] = (color >> 16) & 0xFF;
	main->data[index + 1] = (color >> 8) & 0xFF;
	main->data[index + 2] = color & 0xFF;
}

void	pixel_on_img(t_control *main, int x, int y, int color)
{
	int	index;

	index = (y * main->line_length) + (x * (main->bits_per_pixel / 8));
	if (main->endian == 0)
		little_endian_poi(main, index, color);
	else
		big_endian_poi(main, index, color);
}

void	paint_line(t_control *main, int y_start, int y_end, int color)
{
	int	y;

	if (y_start < 0)
		y_start = 0;
	if (y_end > HEIGHT)
		y_end = HEIGHT;
	y = y_start;
	while (y < y_end)
	{
		pixel_on_img(main, main->current_x, y, color);
		y++;
	}
}

void	paint_texture_line(t_control *main, t_texture *tex)
{
	int	y;
	int	tex_y;
	int	color;

	y = main->drawstart;
	if (y < 0)
		y = 0;
	while (y < main->drawend && y < HEIGHT)
	{
		tex_y = (int)main->texPos & (64 - 1);
		main->texPos += main->steP;
		color = get_texture_pixel_color(tex, main->texx, tex_y);
		pixel_on_img(main, main->current_x, y, color);
		y++;
	}
}
