/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abjellal <abjellal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 09:06:35 by abjellal          #+#    #+#             */
/*   Updated: 2025/12/14 09:17:19 by abjellal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_control	*control_memo(void)
{
	static t_control	control;

	return (&control);
}

int	main(int ac, char *av[])
{
	t_control	*main_control;

	main_control = control_memo();
	if (check_argm(ac))
	{
		printer_and_free("Invalid number of arguments");
	}
	else
	{
		parsing(main_control, av[1]);
		mlx(main_control);
	}
	return (0);
}
