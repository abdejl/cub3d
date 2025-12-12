/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validit_texture_color.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-bar <yael-bar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 22:14:01 by yael-bar          #+#    #+#             */
/*   Updated: 2025/12/09 22:17:04 by yael-bar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_counters(void)
{
	t_control	*main;
	t_counters	*cnt;

	main = control_memo();
	cnt = &main->cnt;
	cnt->f = 0;
	cnt->c = 0;
	cnt->w = 0;
	cnt->n = 0;
	cnt->e = 0;
	cnt->so = 0;
}

static void	check_final_validity(t_counters *cnt)
{
	if (cnt->f == 0 || cnt->c == 0)
		printer_and_free("Invalid color format");
	if (cnt->e == 0 || cnt->n == 0 || cnt->w == 0 || cnt->so == 0)
		printer_and_free("Invalid texture format");
}

static void	process_line_char(char *s, int *i, int *copy_i, t_counters *cnt)
{
	int	color;
	int	texture;

	color = is_color(s, *i);
	texture = is_texture(s, *i);
	if (color == 0 && texture == 0 && (s[*i] != '0' && s[*i] != '1'))
		printer_and_free("Invalid Data");
	if (color == 1)
		process_color(s, i, cnt);
	else if (texture == 1)
		process_texture(s, i, copy_i, cnt);
	else
		check_final_validity(cnt);
}

static void	process_map_line(char *s, int *copy_i, t_counters *cnt)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		while ((s[i] == ' ' || s[i] == '\n' || s[i] == '\t') && s[i] != '\0')
			skep_space(s, &i);
		if (s[i] == '\0')
			break ;
		process_line_char(s, &i, copy_i, cnt);
		if (is_color(s, i) == 0 && is_texture(s, i) == 0)
			break ;
	}
}

void	validit_texture_and_color(void)
{
	t_control	*main;
	t_map		*head;
	int			copy_i;

	copy_i = 0;
	main = control_memo();
	init_counters();
	head = main->map;
	while (head != NULL)
	{
		process_map_line(head->line, &copy_i, &main->cnt);
		head = head->next;
	}
}
