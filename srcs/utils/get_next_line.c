#include "cub3d.h"

char 	*stock_line(int fd, char* line)
{
	int		bytes_read;
	char	*buffer;

	buffer = malloc(sizeof(char)* BUFFER_SIZE + 1);
	if(buffer == NULL)
		free_all();
	buffer[0] = '\0';
	bytes_read = 1;
	while(bytes_read > 0 && ft_strchr(buffer, '\n') != 1)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if(bytes_read == -1)
			free_all();
		buffer[bytes_read] = '\0';
		line = ft_strjoin(line, buffer);
	}
	free(buffer);
	return (line);
}

int	get_size(char *line)
{
	int	i;

	i = 0;
	while(line[i] != '\0' && line[i] != '\n')
	{
		i++;
	}
	return (i);
}

char	*get_good_line(char *line)
{
	int		i;
	int 	size;
	char	*good_line;

	i = 0;
	if(line[i] == '\0')
		return (NULL);
	size = get_size(line);
	good_line = malloc(size + 2);
	if(good_line == NULL)
		free_all();
	add_m_node(good_line);
	while(line[i] != '\0' && line[i] != '\n')
	{
		good_line[i] = line[i];
		i++;
	}
	if(line[i] == '\n' && i == 0)
	{
		good_line[i] = '\n';
		i++;
	}
	good_line[i] = '\0';
	return (good_line);
}
char  *fix_line(char *line)
{
	char 	*new_line;
	int		size;
	int		i;

	size = get_size(line);
	if(line[size] == '\0')
	{
		free(line);
		return (NULL);
	}
	new_line = malloc((ft_strlen(line) - size));
	if(new_line == NULL)
		free_all();
	i = 0;
	size++;
	while(line[size])
	{
		new_line[i] = line[size];
		size++;
		i++;
	}
	new_line[i] = '\0';
	free(line);
	return (new_line);
}

char 	*get_next_line(int fd)
{
	static	char *line = NULL;
	char	*good_line;

	line = stock_line(fd, line);
	good_line = get_good_line(line);
	line = fix_line(line);
	return (good_line);
}