/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abjellal <abjellal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 16:51:15 by abjellal          #+#    #+#             */
/*   Updated: 2025/12/04 16:51:54 by abjellal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_data_addr(t_control *main)
{
	main->east_tex.data = mlx_get_data_addr(main->east_tex.img_ptr,
			&main->east_tex.bits_per_pixel, &main->east_tex.line_length,
			&main->east_tex.endian);
	main->north_tex.data = mlx_get_data_addr(main->north_tex.img_ptr,
			&main->north_tex.bits_per_pixel, &main->north_tex.line_length,
			&main->north_tex.endian);
	main->south_tex.data = mlx_get_data_addr(main->south_tex.img_ptr,
			&main->south_tex.bits_per_pixel, &main->south_tex.line_length,
			&main->south_tex.endian);
	main->west_tex.data = mlx_get_data_addr(main->west_tex.img_ptr,
			&main->west_tex.bits_per_pixel, &main->west_tex.line_length,
			&main->west_tex.endian);
}

void	load_texture(t_control *main)
{
	main->east_tex.img_ptr = mlx_xpm_file_to_image(main->mlx_ptr,
			main->ea_texture_path,
			&main->east_tex.width, &main->east_tex.height);
	main->north_tex.img_ptr = mlx_xpm_file_to_image(main->mlx_ptr,
			main->no_texture_path, &main->north_tex.width,
			&main->north_tex.height);
	main->south_tex.img_ptr = mlx_xpm_file_to_image(main->mlx_ptr,
			main->so_texture_path, &main->south_tex.width,
			&main->south_tex.height);
	main->west_tex.img_ptr = mlx_xpm_file_to_image(main->mlx_ptr,
			main->we_texture_path, &main->west_tex.width,
			&main->west_tex.height);
	if (!main->east_tex.img_ptr || !main->north_tex.img_ptr
		||!main->south_tex.img_ptr || !main->west_tex.img_ptr)
	{
		printer_and_free("path is not valid");
		return ;
	}
	get_data_addr(main);
}

int	read_color(t_texture *texture, int final_addr_index)
{
	int	red_byte;
	int	green_byte;
	int	blue_byte;

	if (texture->endian == 0)
	{
		blue_byte = texture->data[final_addr_index];
		green_byte = texture->data[final_addr_index + 1];
		red_byte = texture->data[final_addr_index + 2];
	}
	if (texture->endian == 1)
	{
		red_byte = texture->data[final_addr_index];
		green_byte = texture->data[final_addr_index + 1];
		blue_byte = texture->data[final_addr_index + 2];
	}
	return (red_byte << 16 | green_byte << 8 | blue_byte);
}

int	get_texture_pixel_color(t_texture *texture, int x, int y)
{
	int	y_offset;
	int	x_offset;
	int	final_addr_index;

	y_offset = y * texture->line_length;
	x_offset = x * (texture->bits_per_pixel / 8);
	final_addr_index = y_offset + x_offset;
	final_addr_index = (y * texture->line_length)
		+ (x * (texture->bits_per_pixel / 8));
	return (read_color(texture, final_addr_index));
}
