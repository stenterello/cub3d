/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 17:56:50 by ddelladi          #+#    #+#             */
/*   Updated: 2022/09/09 12:18:27 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	decrement_angle(double angle, int t)
{
	int	i;

	i = 0;
	while (i++ < t)
	{
		angle -= ANGLE_UNIT;
		if (angle < 0)
			angle = 2 * M_PI;
	}
	return (angle);
}

void	calc_ray(t_bres_data *data, t_rules *rules,
	t_image *view)
{
	float		f_pts[3];
	float		s_pts[3];

	horizontal_lines_check(data->dir1, rules, f_pts);
	vertical_lines_check(data->dir1, rules, s_pts);
	data->xy[0] = rules->player.x;
	data->xy[1] = rules->player.y;
	if (final_length(rules->player.x, rules->player.y, s_pts) == INT_MAX
		|| final_length(rules->player.x, rules->player.y, f_pts)
		< final_length(rules->player.x, rules->player.y, s_pts))
	{
		data->xy2[0] = f_pts[0];
		data->xy2[1] = f_pts[1];
		bresenham(*data, view, rules);
	}
	else
	{
		data->xy2[0] = s_pts[0];
		data->xy2[1] = s_pts[1];
		bresenham(*data, view, rules);
	}
	data->x += (rules->mlx.win_width / (rules->mlx.win_width / 3.66) + 1);
	data->dir1 = decrement_angle(data->dir1, 2);
}

void	raycast(t_rules *rules, t_image *view)
{
	int			i;
	t_bres_data	data;

	data.dir1 = increment_angle(rules->player.dir,
			rules->mlx.win_width / 3.79259259);
	i = 0;
	data.x = 0;
	data.color = 0x00FFFFFF;
	while (i++ < rules->mlx.win_width / 3.66)
		calc_ray(&data, rules, view);
}
