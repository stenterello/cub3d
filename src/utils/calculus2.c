/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculus2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 15:25:26 by ddelladi          #+#    #+#             */
/*   Updated: 2022/10/07 15:01:36 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	decrement_angle(double angle, int t)
{
	int	i;

	i = 0;
	while (i++ < t)
	{
		angle -= ANGLE_UNIT / 2;
		if (angle < 0)
			angle = 2 * M_PI;
	}
	return (angle);
}

double	increment_angle(double angle, int t)
{
	int	i;

	i = 0;
	while (i++ < t)
	{
		angle += ANGLE_UNIT / 2;
		if (angle > 2 * M_PI)
			angle = 0;
	}
	return (angle);
}

double	final_length(float start_x, float start_y, float rxy[2])
{
	if (rxy[0] == INT_MAX)
		return (INT_MAX);
	return (sqrt(pow(get_abs(start_x - rxy[0]), 2) + pow(start_y - rxy[1], 2)));
}

double	final_length_double(double start_x, double start_y, double rxy[2])
{
	if (rxy[0] == INT_MAX)
		return (INT_MAX);
	return (sqrt(pow(get_abs(start_x - rxy[0]), 2) + pow(start_y - rxy[1], 2)));
}
