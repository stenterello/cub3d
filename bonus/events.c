/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 16:45:37 by ddelladi          #+#    #+#             */
/*   Updated: 2022/09/29 11:52:32 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

int	mouse_exit(t_rules *rules)
{
	mlx_destroy_window(rules->mlx.mlx, rules->mlx.mlx_win);
	exit(0);
	return (0);
}

int	mouse_move(int x, int y, t_rules *rules)
{
	if (x < 0 || y < 0 || x > rules->mlx.win_width || y > rules->mlx.win_height)
		return (0);
	if (!rules->mouse.moved)
	{
		rules->mouse.moved = 1;
		rules->mouse.last_x = x;
		rules->mouse.last_y = y;
	}
	else
	{
		if (x < rules->mouse.last_x)
			rules->player.dir += ANGLE_UNIT * 45;
		else if (x > rules->mouse.last_x)
			rules->player.dir -= ANGLE_UNIT * 45;
		else
			return (0);
		rules->mouse.last_x = x;
		rules->mouse.last_y = y;
	}
	rules->player.d_x = cos(rules->player.dir);
	if (rules->player.dir == (double)M_PI)
		rules->player.d_y = 0;
	else
		rules->player.d_y = -sin(rules->player.dir);
	return (0);
}

void	add_events(t_rules *rules)
{
	mlx_hook(rules->mlx.mlx_win, 2, 1L << 0, press, rules);
	mlx_hook(rules->mlx.mlx_win, 3, 1L << 1, release, rules);
	mlx_hook(rules->mlx.mlx_win, 17, 0, mouse_exit, rules);
	mlx_hook(rules->mlx.mlx_win, 6, 1L << 6, mouse_move, rules);
}

void	restore_gun(t_rules *rules)
{
	if (!ft_strncmp(rules->player.gun.path, "./img/sparo.xpm", 16)
		&& rules->n_frames - rules->player.gun.last_shoot > 350)
	{
		ft_strlcpy(rules->player.gun.path, "./img/pistola.xpm", 18);
		mlx_destroy_image(rules->mlx.mlx, rules->player.gun.gun_img.img);
		load_gun(rules);
	}
}
