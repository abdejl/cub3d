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
				main->player.x = x + 0.5;
				main->player.y = y + 0.5;
				main->player.direction = main->map_grid[y][x];
				player_count++;
			}
			x++;
		}
		y++;
	}
	if (player_count != 1)
		printer_and_free("Map must contain exactly one player start position");
}

void	validit_filename(char *s, const char *sc)
{
	int	i;

	i = 0;
	while(s[i] != '\0')
	{
		if(s[i] == '.' && (s[i + 1] != '\0' && s[i + 1] != '/'))
		{
			if((ft_strncmp(sc, s + (i + 1), 3) != 0) || s[i + 4] != '\0' )
				printer_and_free("Invalid name of file");
			else
				return;
		}
		i++;
	}
		printer_and_free("Invalid name of file");
}