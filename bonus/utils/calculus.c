/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculus.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 17:08:38 by ddelladi          #+#    #+#             */
/*   Updated: 2022/10/01 15:23:57 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	get_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

double	get_abs_double(double n)
{
	if (n < 0)
		return (-n);
	return (n);
}

double	our_modulo(double x, double y)
{
	while (x >= y && y != 0)
		x -= y;
	return (x);
}

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
