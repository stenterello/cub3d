/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_enemies_utils2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 12:03:55 by ddelladi          #+#    #+#             */
/*   Updated: 2022/09/28 19:40:26 by ddelladi         ###   ########.fr       */
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

	if (rules->player.dir > M_PI / 2 && rules->player.dir < 3 * M_PI / 2)
		en_xy[0] = coord[0] * rules->map.block_width - rules->map.block_width / 2;
	else
		en_xy[0] = coord[0] * rules->map.block_width + rules->map.block_width / 2;
	en_xy[1] = coord[1] * rules->map.block_width + rules->map.block_width / 2;
	return (final_length_double(rules->player.x, rules->player.y, en_xy));
	// il calcolo cambia in base alla direzione del player
}

double	get_end_angle(t_rules *rules, double start_angle, int *range, int *counter2, double real_start)
{
	float	end_pts[2];
	int		counter;
	double	bench;

	counter = 0;
	ft_bzero(&end_pts, 8);
	bench = start_angle;
	while (enemy_in_view(start_angle, rules, end_pts))
	{
		start_angle = decrement_angle(start_angle, 1);
		counter++;
	}
	if (counter < 10)
		enemy_in_view(decrement_angle(start_angle, counter), rules, end_pts);
	*range = counter;
	if (real_start)
	{
		while (real_start != bench)
		{
			(*counter2)++;
			real_start = decrement_angle(real_start, 1);
		}
	} 
	return (increment_angle(start_angle, 1));
}

double	get_real_start_angle(double angle, t_bres_data *data, t_rules *rules)
{
	int	coord[2];
	int	coord2[2];

	ft_bzero(&coord, 8);
	ft_bzero(&coord2, 8);
	get_enemy_mini_coord(rules, data, coord);
	get_enemy_mini_coord(rules, data, coord2);
	while (coord[0] == coord2[0] && coord[1] == coord2[1] && enemy_in_view(angle, rules, data->xy2))
	{
		angle = increment_angle(angle, 1);
		get_enemy_mini_coord(rules, data, coord2);
	}
	return (angle);
}
