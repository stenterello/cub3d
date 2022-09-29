/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 20:41:24 by ddelladi          #+#    #+#             */
/*   Updated: 2022/09/29 23:07:01 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	draw_sprites(t_rules *rules, t_image *view)
{
	double	x;
	double	y;
	int		i;
	double	inv_det;
	double	trans_x;
	double	trans_y;
	int		s_x;
	int		height;
	int		start_y;
	int		end_y;
	int		width;
	int		start_x;
	int		end_x;

	i = 0;
	while (i < rules->n_sprites)
	{
		x = rules->sort_spr[i].x - rules->player.x;
		y = rules->sort_spr[i].y - rules->player.y;
		inv_det = 1.0 / (rules->player.plane_x * rules->player.d_y - rules->player.d_x * rules->player.plane_y);
		trans_x = inv_det * (rules->player.d_y * x - rules->player.d_x * y) * 2.6;
		trans_y = inv_det * (-rules->player.plane_y * x + rules->player.plane_x * y);
		s_x = (int)((rules->mlx.win_width / 2) * (1 + trans_x / trans_y));
		height = (int)(rules->mlx.win_height / trans_y);
		start_y = rules->mlx.win_height / 2 - height / 2;
		if (start_y < 0)
			start_y = 0;
		end_y = rules->mlx.win_height / 2 + height / 2;
		if (end_y > rules->mlx.win_height)
			end_y = rules->mlx.win_height;
		width = get_abs((int)(rules->mlx.win_height / trans_y));
		start_x = -width / 2 + s_x;
		if (start_x < 0)
			start_x = 0;
		end_x = width / 2 + s_x;
		if (end_x > rules->mlx.win_width)
			end_x = rules->mlx.win_width;
		while (start_x < end_x)
		{
			if (trans_y > 0 && start_x > 0 && start_x < rules->mlx.win_width && trans_y < rules->dist_array[start_x])
			{
				while (start_y < end_y)
				{
					easy_pxl(view, start_x, start_y, 0x00FFFF00);
					start_y++;
				}
			}
			start_x++;
		}
		i++;
	}
}
