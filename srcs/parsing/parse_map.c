#include "cub3d.h"

void	add_node(char *data)
{
	t_control *main;
	t_map	*n;
	t_map	*temp;

	main = control_memo();
	
	n = malloc(sizeof(t_map));
	if(!n)
		free_all();
	add_m_node(n);
	n->next = NULL;
	n->line = data;
	if(main->map == NULL)
		main->map = n;
	else
	{
		temp = main->map;
		while (temp != NULL && temp->next != NULL)
			temp = temp->next;
		temp->next = n;
	}
}

void	change_map_to_data(char *file_nmae)
{
	int 		fd;
	//t_control	*main;
	char		*s;

	//main = control_memo();
	fd = open(file_nmae, O_RDWR , 0644);
	if (fd == -1)
		printer_and_free("Can't opening file");
	s = get_next_line(fd);
	if(s == NULL)
		printer_and_free("Empty file");
	while (s != NULL)
	{
		add_node(strip_newline(s));
		s = get_next_line(fd);
	}
}

static void skep_space(char *s, int *i)
{
	if(s[*i] != '\0' && (s[*i] == ' '  || s[*i] == '\n'))
		(*i)++;
}

int	check_is_texture(char *s, int i, char c1, char c2)
{
	if(s[i] == c1)
	{
		(i)++;
		if(s[i] != '\0' && s[i] == c2)
		{
			(i)++;
			if(s[i] == ' ')
				return(1);
		}
	}
	return(0);
}

static	int is_texture(char *s, int i)
{
	if(check_is_texture(s, i, 'N', 'O'))
		return(1);
	if(check_is_texture(s, i, 'S', 'O'))
		return(1);
	if(check_is_texture(s, i, 'W', 'E'))
		return(1);
	if(check_is_texture(s, i, 'E', 'A'))
		return(1);
	return(0);
}

static	int	check_is_color(char *s, int i, char c)
{
	if(s[i] == c)
	{
		(i)++;
		if(s[i] != '\0' && s[i] == ' ')
			return(1);
	}
	return(0);
}
static int is_color(char *s, int i)
{
	if(check_is_color(s, i, 'F'))
		return(1);
	if(check_is_color(s, i, 'C'))
		return(1);
	return(0);
}

void	validit_color(char *s, int *i, char c)
{
	char	temp[4];
	int		x;
	int		y;
	t_control *m_cnt;

	x = 0;
	m_cnt =  control_memo();
	while(x < 3)
	{
		skep_space(s, i);
		y = 0;
		if(s[*i] == ',')
			printer_and_free("Invalid color format");
		while(s[*i] != '\0' && s[*i] != ',')
		{
			if(s[*i] == ' ')
				skep_space(s, i);
			else
			{
				if((!(s[*i] >= 48 && s[*i] <= 57)) && (!(s[*i] == '\n' && s[*i + 1] == '\0')))
					printer_and_free("Invalid color format");
				temp[y] = s[*i];
				(*i)++;
				y++;
			}
		}
		temp[y + 1] = '\0';
		if(ft_atoi(temp) == INT_MAX || (s[*i] == ',' && x == 2) || (s[*i] == '\0' && x < 2))
			printer_and_free("Invalid color format");
		if(s[*i] == ',')
			(*i)++;	
		if (c == 'F')
			m_cnt->color.Floor[x] = ft_atoi(temp);
		else if(c == 'C')
			m_cnt->color.Ceiling[x] = ft_atoi(temp);
		x++;	
	}
}

void	validit_texture(char *s, int *i, int *f)
{
	const char *sc = "xpm";
	skep_space(s, i);
	*f = *i;
	validit_filename(s + (*i), sc);
	while(s[*i] != '\0')
	{
		if(s[*i] == ' ')
		{
			skep_space(s, i);
			if(s[*i] == '\0')
				break;
			else
				printer_and_free("Invalid texture format");
		}
		(*i)++;
	}
}

void	validit_texture_and_color()
{
	t_control	*main;
	t_map		*head;
	int			i;
	char		*s;
	int color = 0;
	int texture = 0;
	int f = 0;
	int c = 0;
	int w = 0;
	int n = 0;
	int e = 0;
	int so = 0;
	int		copy_i;
	int		l = 0;

	copy_i = 0;
	main = control_memo();
	head = main->map;
	while (head != NULL)
	{
		i = 0;
		s = head->line;

		while(s[i] != '\0')
		{
			while((s[i] == ' ' || s[i] == '\n') && s[i] != '\0')
				skep_space(s, &i);
			if(s[i] == '\0')
				break;
			color = is_color(s, i);
			texture = is_texture(s, i);
			if(color == 0 && texture == 0 && (s[i] != '0' && s[i] != '1'))
				printer_and_free("Invalid Data");
			if(color == 1)
			{
				if(s[i] == 'F')
				{
					i++;
					validit_color(s, &i, 'F');
					f++;
					if(f > 1)
						printer_and_free("Invalid color format");
				}
				else if(s[i] == 'C')
				{
					i++;
					validit_color(s, &i, 'C');
					c++;
					if(c > 1)
						printer_and_free("Invalid color format");
				}
			}
			else if(texture == 1)
			{
				if(s[i] == 'N')
				{
					i += 2;
					validit_texture(s, &i, &copy_i);
					n++;
					if(n > 1)
						printer_and_free("Invalid texture format");
				}
				else if(s[i] == 'S')
				{
					i += 2;
					validit_texture(s, &i, &copy_i);
					so++;
					if(so > 1)
						printer_and_free("Invalid texture format");
				}
				else if(s[i] == 'W')
				{
					i += 2;
					validit_texture(s, &i, &copy_i);
					w++;
					if(w > 1)
						printer_and_free("Invalid texture format");
				}
				else if(s[i] == 'E')
				{
					i += 2;
					validit_texture(s, &i, &copy_i);
					e++;
					if(e > 1)
						printer_and_free("Invalid texture format");
				}
				main->texture[l] = ft_strdup(s + copy_i);
				l++;
			}
			else
			{
				if(f == 0 || c == 0)
					printer_and_free("Invalid color format");
				if(e == 0 || n == 0 || w == 0 || so == 0)
					printer_and_free("Invalid texture format");
				break;
			}
		}
		head = head->next;
	}
}