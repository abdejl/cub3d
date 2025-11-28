#include "cub3d.h"

char	*trim_leading_spaces(char *line)
{
	if (!line)
		return (NULL);
	while (*line == ' ' || *line == '\t')
		line++;
	return (line);
}

int	is_empty_line(char *line)
{
	char	*trimmed_line;

	trimmed_line = trim_leading_spaces(line);
	if (!trimmed_line || *trimmed_line == '\0' || *trimmed_line == '\n')
		return (1);
	return (0);
}

int	is_map_line(char *line)
{
	char	*trimmed_line;

	trimmed_line = trim_leading_spaces(line);
	if (*trimmed_line == '1' || *trimmed_line == '0')
		return (1);
	if (*line == ' ') 
		return (1);
	return (0);
}

static void	parse_texture(t_control *main, char *line, char **storage)
{
	char	*path;
	
    (void)main;
	if (*storage != NULL)
		printer_and_free("Duplicate texture element found");
	
	path = trim_leading_spaces(line + 2);
	path = trim_leading_spaces(path);
	
	if (!path || *path == '\n' || *path == '\0')
		printer_and_free("Missing texture path");
		
	*storage = ft_strdup(path); 
	if (!*storage)
		printer_and_free("Malloc failed for texture path");
	add_m_node(*storage);	
	validit_filename(*storage, "xpm");
}

static void free_split(char **split)
{
    int i = 0;
    while (split[i])
    {
        free(split[i]);
        i++;
    }
    free(split);
}

static void parse_color(t_control *main, char *line, int *storage)
{
    char	**colors;
    int		r;
	int		g;
	int		b;

	(void)main;
    if (*storage != -1)
        printer_and_free("Duplicate color element found");
    line = trim_leading_spaces(line + 1);
    colors = ft_split(line, ',');
    if (!colors || !colors[0] || !colors[1] || !colors[2])
    {
        free_split(colors);
        printer_and_free("Invalid color format (missing values)");
    }
    r = ft_atoi(colors[0]);
    g = ft_atoi(colors[1]);
    b = ft_atoi(colors[2]);
    free_split(colors);
    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
        printer_and_free("Color value out of range (0-255)");
    *storage = (r << 16) | (g << 8) | b;
}

static void	parse_and_store_element(char *line, t_control *main)
{
	char *trimmed_line;

	trimmed_line = trim_leading_spaces(line);

	if (ft_strncmp(trimmed_line, "NO ", 3) == 0)
		parse_texture(main, trimmed_line, &main->no_texture_path);
	else if (ft_strncmp(trimmed_line, "SO ", 3) == 0)
		parse_texture(main, trimmed_line, &main->so_texture_path);
	else if (ft_strncmp(trimmed_line, "WE ", 3) == 0)
		parse_texture(main, trimmed_line, &main->we_texture_path);
	else if (ft_strncmp(trimmed_line, "EA ", 3) == 0)
		parse_texture(main, trimmed_line, &main->ea_texture_path);
	else if (ft_strncmp(trimmed_line, "F ", 2) == 0)
		parse_color(main, trimmed_line, &main->floor_color);
	else if (ft_strncmp(trimmed_line, "C ", 2) == 0)
		parse_color(main, trimmed_line, &main->ceiling_color);
	else
		printer_and_free("Invalid element identifier in file");
	
	main->elements_found++;
}


static void	init_parser_state(t_control *main)
{
	main->no_texture_path = NULL;
	main->so_texture_path = NULL;
	main->we_texture_path = NULL;
	main->ea_texture_path = NULL;
	main->floor_color = -1;
	main->ceiling_color = -1; 
	main->elements_found = 0;
	main->map = NULL;
}

void	read_and_parse_file(char *file_name)
{
	int			fd;
	char		*line;
	t_control	*main;
	int			map_started;

	main = control_memo();
	init_parser_state(main);
	map_started = 0;
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		printer_and_free("Can't opening file");
	
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (is_empty_line(line))
		{
			if (map_started)
				printer_and_free("Empty line in or after map");
			free(line);
		}
		else if (is_map_line(line))
		{
			if (main->elements_found < 6)
				printer_and_free("Map line found before all 6 elements");
			map_started = 1;
			add_node(strip_newline(line)); 
		}
		else
		{
			if (map_started)
				printer_and_free("Element found after map started");
			parse_and_store_element(line, main);
			free(line);
		}
		line = get_next_line(fd);
	}
	close(fd);
	if (main->elements_found < 6)
		printer_and_free("Missing one or more map elements");
	if (map_started == 0)
		printer_and_free("No map found in file");
}
