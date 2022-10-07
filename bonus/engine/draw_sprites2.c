/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 17:25:32 by ddelladi          #+#    #+#             */
/*   Updated: 2022/10/07 17:44:37 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	draw_sprites_2(t_rules *rules, int num[2], double var[5])
{
	var[0] = rules->sort_spr[num[0]]->x - rules->player.x;
	if (!var[0])
		var[0] = 1;
	var[1] = rules->sort_spr[num[0]]->y - rules->player.y;
	var[2] = 1.0 / (rules->player.plane_x * rules->player.d_y
			- rules->player.d_x * rules->player.plane_y);
	var[3] = var[2] * (rules->player.d_y * var[0]
			- rules->player.d_x * var[1])
		* (854 * 2.6 / (float)rules->mlx.win_width);
	var[4] = var[2] * (-rules->player.plane_y
			* var[0] + rules->player.plane_x * var[1]);
	num[1] = (int)((rules->mlx.win_width / 2) * (1 + var[3] / var[4]));
}

void	draw_sprites(t_rules *rules, t_image *view)
{
	t_draw_coord	*info;
	double			var[5];
	int				num[2];

	num[0] = 0;
	while (num[0] < rules->n_sprites)
	{
		if (rules->sort_spr[num[0]]->state && rules->sort_spr[num[0]]->dist
			> rules->map.block_width / 2)
		{
			draw_sprites_2(rules, num, var);
			info = define_sprite_info(rules, var[4], num[1], num[0]);
			while (info->start_x < info->end_x)
			{
				info->t_x = (int)((info->start_x - info->bench_x)
						* info->sprite->width / info->width);
				draw_sprite_col(rules, info, view, var[4]);
				info->start_x++;
			}
			free(info);
		}
		num[0]++;
	}
}
