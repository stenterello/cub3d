/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 18:37:44 by ddelladi          #+#    #+#             */
/*   Updated: 2022/10/07 13:43:12 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	viewfinder_supp(t_rules *rules, t_image *view, t_draw_coord *info)
{
	while (info->start_x < info->end_x)
	{
		info->t_x = (info->start_x - info->bench_x)
			* rules->player.viewfinder.width / info->width;
		info->start_y = info->bench_y;
		while (info->start_y < info->end_y)
		{
			info->t_y = (info->start_y - info->bench_y)
				* rules->player.viewfinder.height / info->height;
			info->color = get_sprite_color(&rules->player.viewfinder,
					info->t_x, info->t_y, rules);
			if (info->color)
				easy_pxl(view, info->start_x, info->start_y, info->color);
			info->start_y++;
		}
		info->start_x++;
	}
}

static void	viewfinder(t_rules *rules, t_image *view)
{
	t_draw_coord	info;

	info.width = 26;
	info.height = 26;
	info.start_x = rules->mlx.win_width / 2 - info.width / 2;
	info.bench_x = info.start_x;
	info.end_x = rules->mlx.win_width / 2 + info.width / 2;
	info.start_y = rules->mlx.win_height / 2 - info.height / 2;
	info.bench_y = info.start_y;
	info.end_y = rules->mlx.win_height / 2 + info.height / 2;
	viewfinder_supp(rules, view, &info);
}

void	hud(t_rules *rules, t_image *view)
{
	if (rules->player.ammo > 20)
		rules->player.ammo = 20;
	health_level(rules, view);
	draw_ammo_amount(rules, view);
	viewfinder(rules, view);
}
