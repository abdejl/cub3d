/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abjellal <abjellal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 12:10:59 by abjellal          #+#    #+#             */
/*   Updated: 2025/11/30 12:10:59 by abjellal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*strip_newline(char *line)
{
	int	len;

	if (!line)
		return (NULL);
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	return (line);
}

typedef struct s_flood
{
	char	**map;
	int		height;
}	t_flood;

static void	flood_fill(t_flood *f, int x, int y)
{
	if (y < 0 || y >= f->height || x < 0 || x >= (int)ft_strlen(f->map[y])
		|| f->map[y][x] == ' ')
	{
		printer_and_free("Map is not enclosed by walls");
	}
	if (f->map[y][x] == '1' || f->map[y][x] == 'V')
		return ;
	f->map[y][x] = 'V';
	flood_fill(f, x + 1, y);
	flood_fill(f, x - 1, y);
	flood_fill(f, x, y + 1);
	flood_fill(f, x, y - 1);
}

static void	init_map(char **tmp_map, int height, t_flood *flood)
{
	tmp_map[height] = NULL;
	flood->map = tmp_map;
	flood->height = height;
}

int	check_map_enclosure(t_control *main)
{
	t_flood	flood;
	char	**tmp_map;
	int		i;
	int		height;

	height = 0;
	while (main->map_grid[height])
		height++;
	tmp_map = malloc(sizeof(char *) * (height + 1));
	if (!tmp_map)
		printer_and_free("Malloc failed for flood fill");
	add_m_node(tmp_map);
	i = 0;
	while (i < height)
	{
		tmp_map[i] = ft_strdup(main->map_grid[i]);
		if (!tmp_map[i])
			printer_and_free("Malloc failed for flood fill");
		add_m_node(tmp_map[i]);
		i++;
	}
	init_map(tmp_map, height, &flood);
	flood_fill(&flood, (int)main->player.x, (int)main->player.y);
	return (1);
}

void	validate_map_enclosure(t_control *main)
{
	check_map_enclosure(main);
}
