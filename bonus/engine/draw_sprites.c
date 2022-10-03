/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 20:41:24 by ddelladi          #+#    #+#             */
/*   Updated: 2022/10/03 23:48:52 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	draw_gun(t_rules *rules, t_image *view)
{
	t_draw_coord	info;

	info.width = rules->mlx.win_width / 5;
	info.start_x = rules->mlx.win_width / 2 - info.width / 2;
	info.end_x = info.start_x + info.width;
	info.height = info.width * rules->player.gun.gun_img.height / rules->player.gun.gun_img.width;
	info.start_y = rules->mlx.win_height - info.height + rules->player.gun.off;
	info.end_y = info.start_y + info.height;
	info.bench_x = info.start_x;
	info.bench_y = info.start_y;
	while (info.start_x < info.end_x)
	{
		info.start_y = info.bench_y;
		info.t_x = (int)((info.start_x - info.bench_x) * rules->player.gun.gun_img.width / info.width);
		while (info.start_y < info.end_y)
		{
			info.t_y = (int)((info.start_y - info.bench_y) * rules->player.gun.gun_img.height / info.height);
			info.color = get_sprite_color(&rules->player.gun.gun_img, info.t_x, info.t_y, rules);
			if (info.color && info.start_x > 0 && info.start_x < rules->mlx.win_width && info.start_y > 0 && info.start_y < rules->mlx.win_height)
				easy_pxl(view, info.start_x, info.start_y, info.color);
			info.start_y++;
		}
		info.start_x++;
	}
}

static void	draw_sprite_col(t_rules *rules, t_draw_coord *info, t_image *view, double trans_y)
{
	if (trans_y > 0 && info->start_x > 0 && info->start_x < rules->mlx.win_width && trans_y < rules->dist_array[(int)info->start_x])
	{
		info->start_y = info->bench_y;
		while (info->start_y < info->end_y)
		{
			info->t_y = (int)((info->start_y - info->bench_y) * info->sprite->height / info->height);
			info->color = get_sprite_color(info->sprite, info->t_x, info->t_y, rules);
			if (info->color)
				easy_pxl(view, info->start_x, info->start_y, info->color);
			info->start_y++;
		}
	}
}

static void	define_sprite_info(t_rules *rules, t_draw_coord *info, double trans_y, int s_x)
{
	info->height = (rules->mlx.win_height / trans_y) * 25;
	info->start_y = rules->mlx.win_height / 2 - info->height / 2;
	info->bench_y = info->start_y;
	if (info->start_y < 0)
		info->start_y = 0;
	info->end_y = rules->mlx.win_height / 2 + info->height / 2;
	if (info->end_y > rules->mlx.win_height)
		info->end_y = rules->mlx.win_height;
	info->width = get_abs_double((rules->mlx.win_height / trans_y)) * 15;
	info->start_x = -info->width / 2 + s_x;
	info->bench_x = info->start_x;
	if (info->start_x < 0)
		info->start_x = 0;
	info->end_x = info->width / 2 + s_x;
	if (info->end_x > rules->mlx.win_width)
		info->end_x = rules->mlx.win_width;
}

void	draw_sprites(t_rules *rules, t_image *view)
{
	t_draw_coord	info;
	double	x;
	double	y;
	int		i;
	double	inv_det;
	double	trans_x;
	double	trans_y;
	int		s_x;

	i = 0;
	while (i < rules->n_sprites)
	{
		if (rules->sort_spr[i].state)
		{
			x = rules->sort_spr[i].x - rules->player.x;
			y = rules->sort_spr[i].y - rules->player.y;
			inv_det = 1.0 / (rules->player.plane_x * rules->player.d_y - rules->player.d_x * rules->player.plane_y);
			trans_x = inv_det * (rules->player.d_y * x - rules->player.d_x * y) * 2.6;
			trans_y = inv_det * (-rules->player.plane_y * x + rules->player.plane_x * y);
			s_x = (int)((rules->mlx.win_width / 2) * (1 + trans_x / trans_y));
			define_sprite_info(rules, &info, trans_y, s_x);
			info.sprite = rules->animations[rules->sort_spr[i].type];
			while (info.start_x < info.end_x)
			{
				info.t_x = (int)((info.start_x - info.bench_x) * info.sprite->width / info.width);
				draw_sprite_col(rules, &info, view, trans_y);
				info.start_x++;
			}
		}
		i++;
	}
}
