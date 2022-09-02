/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 16:45:37 by ddelladi          #+#    #+#             */
/*   Updated: 2022/09/02 13:48:33 by ddelladi         ###   ########.fr       */
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
	// float	ray_sin;
	// float	ray_cos;

	// ray_sin = sin(rules->player.dir);
	// ray_cos = cos(rules->player.dir);
	if (rules->keys.w_pressed && !wall_coll(*rules, 0, -1))
	{
		rules->player.y -= 1;
	}
	if (rules->keys.a_pressed && !wall_coll(*rules, -1, 0))
		rules->player.x -= 1;
	if (rules->keys.s_pressed && !wall_coll(*rules, 0, 1))
		rules->player.y += 1;
	if (rules->keys.d_pressed && !wall_coll(*rules, 1, 0))
		rules->player.x += 1;
	if (rules->keys.l_pressed)
	{
		rules->player.dir += 0.025;
		if (rules->player.dir > 2 * M_PI)
			rules->player.dir = 0;
	}
	if (rules->keys.r_pressed)
	{
		rules->player.dir -= 0.025;
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
		game(rules);
	}
	return (0);
}
