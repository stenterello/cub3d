/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gimartin <gimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 11:59:10 by gimartin          #+#    #+#             */
/*   Updated: 2022/09/20 11:59:27 by gimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

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
	if (rules->keys.e_pressed)
		try_open_door(rules);
	restore_gun(rules);
	rules->player.gun.counted = 0;
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
		rules->player.dir += ANGLE_UNIT * 30;
	if (rules->keys.r_pressed)
		rules->player.dir -= ANGLE_UNIT * 30;
	if (rules->player.dir < 0)
		rules->player.dir = 2 * M_PI;
	if (rules->player.dir > 2 * M_PI)
		rules->player.dir = 0;
	rules->player.d_x = cos(rules->player.dir);
	update_pov_supp(rules);
}

void	move_gun(t_gun *gun, int i)
{
	if (gun->counter >= i)
	{
		if (gun->off)
			gun->off = 0;
		else
			gun->off = 10;
		gun->counter = 0;
	}
}

int	loop_events(t_rules *rules)
{
	if (!(rules->n_frames % 170))
	{
		update_pov(rules);
		game(rules);
		if (rules->keys.shift_pressed)
			move_gun(&rules->player.gun, 5);
		else
			move_gun(&rules->player.gun, 10);
		rules->n_frames++;
	}
	else
		rules->n_frames++;
	return (0);
}
