/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validit_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-bar <yael-bar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 00:43:33 by yael-bar          #+#    #+#             */
/*   Updated: 2025/12/09 21:15:19 by yael-bar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	final_color_store(char c)
{
	t_control	*m_cnt;

	m_cnt = control_memo();
	if (c == 'F')
	{
		m_cnt->floor_color = (m_cnt->color.Floor[0] << 16)
			| (m_cnt->color.Floor[1] << 8)
			| m_cnt->color.Floor[2];
	}
	else
	{
		m_cnt->ceiling_color = (m_cnt->color.Ceiling[0] << 16)
			| (m_cnt->color.Ceiling[1] << 8)
			| m_cnt->color.Ceiling[2];
	}
}

static void	is_valid_char(char *s, int *i, int y)
{
	if ((!(s[*i] >= '0' && s[*i] <= '9'))
		&& (!(s[*i] == '\n' && s[*i + 1] == '\0')))
		printer_and_free("Invalid color format");
	if (y >= 3)
		printer_and_free("Invalid color format");
}

static void	validit_number(char *temp, char *s, int *i, int x)
{
	if (ft_atoi(temp) > 255 || (s[*i] == ',' && x == 2) || (s[*i] == '\0'
			&& x < 2))
		printer_and_free("Invalid color format");
	if (s[*i] == ',')
		(*i)++;
}

static void	store_color_value(char *temp, int x, char c)
{
	t_control	*m_cnt;

	m_cnt = control_memo();
	if (c == 'F')
		m_cnt->color.Floor[x] = ft_atoi(temp);
	else if (c == 'C')
		m_cnt->color.Ceiling[x] = ft_atoi(temp);
}

void	validit_color(char *s, int *i, char c)
{
	char	temp[3];
	int		x;
	int		y;

	x = 0;
	while (x < 3)
	{
		while (s[*i] == ' ' || s[*i] == '\n')
			skep_space(s, i);
		y = 0;
		if (s[*i] == ',')
			printer_and_free("Invalid color format");
		while (s[*i] != '\0' && s[*i] != ',')
		{
			is_valid_char(s, i, y);
			if (y < 3)
				temp[y++] = s[*i];
			(*i)++;
		}
		temp[y] = '\0';
		validit_number(temp, s, i, x);
		store_color_value(temp, x, c);
		x++;
	}
	final_color_store(c);
}
