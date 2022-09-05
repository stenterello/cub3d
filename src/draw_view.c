/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_view.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gimartin <gimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 22:28:36 by ddelladi          #+#    #+#             */
/*   Updated: 2022/09/05 13:58:39 by gimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	phi(t_rules *rules, t_bres_data d)
{
	float	angle_diff;
	double	dist;

	dist = final_length(d.xy[0], d.xy[1], d.xy2);
	if (!dist)
		dist = 1;
	angle_diff = rules->player.dir - d.dir1;
	if (angle_diff < 0)
		angle_diff += (float)(2 * M_PI);
	else if (angle_diff > (float)(2 * M_PI))
		angle_diff -= 2 * M_PI;
	dist *= cos(angle_diff);
	return (dist);
}

void	adjust_var(int var[3], t_rules *rules)
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
	if (!(x < 0 || x > rules->mlx.win_width
			|| y < 0 || y > rules->mlx.win_height))
	{
		return ((unsigned int)(tex->addr + (4 * (tex->width * y + x))));
	}
	return (0);
}

t_image	*choose_texture(t_rules *rules)
{
	if (!((int)rules->player.x % (int)rules->map.block_width)
		&& (rules->player.dir < M_PI / 2 || rules->player.dir > 3 * M_PI / 2))
		return (rules->east);
	else if (!((int)rules->player.x % (int)rules->map.block_width)
		&& rules->player.dir > M_PI / 2 && rules->player.dir < 3 * M_PI / 2)
		return (rules->west);
	else if (!((int)rules->player.y % (int)rules->map.block_width)
		&& rules->player.dir < M_PI && rules->player.dir > 0)
		return (rules->north);
	else if (!((int)rules->player.y % (int)rules->map.block_width)
		&& rules->player.dir > M_PI && rules->player.dir <= 3 * M_PI / 2)
		return (rules->south);
	return (NULL);
}

void	copy_draw_view(t_bres_data d, int var[3], t_rules *rules, t_image *view)
{
	int				off;
	double			l_h;
	double			dist;

	dist = phi(rules, d);
	l_h = rules->map.block_width * rules->mlx.win_height / dist;
	off = var[0];
	while (d.x < var[2])
	{
		var[0] = rules->mlx.win_height / 2 - l_h / 2;
		if (var[0] < 0)
			var[0] = 0;
		else if (var[0] > rules->mlx.win_height)
			var[0] = rules->mlx.win_height;
		while (var[0] < var[1])
		{
			easy_pxl(view, d.x, var[0], get_color(choose_texture(rules), d.x, var[0], rules));
			var[0]++;
		}
		d.x++;
	}
}

void	draw_view(t_bres_data d, t_image *view, t_rules *rules)
{
	double			line_height;
	int				var[3];
	double			dist;

	dist = phi(rules, d);
	line_height = rules->map.block_width * rules->mlx.win_height / dist;
	var[0] = rules->mlx.win_height / 2 - line_height / 2;
	var[1] = line_height + var[0];
	var[2] = d.x + (rules->mlx.win_width / 725 + 1);
	adjust_var(var, rules);
	copy_draw_view(d, var, rules, view);
}
