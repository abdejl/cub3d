/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-bar <yael-bar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 22:13:13 by yael-bar          #+#    #+#             */
/*   Updated: 2025/12/09 22:16:11 by yael-bar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	process_color(char *s, int *i, t_counters *cnt)
{
	if (s[*i] == 'F')
		handle_f_color(s, i, cnt);
	else if (s[*i] == 'C')
		handle_c_color(s, i, cnt);
}

void	handle_f_color(char *s, int *i, t_counters *cnt)
{
	(*i)++;
	validit_color(s, i, 'F');
	cnt->f++;
	if (cnt->f > 1)
		printer_and_free("Invalid color format");
}

void	handle_c_color(char *s, int *i, t_counters *cnt)
{
	(*i)++;
	validit_color(s, i, 'C');
	cnt->c++;
	if (cnt->c > 1)
		printer_and_free("Invalid color format");
}
