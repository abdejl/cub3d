/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abjellal <abjellal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 15:13:53 by abjellal          #+#    #+#             */
/*   Updated: 2025/12/04 15:13:53 by abjellal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	get_map_dimensions(t_map *map_list, int *height, int *width)
{
	int		current_width;
	t_map	*temp;

	*height = 0;
	*width = 0;
	temp = map_list;
	while (temp)
	{
		(*height)++;
		current_width = ft_strlen(temp->line);
		if (current_width > *width)
			*width = current_width;
		temp = temp->next;
	}
}

void	create_map_grid(t_control *main)
{
	int		height;
	int		width;
	int		y;
	t_map	*current_node;

	get_map_dimensions(main->map, &height, &width);
	main->map_grid = malloc(sizeof(char *) * (height + 1));
	if (!main->map_grid)
		printer_and_free("Malloc failed for rows");
	add_m_node(main->map_grid);
	y = 0;
	current_node = main->map;
	while (y < height)
	{
		main->map_grid[y] = malloc(sizeof(char) * (width + 1));
		if (!main->map_grid[y])
			printer_and_free("Malloc failed for column");
		add_m_node(main->map_grid[y]);
		ft_strlcpy(main->map_grid[y], current_node->line, width + 1);
		y++;
		current_node = current_node->next;
	}
	main->map_grid[height] = NULL;
}
