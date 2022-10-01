/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hearth.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 18:37:46 by ddelladi          #+#    #+#             */
/*   Updated: 2022/10/01 18:39:09 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	draw_container(t_rules *rules, t_image *view)
{
	int	x;
	int	y;
	int	w;
	int	h;
	int	bench_x;
	int	bench_y;

	w = rules->mlx.win_width / 3;
	x = rules->mlx.win_width - w - 40;
	h = 30;
	bench_x = x;
	y = 15;
	bench_y = y;
	while (x < bench_x + w)
	{
		y = bench_y;
		while (y < h)
		{
			if (y > bench_y + 1 && y < h - 2 && x > bench_x + 1 && x < bench_x + w - 2)
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
	int		x;
	int		y;
	int		bench_y;
	int		bench_x;

	tot = rules->mlx.win_width / 3;
	w = tot / 100 * rules->player.health;
	h = 28;
	x = rules->mlx.win_width - w - 38;
	bench_x = x;
	y = 17;
	bench_y = y;
	while (x < bench_x + w - 4)
	{
		y = bench_y;
		while (y < h)
		{
			if (y < h - bench_y / 2 + 2)
				easy_pxl(view, x, y++, 0x00ED1F1F);
			else
				easy_pxl(view, x, y++, 0x00C40000);
		}
		x++;
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
	while (info.start_x < info.end_x)
	{
		info.start_y = info.bench_y;
		info.t_x = (info.start_x - info.bench_x) * rules->player.heart_tex.width / info.width;
		while (info.start_y < info.end_y)
		{
			info.t_y = (info.start_y - info.bench_y) * rules->player.heart_tex.height / info.height;
			info.color = get_sprite_color(&rules->player.heart_tex, info.t_x, info.t_y, rules);
			if (info.color)
				easy_pxl(view, info.start_x, info.start_y, info.color);
			info.start_y++;
		}
		info.start_x++;
	}
}

void	health_level(t_rules *rules, t_image *view)
{
	draw_container(rules, view);
	draw_health_level(rules, view);
	draw_hearth(rules, view);
}
