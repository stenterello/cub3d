/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 16:45:37 by ddelladi          #+#    #+#             */
/*   Updated: 2022/08/26 19:24:49 by ddelladi         ###   ########.fr       */
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

void	move(t_rules *rules)
{
	if (rules->keys.w_pressed)
		rules->player.y -= 1;
	if (rules->keys.a_pressed)
		rules->player.x -= 1;
	if (rules->keys.s_pressed)
		rules->player.y += 1;
	if (rules->keys.d_pressed)
		rules->player.x += 1;
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
