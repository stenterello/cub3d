/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 11:59:10 by gimartin          #+#    #+#             */
/*   Updated: 2022/10/07 15:06:14 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update_pov_supp(t_rules *rules)
{
	if (rules->player.dir == (double)M_PI)
		rules->player.d_y = 0;
	else
		rules->player.d_y = -sin(rules->player.dir);
	if (rules->keys.shift_pressed)
		rules->player.speed = SPEED * 2;
	else
		rules->player.speed = SPEED;
}

void	update_pov(t_rules *rules)
{
	if (rules->keys.w_pressed)
		move_player(rules, "up");
	if (rules->keys.a_pressed)
		move_player(rules, "left");
	if (rules->keys.s_pressed)
		move_player(rules, "down");
	if (rules->keys.d_pressed)
		move_player(rules, "right");
	if (rules->keys.l_pressed)
		rules->player.dir = increment_angle(rules->player.dir, 40);
	if (rules->keys.r_pressed)
		rules->player.dir = decrement_angle(rules->player.dir, 40);
	rules->player.d_x = cos(rules->player.dir);
	update_pov_supp(rules);
}

int	loop_events(t_rules *rules)
{
	if (!(rules->n_frames % 170))
	{
		update_pov(rules);
		game(rules);
		rules->n_frames++;
	}
	else
		rules->n_frames++;
	return (0);
}
