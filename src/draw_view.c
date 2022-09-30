/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_view.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 22:28:36 by ddelladi          #+#    #+#             */
/*   Updated: 2022/09/30 16:13:04 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	get_dist(t_rules *rules, t_bres_data d)
{
	float	angle_diff;
	double	dist;

	dist = final_length(d.xy[0], d.xy[1], d.xy2);
	if (!dist)
		dist = 0.01;
	angle_diff = rules->player.dir - d.ray_angle;
	if (angle_diff < 0)
		angle_diff += (float)(2 * M_PI);
	else if (angle_diff > (float)(2 * M_PI))
		angle_diff -= 2 * M_PI;
	dist *= cos(angle_diff);
	return (dist);
}

void	adjust_var(double var[3], t_rules *rules)
{
	if (var[0] < 0)
		var[0] = 0;
	if (var[1] > rules->mlx.win_height)
		var[1] = rules->mlx.win_height;
	if (var[2] > rules->mlx.win_width)
		var[2] = rules->mlx.win_width;
}

t_image	*choose_texture(t_rules *rules, t_bres_data *d)
{
	if (!our_modulo(d->xy2[0], rules->map.block_width)
		&& (d->ray_angle < M_PI / 2 || d->ray_angle > 3 * M_PI / 2))
		return (rules->east);
	else if (!our_modulo(d->xy2[0], rules->map.block_width)
		&& d->ray_angle >= M_PI / 2 && d->ray_angle <= 3 * M_PI / 2)
		return (rules->west);
	else if (!our_modulo(d->xy2[1], rules->map.block_width)
		&& d->ray_angle <= M_PI && d->ray_angle >= 0)
		return (rules->south);
	else if (!our_modulo(d->xy2[1], rules->map.block_width)
		&& d->ray_angle > M_PI && d->ray_angle <= 2 * M_PI)
		return (rules->north);
	else
		die("Error while choosing textures. Developers fault. Aborting");
	return (NULL);
}

void	draw_walls(double var[3], t_rules *rules, t_draw_info *info)
{
	while (info->d.x < var[2])
	{
		var[0] = rules->mlx.win_height / 2 - info->l_h / 2;
		if (var[0] < 0)
			var[0] = 0;
		while (var[0] < var[1])
		{
			if (!our_modulo(info->d.xy2[0], rules->map.block_width))
				easy_pxl(info->view, info->d.x, var[0], get_color(info->tex,
						choose_x(info, info->d.xy2[1], rules), choose_y(var[0],
							info), rules));
			else
				easy_pxl(info->view, info->d.x, var[0], get_color(info->tex,
						choose_x(info, info->d.xy2[0], rules), choose_y(var[0],
							info), rules));
			var[0]++;
		}
		info->d.x++;
	}
}

void	draw_view(t_bres_data d, t_image *view, t_rules *rules, t_image *tex)
{
	double			var[3];
	t_draw_info		info;
	double			dist;

	dist = get_dist(rules, d);
	info.l_h = rules->map.block_width * rules->mlx.win_height / dist;
	var[0] = rules->mlx.win_height / 2 - info.l_h / 2;
	var[1] = info.l_h + var[0];
	var[2] = d.x + (rules->mlx.win_width
			/ (rules->mlx.win_width / 2.8) + 1);
	info.off = var[0];
	info.view = view;
	info.tex = tex;
	info.d = d;
	adjust_var(var, rules);
	draw_walls(var, rules, &info);
}
