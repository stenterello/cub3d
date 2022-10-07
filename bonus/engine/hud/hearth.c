/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hearth.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 18:37:46 by ddelladi          #+#    #+#             */
/*   Updated: 2022/10/07 13:17:49 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	draw_container(t_rules *rules, t_image *view)
{
	int	x;
	int	y;
	int	w;
	int	h;
	int	bench[2];

	w = rules->mlx.win_width / 3;
	x = rules->mlx.win_width - w - 40;
	h = 30;
	bench[0] = x;
	y = 15;
	bench[1] = y;
	while (x < bench[0] + w)
	{
		y = bench[1];
		while (y < h)
		{
			if (y > bench[1] + 1 && y < h - 2 && x > bench[0]
				+ 1 && x < bench[0] + w - 2)
				easy_pxl(view, x, y++, 0x00FFFFFF);
			else
				easy_pxl(view, x, y++, 0x00B5B1A7);
		}
		x++;
	}
}

static void	draw_health_level(t_rules *rules, t_image *view)
{
	float	tot;
	float	w;
	float	h;
	int		xy[2];
	int		bench[2];

	tot = rules->mlx.win_width / 3;
	w = tot / 100 * rules->player.health;
	h = 28;
	xy[0] = rules->mlx.win_width - w - 38;
	bench[1] = xy[0];
	xy[1] = 17;
	bench[0] = xy[1];
	while (xy[0] < bench[1] + w - 4)
	{
		xy[1] = bench[0];
		while (xy[1] < h)
		{
			if (xy[1] < h - bench[0] / 2 + 2)
				easy_pxl(view, xy[0], xy[1]++, 0x00ED1F1F);
			else
				easy_pxl(view, xy[0], xy[1]++, 0x00C40000);
		}
		xy[0]++;
	}
}

void	draw_hearth_sup(t_rules *rules, t_image *view, t_draw_coord *info)
{
	while (info->start_x < info->end_x)
	{
		info->start_y = info->bench_y;
		info->t_x = (info->start_x - info->bench_x)
			* rules->player.life_tex.width / info->width;
		while (info->start_y < info->end_y)
		{
			info->t_y = (info->start_y - info->bench_y)
				* rules->player.life_tex.height / info->height;
			info->color = get_sprite_color(&rules->player.life_tex,
					info->t_x, info->t_y, rules);
			if (info->color)
				easy_pxl(view, info->start_x, info->start_y, info->color);
			info->start_y++;
		}
		info->start_x++;
	}
}

static void	draw_hearth(t_rules *rules, t_image *view)
{
	t_draw_coord	info;

	info.start_x = rules->mlx.win_width - 35;
	info.width = rules->mlx.win_width - info.start_x - 5;
	info.end_x = info.start_x + info.width;
	info.bench_x = info.start_x;
	info.start_y = 12;
	info.end_y = 35;
	info.bench_y = info.start_y;
	info.height = info.end_y - info.start_y;
	draw_hearth_sup(rules, view, &info);
}

void	health_level(t_rules *rules, t_image *view)
{
	draw_container(rules, view);
	draw_health_level(rules, view);
	draw_hearth(rules, view);
}
