#include "cub3d.h"

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