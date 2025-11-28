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
