/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validit_texture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-bar <yael-bar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 00:43:15 by yael-bar          #+#    #+#             */
/*   Updated: 2025/12/09 01:18:43 by yael-bar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_is_texture(char *s, int i, char c1, char c2)
{
	if (s[i] == c1)
	{
		(i)++;
		if (s[i] != '\0' && s[i] == c2)
		{
			(i)++;
			if (s[i] == ' ')
				return (1);
		}
	}
	return (0);
}

int	is_texture(char *s, int i)
{
	if (check_is_texture(s, i, 'N', 'O'))
		return (1);
	if (check_is_texture(s, i, 'S', 'O'))
		return (1);
	if (check_is_texture(s, i, 'W', 'E'))
		return (1);
	if (check_is_texture(s, i, 'E', 'A'))
		return (1);
	return (0);
}

void	validit_texture(char *s, int *i, int *f)
{
	const char	*sc = "xpm";

	while (s[*i] != '\0' && (s[*i] == ' ' || s[*i] == '\n'))
		skep_space(s, i);
	*f = *i;
	validit_filename(s + (*i), sc);
	while (s[*i] != '\0')
	{
		if (s[*i] == ' ')
		{
			skep_space(s, i);
			if (s[*i] == '\0')
				break ;
			else
				printer_and_free("Invalid texture format");
		}
		(*i)++;
	}
}
