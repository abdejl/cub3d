/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-bar <yael-bar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 10:57:43 by yael-bar          #+#    #+#             */
/*   Updated: 2025/12/12 10:57:44 by yael-bar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_argm(int ac)
{
	if (ac != 2)
		return (1);
	return (0);
}

void	printer_and_free(char *s)
{
	printf("Error\n");
	printf("%s\n", s);
	free_all();
}
