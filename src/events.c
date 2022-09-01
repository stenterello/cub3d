/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 16:45:37 by ddelladi          #+#    #+#             */
/*   Updated: 2022/09/01 17:30:08 by ddelladi         ###   ########.fr       */
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
	mlx_hook(rules->mlx.mlx_win, 3, 1L << 0, release, rules);
	mlx_hook(rules->mlx.mlx_win, 17, 0, mouse_exit, rules);
}

int	wall(t_rules rules, float x, float y)
{
	if ((int)(x / rules.map.block_width) < 0 || (int)(y / rules.map.block_width) < 0
		|| (int)(x / rules.map.block_width) > rules.map.map_height_len[0] - 1
		|| (int)(y / rules.map.block_width) > rules.map.map_height_len[1] - 1)
		return (1);
	if (rules.map.map[(int)(y / rules.map.block_width)][(int)(x / rules.map.block_width)] == '1')
		return (1);
	return (0);
}

int	wall_coll(t_rules rules, float x, float y)
{
	if (x == 1)
		rules.player.x += (rules.map.block_width / 10) + 1;
	else if (x == -1)
		rules.player.x -= ((rules.map.block_width / 10) + 1);
	else if (y == 1)
		rules.player.y += (rules.map.block_width / 10) + 1;
	else if (y == -1)
		rules.player.y -= ((rules.map.block_width / 10) + 1);
	if (wall(rules, rules.player.x, rules.player.y))
		return (1);
	printf("x: %f\ny: %f\n", rules.player.x, rules.player.y);
	return (0);
}

void	move(t_rules *rules)
{
	if (rules->keys.w_pressed && !wall_coll(*rules, 0, -1))
		rules->player.y -= 1;
	if (rules->keys.a_pressed && !wall_coll(*rules, -1, 0))
		rules->player.x -= 1;
	if (rules->keys.s_pressed && !wall_coll(*rules, 0, 1))
		rules->player.y += 1;
	if (rules->keys.d_pressed && !wall_coll(*rules, 1, 0))
		rules->player.x += 1;
	if (rules->keys.l_pressed)
	{
		rules->player.dir += 0.05;
		if (rules->player.dir > 2 * M_PI)
			rules->player.dir = 0;
	}
	if (rules->keys.r_pressed)
	{
		rules->player.dir -= 0.05;
		if (rules->player.dir < 0)
			rules->player.dir = 2 * M_PI;
	}
}

int	loop_events(t_rules *rules)
{
	if (!(rules->n_frames % 90))
	{
		rules->n_frames = 0;
		move(rules);
		minimap(rules);
	}
	return (0);
}
