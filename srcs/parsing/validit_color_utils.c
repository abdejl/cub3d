/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validit_color_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-bar <yael-bar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 21:02:08 by yael-bar          #+#    #+#             */
/*   Updated: 2025/12/09 21:06:25 by yael-bar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_is_color(char *s, int i, char c)
{
	if (s[i] == c)
	{
		(i)++;
		if (s[i] != '\0' && (s[i] == ' ' || s[i] == '\t'))
			return (1);
	}
	return (0);
}

int	is_color(char *s, int i)
{
	if (check_is_color(s, i, 'F'))
		return (1);
	if (check_is_color(s, i, 'C'))
		return (1);
	return (0);
}
