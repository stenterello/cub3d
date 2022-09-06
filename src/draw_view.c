/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_view.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 22:28:36 by ddelladi          #+#    #+#             */
/*   Updated: 2022/09/06 17:17:58 by ddelladi         ###   ########.fr       */
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
	angle_diff = rules->player.dir - d.dir1;
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

unsigned int	get_color(t_image *tex, int x, int y, t_rules *rules)
{
	if (!(x < 0 || x > rules->mlx.win_width - 1
			|| y < 0 || y > rules->mlx.win_height - 1))
	{
		return (*(unsigned int *)(tex->addr + (4 * (tex->width * y + x))));
	}
	return (0x0);
}

t_image	*choose_texture(t_rules *rules, float xy[2])
{
	if (!our_modulo(xy[0], rules->map.block_width)
		&& (rules->player.dir < M_PI / 2 || rules->player.dir > 3 * M_PI / 2))
		return (rules->east);
	else if (!our_modulo(xy[0], rules->map.block_width)
		&& rules->player.dir >= M_PI / 2 && rules->player.dir <= 3 * M_PI / 2)
		return (rules->west);
	else if (!our_modulo(xy[1], rules->map.block_width)
		&& rules->player.dir < M_PI && rules->player.dir >= 0)
		return (rules->north);
	else if (!our_modulo(xy[1], rules->map.block_width)
		&& rules->player.dir >= M_PI && rules->player.dir <= 2 * M_PI)
		return (rules->south);
	return (NULL);
}

void	draw_walls(t_bres_data d, double var[3], t_rules *rules, t_image *view, double l_h, t_image *tex, double off)
{
	while (d.x < var[2])
	{
		var[0] = rules->mlx.win_height / 2 - l_h / 2;
		if (var[0] < 0)
			var[0] = 0;
		while (var[0] < var[1])
		{
			if (!our_modulo(d.xy2[0], rules->map.block_width))
				easy_pxl(view, d.x, var[0], get_color(tex, our_modulo(d.xy2[1], rules->map.block_width) * tex->width / rules->map.block_width, (var[0] - off) * tex->width / l_h, rules));
			else
				easy_pxl(view, d.x, var[0], get_color(tex, our_modulo(d.xy2[0], rules->map.block_width) * tex->width / rules->map.block_width, (var[0] - off) * tex->width / l_h, rules)); //d.xy2 : rules->map.block_width = x : tex->width
			var[0]++;
		}
		d.x++;
	}
	rules->x_counter++;
}

void	draw_view(t_bres_data d, t_image *view, t_rules *rules, t_image *tex)
{
	double			line_height;
	double			var[3];
	double			dist;
	double			off;

	dist = get_dist(rules, d);
	line_height = rules->map.block_width * rules->mlx.win_height / dist;
	var[0] = rules->mlx.win_height / 2 - line_height / 2;
	var[1] = line_height + var[0];
	var[2] = d.x + (rules->mlx.win_width / 725 + 1);
	off = var[0];
	adjust_var(var, rules);
	draw_walls(d, var, rules, view, line_height, tex, off);
}
