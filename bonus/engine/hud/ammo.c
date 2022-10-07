/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ammo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gimartin <gimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 18:39:28 by ddelladi          #+#    #+#             */
/*   Updated: 2022/10/07 10:48:32 by gimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	draw_ammo_amount(t_rules *rules)
{
	char	*s;

	s = ft_itoa(rules->player.ammo);
	mlx_string_put(rules->mlx.mlx, rules->mlx.mlx_win,
		rules->mlx.win_width - 55, 60, 0x00FFFFFF, s);
	free(s);
}

void	ammo_leve_sup(t_rules *rules, t_image *view, t_draw_coord *info)
{
	while (info->start_x < info->end_x)
	{
		info->start_y = info->bench_y;
		info->t_x = (info->start_x - info->bench_x)
			* rules->player.ammo_tex.width / info->width;
		while (info->start_y < info->end_y)
		{
			info->t_y = (info->start_y - info->bench_y)
				* rules->player.ammo_tex.height / info->height;
			info->color = get_sprite_color(&rules->player.ammo_tex,
					info->t_x, info->t_y, rules);
			if (info->color)
				easy_pxl(view, info->start_x, info->start_y, info->color);
			info->start_y++;
		}
		info->start_x++;
	}
}

void	ammo_level(t_rules *rules, t_image *view)
{
	t_draw_coord	info;

	info.start_x = rules->mlx.win_width - 35;
	info.width = rules->mlx.win_width - info.start_x - 5;
	info.end_x = info.start_x + info.width;
	info.bench_x = info.start_x;
	info.start_y = 40;
	info.end_y = 70;
	info.bench_y = info.start_y;
	info.height = info.end_y - info.start_y;
	ammo_leve_sup(rules, view, &info);
}
