/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 18:46:17 by ddelladi          #+#    #+#             */
/*   Updated: 2022/10/01 19:10:05 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	press(int keycode, t_rules *rules)
{
	if (keycode == 53)
	{
		mlx_destroy_window(rules->mlx.mlx, rules->mlx.mlx_win);
		exit(0);
	}
	if (keycode == 13)
		rules->keys.w_pressed = 1;
	if (keycode == 0)
		rules->keys.a_pressed = 1;
	if (keycode == 1)
		rules->keys.s_pressed = 1;
	if (keycode == 2)
		rules->keys.d_pressed = 1;
	if (keycode == 123)
		rules->keys.l_pressed = 1;
	if (keycode == 124)
		rules->keys.r_pressed = 1;
	if (keycode == 257 || keycode == 258)
		rules->keys.shift_pressed = 1;
	if (keycode == 14)
		rules->keys.e_pressed = 1;
	if (keycode == 49 && rules->player.ammo)
		shoot(rules);
	printf("%d\n", keycode);
	return (0);
}

int	release(int keycode, t_rules *rules)
{
	if (keycode == 13)
		rules->keys.w_pressed = 0;
	if (keycode == 0)
		rules->keys.a_pressed = 0;
	if (keycode == 1)
		rules->keys.s_pressed = 0;
	if (keycode == 2)
		rules->keys.d_pressed = 0;
	if (keycode == 123)
		rules->keys.l_pressed = 0;
	if (keycode == 124)
		rules->keys.r_pressed = 0;
	if (keycode == 257 || keycode == 258)
		rules->keys.shift_pressed = 0;
	if (keycode == 14)
		rules->keys.e_pressed = 0;
	return (0);
}