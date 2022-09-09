/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 16:45:37 by ddelladi          #+#    #+#             */
/*   Updated: 2022/09/09 11:50:11 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	mouse_exit(t_rules *rules)
{
	mlx_destroy_window(rules->mlx.mlx, rules->mlx.mlx_win);
	exit(0);
	return (0);
}

void	add_events(t_rules *rules)
{
	mlx_hook(rules->mlx.mlx_win, 2, 1L << 0, press, rules);
	mlx_hook(rules->mlx.mlx_win, 3, 1L << 1, release, rules);
	mlx_hook(rules->mlx.mlx_win, 17, 0, mouse_exit, rules);
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
		rules->player.dir += ANGLE_UNIT * 20;
	if (rules->keys.r_pressed)
		rules->player.dir -= ANGLE_UNIT * 20;
	if (rules->player.dir < 0)
		rules->player.dir = 2 * M_PI;
	if (rules->player.dir > 2 * M_PI)
		rules->player.dir = 0;
	rules->player.d_x = cos(rules->player.dir);
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
	rules->player.gun.counted = 0;
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
		rules->n_frames = 1;
		update_pov(rules);
		game(rules);
		if (rules->keys.shift_pressed)
			move_gun(&rules->player.gun, 5);
		else
			move_gun(&rules->player.gun, 10);
	}
	else
		rules->n_frames++;
	return (0);
}
