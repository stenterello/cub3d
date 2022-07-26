/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 18:32:06 by ddelladi          #+#    #+#             */
/*   Updated: 2022/07/26 12:53:56 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_view(int keycode, t_rules *rules)
{
	if (keycode == 65361)
	{
		rules->player.dir -= ANGLE_UNIT * 5;
		if (rules->player.dir < 0)
			rules->player.dir = 2 * PI;
	}
	else if (keycode == 65363)
	{
		rules->player.dir += ANGLE_UNIT * 5;
		if (rules->player.dir > 2 * PI)
			rules->player.dir = 0;
	}
	rules->player.d_x = cos(rules->player.dir) * 5;
	rules->player.d_y = -sin(rules->player.dir) * 5;
}

int	press(int keycode, t_rules *rules)
{
	if (keycode == 65307)
	{
		mlx_destroy_window(rules->mlx.mlx, rules->mlx.mlx_win);
		free_rules(rules);
		exit(0);
	}
	else if (keycode == 119)
		rules->keys.w_pressed = 1;
	else if(keycode == 97)
		rules->keys.a_pressed = 1;
	else if (keycode == 115)
		rules->keys.s_pressed = 1;
	else if (keycode == 100)
		rules->keys.d_pressed = 1;
	else if (keycode == 65361)
		rules->keys.l_pressed = 1;
	else if (keycode == 65363)
		rules->keys.r_pressed = 1;
	if (rules->keys.l_pressed)
		rules->player.dir += ANGLE_UNIT * 5;
	if (rules->keys.r_pressed)
		rules->player.dir -= ANGLE_UNIT * 5;
	if (rules->player.dir < 0)
		rules->player.dir = 2 * PI;
	if (rules->player.dir > 2 * PI)
		rules->player.dir = 0;
	return (0);
}

int	release(int keycode, t_rules *rules)
{
	if (keycode == 65307)
	{
		mlx_destroy_window(rules->mlx.mlx, rules->mlx.mlx_win);
		free_rules(rules);
		exit(0);
	}
	else if (keycode == 119)
		rules->keys.w_pressed = 0;
	else if(keycode == 97)
		rules->keys.a_pressed = 0;
	else if (keycode == 115)
		rules->keys.s_pressed = 0;
	else if (keycode == 100)
		rules->keys.d_pressed = 0;
	else if (keycode == 65361)
		rules->keys.l_pressed = 0;
	else if (keycode == 65363)
		rules->keys.r_pressed = 0;
	return (0);
}

void	add_events(t_rules *rules)
{
	mlx_hook(rules->mlx.mlx_win, 2, 1L << 0, press, rules);
	mlx_hook(rules->mlx.mlx_win, 03, 1L << 1, release, rules);
}
