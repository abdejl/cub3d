/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-bar <yael-bar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 22:29:02 by yael-bar          #+#    #+#             */
/*   Updated: 2025/12/10 21:39:02 by yael-bar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	add_node(char *data)
{
	t_control	*main;
	t_map		*n;
	t_map		*temp;

	main = control_memo();
	n = malloc(sizeof(t_map));
	if (!n)
		free_all();
	add_m_node(n);
	n->next = NULL;
	n->line = data;
	if (main->map == NULL)
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
	int		fd;
	char	*s;

	fd = open(file_nmae, O_RDWR, 0644);
	if (fd == -1)
		printer_and_free("Can't opening file");
	s = get_next_line(fd);
	if (s == NULL)
		printer_and_free("Empty file");
	while (s != NULL)
	{
		add_node(strip_newline(s));
		s = get_next_line(fd);
	}
}

void	skep_space(char *s, int *i)
{
	if (s[*i] != '\0' && (s[*i] == ' ' || s[*i] == '\n'))
		(*i)++;
}
