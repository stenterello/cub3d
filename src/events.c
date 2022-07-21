/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 18:32:06 by ddelladi          #+#    #+#             */
/*   Updated: 2022/07/21 22:05:27 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_player(int keycode, t_rules *rules)
{
	if (keycode == 119 && !colliding(rules, "up"))
		rules->player.y -= rules->block_width / 10;
	else if (keycode == 115 && !colliding(rules, "down"))
		rules->player.y += rules->block_width / 10;
	else if (keycode == 97 && !colliding(rules, "left"))
		rules->player.x -= rules->block_width / 10;
	else if (keycode == 100 && !colliding(rules, "right"))
		rules->player.x += rules->block_width / 10;
	draw_view_rays(rules);
}

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
	draw_view_rays(rules);
}

int	events(int keycode, t_rules *rules) // i keycode sono attualmente per linux... se possibile scriverli qui: { TASTO : linux : mac }
																											// { ESC   : 65307 :     }
{
	if (keycode == 65307)
	{
		mlx_destroy_window(rules->mlx, rules->mlx_win);
		free_rules(rules);
		exit(0);
	}
	else if (keycode == 119 || keycode == 97 || keycode == 115 || keycode == 100)
		move_player(keycode, rules);
	else if (keycode == 65361 || keycode == 65363)
		move_view(keycode, rules);
	printf("keycode: %d\n", keycode);
	return (0);
}

void	add_events(t_rules *rules)
{
	mlx_hook(rules->mlx_win, 2, 1L << 0, events, rules);
}
