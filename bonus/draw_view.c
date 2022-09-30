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

#include "../include/cub3d_bonus.h"

double	get_dist(t_rules *rules, t_bres_data *d)
{
	float	angle_diff;
	double	dist;

	dist = final_length(d->xy[0], d->xy[1], d->xy2);
	if (!dist)
		dist = 0.01;
	angle_diff = rules->player.dir - d->ray_angle;
	if (angle_diff < 0)
		angle_diff += (float)(2 * M_PI);
	else if (angle_diff > (float)(2 * M_PI))
		angle_diff -= 2 * M_PI;
	dist *= cos(angle_diff);
	return (dist);
}

double	get_fix(double angle)
{
	if (angle > M_PI * 2)
		angle -= M_PI * 2;
	if (angle < 0)
		angle += M_PI * 2;
	return (angle);
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
	{
		if (is_door((int)(d->xy2[0] / rules->map.block_width), (int)(d->xy2[1] / rules->map.block_width), rules))
			return (rules->door);
		return (rules->east);
	}
	else if (!our_modulo(d->xy2[0], rules->map.block_width)
		&& d->ray_angle >= M_PI / 2 && d->ray_angle <= 3 * M_PI / 2)
	{
		if (is_door((int)(d->xy2[0] / rules->map.block_width) - 1, (int)(d->xy2[1] / rules->map.block_width), rules))
			return (rules->door);
		return (rules->west);
	}
	else if (!our_modulo(d->xy2[1], rules->map.block_width)
		&& d->ray_angle <= M_PI && d->ray_angle >= 0)
	{
		if (is_door((int)(d->xy2[0] / rules->map.block_width), (int)(d->xy2[1] / rules->map.block_width) - 1, rules))
			return (rules->door);
		return (rules->south);
	}
	else if (!our_modulo(d->xy2[1], rules->map.block_width)
		&& d->ray_angle > M_PI && d->ray_angle <= 2 * M_PI)
	{
		if (is_door((int)(d->xy2[0] / rules->map.block_width), (int)(d->xy2[1] / rules->map.block_width), rules))
			return (rules->door);
		return (rules->north);
	}
	else
		die("Error while choosing textures. Developers fault. Aborting");
	return (NULL);
}

void	draw_walls(double var[3], t_rules *rules, t_draw_info *info)
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
}

void	draw_ceiling(double var[3], t_rules *rules, t_draw_info *info)
{
	int		y;
	float	dy;
	float	tx;
	float	ty;
	unsigned int	color;
	float	dist;

	y = -1;
	while (++y < var[0])
	{
		dy = y - (rules->mlx.win_height / 2);
		dist = rules->mlx.win_height / 2 / dy;
		tx = rules->player.x / rules->map.block_width - cos(info->d.ray_angle) * dist / cos(get_fix(rules->player.dir - info->d.ray_angle));
		ty = rules->player.y / rules->map.block_width + sin(info->d.ray_angle) * dist / cos(get_fix(rules->player.dir - info->d.ray_angle));
		color = get_color(rules->ceiling,	
				our_modulo(tx * rules->ceiling->width, rules->ceiling->width),
				our_modulo(ty * rules->ceiling->width, rules->ceiling->width),
				rules);
		easy_pxl(info->view, info->d.x, y, color);
	}
}

void	draw_floor(double var[3], t_rules *rules, t_draw_info *info)
{
	int		y;
	float	dy;
	float	tx;
	float	ty;
	unsigned int	color;
	float	dist;

	y = var[1] - 1;
	while (++y < rules->mlx.win_height)
	{
		dy = y - (rules->mlx.win_height / 2) + 1;
		dist = rules->mlx.win_height / 2 / dy;
		tx = rules->player.x / rules->map.block_width + cos(info->d.ray_angle) * dist / cos(get_fix(rules->player.dir - info->d.ray_angle));
		ty = rules->player.y / rules->map.block_width - sin(info->d.ray_angle) * dist / cos(get_fix(rules->player.dir - info->d.ray_angle));
		color = get_color(rules->floor,	
				our_modulo(tx * rules->floor->width, rules->floor->width),
				our_modulo(ty * rules->floor->width, rules->floor->width),
				rules);
		easy_pxl(info->view, info->d.x, y, color);
	}
}

void	draw_view(t_bres_data *d, t_image *view, t_rules *rules, t_image *tex)
{
	double			var[3];
	t_draw_info		info;

	rules->dist_array[d->x] = get_dist(rules, d);
	info.l_h = rules->map.block_width * rules->mlx.win_height / rules->dist_array[d->x];
	var[0] = rules->mlx.win_height / 2 - info.l_h / 2;
	var[1] = info.l_h + var[0];
	var[2] = 2;
	info.off = var[0];
	info.view = view;
	info.tex = tex;
	info.d = *d;
	adjust_var(var, rules);
	draw_ceiling(var, rules, &info);
	draw_walls(var, rules, &info);
	draw_floor(var, rules, &info);
}
