#include "cub3d.h"

/**
 trims leading whitespace from a string.
 it returns a pointer to the first non-space character.
 */
char	*trim_leading_spaces(char *line)
{
	if (!line)
		return (NULL);
	while (*line == ' ' || *line == '\t')
		line++;
	return (line);
}

/**
	Checks if a line is empty or contains only whitespace.
 */
int	is_empty_line(char *line)
{
	char	*trimmed_line;

	trimmed_line = trim_leading_spaces(line);
	if (!trimmed_line || *trimmed_line == '\0' || *trimmed_line == '\n')
		return (1);
	return (0);
}

/*
	Checks if a line looks like a map line (starts with '1', '0', or ' ').
	a line with spaces then '1' is a map line.
 */
int	is_map_line(char *line)
{
	char	*trimmed_line;

	trimmed_line = trim_leading_spaces(line);
	if (*trimmed_line == '1' || *trimmed_line == '0')
		return (1);
	// Allow lines that start with spaces (part of map)
	if (*line == ' ') 
		return (1);
	return (0);
}

/*
 	Parses and stores a texture path.
	Replaces logic from validit_texture.
 */
static void	parse_texture(t_control *main, char *line, char **storage)
{
	char	*path;
	
    (void)main;
	if (*storage != NULL)
		printer_and_free("Duplicate texture element found");
	
	path = trim_leading_spaces(line + 2); // Skip NO, SO...
	path = trim_leading_spaces(path);
	
	if (!path || *path == '\n' || *path == '\0')
		printer_and_free("Missing texture path");
		
	*storage = ft_strdup(path); 
	if (!*storage)
		printer_and_free("Malloc failed for texture path");
	add_m_node(*storage);	
	validit_filename(*storage, "xpm");
}

/**
	Parses and stores an F/C color.
	Replaces logic from validit_color.
 */
static void	parse_color(t_control *main, char *line, int *storage)
{
	//char	**rgb_parts;
	int	r;
	int g;
	int b;
	//int		i;
    (void)main;
	
	if (*storage != -1)
		printer_and_free("Duplicate color element found");

	line = trim_leading_spaces(line + 1); // Skip "F" or "C"
	line = trim_leading_spaces(line);
	//char *rgb_string = line;
	r = 100;
	g = 100;
	b = 100;
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		printer_and_free("Color value out of range (0-255)");
	*storage = (r << 16) + (g << 8) + b; // Combine into a single int
}

	//Parses a single element line and stores it in t_control.
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


/**
	initializes parser state variables in t_control.
 */
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

/**
 * reads the .cub file, parses elements, and builds the map list.
 * this function replaces change_map_to_data.
 */
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
			if (map_started) // Empty lines inside or after the map are an error
				printer_and_free("Empty line in or after map");
			free(line);
		}
		else if (is_map_line(line))
		{
			if (main->elements_found < 6) // All 6 must be found first
				printer_and_free("Map line found before all 6 elements");
			map_started = 1;
			// ONLY map lines are added to the list
			add_node(strip_newline(line)); 
		}
		else // If it's not empty and not a map, it must be an element
		{
			if (map_started)
				printer_and_free("Element found after map started");
			parse_and_store_element(line, main);
			free(line); // We processed it, so we free it
		}
		line = get_next_line(fd);
	}
	close(fd);
	if (main->elements_found < 6)
		printer_and_free("Missing one or more map elements");
	if (map_started == 0)
		printer_and_free("No map found in file");
}
