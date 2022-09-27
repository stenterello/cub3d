/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_enemies_utils2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 12:03:55 by ddelladi          #+#    #+#             */
/*   Updated: 2022/09/27 23:58:15 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	get_enemy_mini_coord(t_rules *rules, t_bres_data *data, int mini_coord[2])
{
	mini_coord[0] = data->xy2[0] / rules->map.block_width - 1;
	mini_coord[1] = data->xy2[1] / rules->map.block_width;
	if (!our_modulo(data->xy2[0], rules->map.block_width)
		&& (data->dir1 < M_PI / 2 || data->dir1 > 3 * M_PI / 2))
		mini_coord[0]++;
	else if (!our_modulo(data->xy2[1], rules->map.block_width)
		&& data->dir1 < M_PI / 2)
	{
		mini_coord[0]++;
		mini_coord[1]--;
	}
	else if (!our_modulo(data->xy2[1], rules->map.block_width)
		&& data->dir1 > 3 * M_PI / 2)
		mini_coord[0]++;
	else if (!our_modulo(data->xy2[1], rules->map.block_width)
		&& data->dir1 > M_PI && data->dir1 < 3 * M_PI / 2)
		mini_coord[0]++;
	else if (!our_modulo(data->xy2[1], rules->map.block_width)
		&& data->dir1 > M_PI / 2 && data->dir1 < M_PI)
	{
		mini_coord[0]++;
		mini_coord[1]--;
	}
	// printf("data->xy2[0], %f\n", data->xy2[0]);
	// printf("data->xy2[1], %f\n", data->xy2[1]);
	// printf("coord x %d, coord y %d\n", mini_coord[0], mini_coord[1]);

	// controllare gli angoli precisi 90°, 180°, 270°, 360°!!!
}

double	final_length_double(double start_x, double start_y, double rxy[2])
{
	if (rxy[0] == INT_MAX)
		return (INT_MAX);
	return (sqrt(pow(get_abs(start_x - rxy[0]), 2) + pow(start_y - rxy[1], 2)));
}

double	get_enemy_dist(t_rules *rules, int coord[2])
{
	double	en_xy[2];

	en_xy[0] = coord[0] * rules->map.block_width + rules->map.block_width / 2;
	en_xy[1] = coord[1] * rules->map.block_width + rules->map.block_width / 2;
	return (final_length_double(rules->player.x, rules->player.y, en_xy));
}

double	get_end_angle(t_rules *rules, double start_angle, int *range, int *counter2, double real_start)
{
	float	end_pts[2];
	int		counter;
	double	bench;

	counter = 0;
	ft_bzero(&end_pts, 8);
	bench = start_angle;
	enemy_in_view(start_angle, rules, end_pts);
	while (enemy_in_view(start_angle, rules, end_pts))
	{
		start_angle = decrement_angle(start_angle, 1);
		counter++;
	}
	if (!real_start)
		*range = counter;
	else
	{
		*range = counter;
		while (real_start != bench)
		{
			(*counter2)++;
			real_start = decrement_angle(real_start, 1);
		}
	} 
	return (increment_angle(start_angle, 1));
}
