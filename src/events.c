/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 16:45:37 by ddelladi          #+#    #+#             */
/*   Updated: 2022/09/02 16:45:52 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	move(t_rules *rules)
{
	float	ray_sin;
	float	ray_cos;

	ray_sin = sin(rules->player.dir);
	ray_cos = cos(rules->player.dir);
	if (rules->keys.w_pressed)
	{
		if (!colliding(rules, ray_cos, 0, 1))
			rules->player.x += rules->player.d_x * rules->player.speed;
		if (!colliding(rules, 0, ray_sin, 1))
			rules->player.y += rules->player.d_y * rules->player.speed;
	}
	if (rules->keys.a_pressed)
	{
		if (!colliding(rules, ray_sin, 0, 1))
			rules->player.x += rules->player.d_y * rules->player.speed;
		if (!colliding(rules, 0, ray_cos, 0))
			rules->player.y -= rules->player.d_x * rules->player.speed;
	}
	if (rules->keys.s_pressed)
	{
		if (!colliding(rules, ray_cos, 0, 0))
			rules->player.x -= rules->player.d_x * rules->player.speed;
		if (!colliding(rules, 0, ray_sin, 0))
			rules->player.y -= rules->player.d_y * rules->player.speed;
	}
	if (rules->keys.d_pressed)
	{
		if (!colliding(rules, ray_sin, 0, 0))
			rules->player.x -= rules->player.d_y * rules->player.speed;
		if (!colliding(rules, 0, ray_cos, 1))
			rules->player.y += rules->player.d_x * rules->player.speed;
	}
	if (rules->keys.l_pressed)
		rules->player.dir += ANGLE_UNIT * 5;
	if (rules->keys.r_pressed)
		rules->player.dir -= ANGLE_UNIT * 5;
	if (rules->player.dir < 0)
		rules->player.dir = 2 * M_PI;
	if (rules->player.dir > 2 * M_PI)
		rules->player.dir = 0;
	rules->player.d_x = cos(rules->player.dir) * 5;
	if (rules->player.dir == (double)M_PI)
		rules->player.d_y = 0;
	else
		rules->player.d_y = -sin(rules->player.dir) * 5;
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
		rules->player.dir += ANGLE_UNIT * 10;
	if (rules->keys.r_pressed)
		rules->player.dir -= ANGLE_UNIT * 10;
	if (rules->player.dir < 0)
		rules->player.dir = 2 * M_PI;
	if (rules->player.dir > 2 * M_PI)
		rules->player.dir = 0;
	rules->player.d_x = cos(rules->player.dir);
	if (rules->player.dir == (double)M_PI)
		rules->player.d_y = 0;
	else
		rules->player.d_y = -sin(rules->player.dir);
}

int	loop_events(t_rules *rules)
{
	if (!(rules->n_frames % 30))
	{
		rules->n_frames = 0;
		update_pov(rules);
		game(rules);
	}
	return (0);
}
