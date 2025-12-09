/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-bar <yael-bar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 22:11:36 by yael-bar          #+#    #+#             */
/*   Updated: 2025/12/09 22:15:14 by yael-bar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	process_texture(char *s, int *i, int *copy_i, t_counters *cnt)
{
	if (s[*i] == 'N')
		handle_n_texture(s, i, copy_i, cnt);
	else if (s[*i] == 'S')
		handle_so_texture(s, i, copy_i, cnt);
	else if (s[*i] == 'W')
		handle_w_texture(s, i, copy_i, cnt);
	else if (s[*i] == 'E')
		handle_e_texture(s, i, copy_i, cnt);
}

void	handle_n_texture(char *s, int *i, int *copy_i, t_counters *cnt)
{
	t_control	*main;

	main = control_memo();
	(*i) += 2;
	validit_texture(s, i, copy_i);
	cnt->n++;
	main->no_texture_path = ft_strdup(s + *copy_i);
	if (cnt->n > 1)
		printer_and_free("Invalid texture format");
}

void	handle_so_texture(char *s, int *i, int *copy_i, t_counters *cnt)
{
	t_control	*main;

	main = control_memo();
	(*i) += 2;
	validit_texture(s, i, copy_i);
	cnt->so++;
	main->so_texture_path = ft_strdup(s + *copy_i);
	if (cnt->so > 1)
		printer_and_free("Invalid texture format");
}

void	handle_w_texture(char *s, int *i, int *copy_i, t_counters *cnt)
{
	t_control	*main;

	main = control_memo();
	(*i) += 2;
	validit_texture(s, i, copy_i);
	cnt->w++;
	main->we_texture_path = ft_strdup(s + *copy_i);
	if (cnt->w > 1)
		printer_and_free("Invalid texture format");
}

void	handle_e_texture(char *s, int *i, int *copy_i, t_counters *cnt)
{
	t_control	*main;

	main = control_memo();
	(*i) += 2;
	validit_texture(s, i, copy_i);
	cnt->e++;
	main->ea_texture_path = ft_strdup(s + *copy_i);
	if (cnt->e > 1)
		printer_and_free("Invalid texture format");
}
