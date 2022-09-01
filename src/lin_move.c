/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lin_move.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 18:46:17 by ddelladi          #+#    #+#             */
/*   Updated: 2022/09/01 22:04:15 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	press(int keycode, t_rules *rules)
{
	if (keycode == 65307)
	{
		mlx_destroy_window(rules->mlx.mlx, rules->mlx.mlx_win);
		exit(0);
	}
	printf("keycode: %d\n", keycode);
	if (keycode == 119)
		rules->keys.w_pressed = 1;
	if (keycode == 97)
		rules->keys.a_pressed = 1;
	if (keycode == 115)
		rules->keys.s_pressed = 1;
	if (keycode == 100)
		rules->keys.d_pressed = 1;
	if (keycode == 65361)
		rules->keys.l_pressed = 1;
	if (keycode == 65363)
		rules->keys.r_pressed = 1;
	return (0);
}

int	release(int keycode, t_rules *rules)
{
	if (keycode == 119)
		rules->keys.w_pressed = 0;
	if (keycode == 97)
		rules->keys.a_pressed = 0;
	if (keycode == 115)
		rules->keys.s_pressed = 0;
	if (keycode == 100)
		rules->keys.d_pressed = 0;
	if (keycode == 65361)
		rules->keys.l_pressed = 0;
	if (keycode == 65363)
		rules->keys.r_pressed = 0;
	return (0);
}
