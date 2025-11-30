/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abjellal <abjellal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 11:57:51 by abjellal          #+#    #+#             */
/*   Updated: 2025/11/30 11:58:01 by abjellal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update_player_movement(t_control *main)
{
	if (main->keys.w == 1)
		move_player_forward(main);
	if (main->keys.s == 1)
		move_player_backward(main);
	if (main->keys.a == 1)
		move_player_left(main);
	if (main->keys.d == 1)
		move_player_right(main);
	if (main->keys.left_arrow == 1)
		rotate_player(main, -1);
	if (main->keys.right_arrow == 1)
		rotate_player(main, 1);
}
