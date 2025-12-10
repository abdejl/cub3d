/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_chars.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abjellal <abjellal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 14:03:42 by abjellal          #+#    #+#             */
/*   Updated: 2025/12/10 14:20:51 by abjellal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_valid_char(char c)
{
	return (c == ' ' || c == '1' || c == '0' || c == 'N' || c == 'S'
		|| c == 'E' || c == 'W');
}

static int	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

void	init_player(t_control *main, int x, int y)
{
	main->player.x = x + 0.5;
	main->player.y = y + 0.5;
	main->player.direction = main->map_grid[y][x];
}

void	validate_map_characters(t_control *main)
{
	int	x;
	int	y;
	int	player_count;

	y = 0;
	player_count = 0;
	while (main->map_grid && main->map_grid[y])
	{
		x = 0;
		while (main->map_grid[y][x])
		{
			if (!is_valid_char(main->map_grid[y][x]))
				printer_and_free("Invalid character found in map");
			if (is_player_char(main->map_grid[y][x]))
			{
				init_player(main, x, y);
				player_count++;
			}
			x++;
		}
		y++;
	}
	if (player_count != 1)
		printer_and_free("Map must contain exactly one player start position");
}
