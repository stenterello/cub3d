/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 02:45:13 by ddelladi          #+#    #+#             */
/*   Updated: 2022/07/21 11:15:37 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	bresenham(int xy[2], int xy2[2], unsigned int color, t_rules *rules)
{
	double	deltaX;
	double	deltaY;
	double	swap;
	double	a;
	double	b;
	double	d;
	double	k;
	int		s;
	int		q;
	int		ax;
	int		ay;

	swap = 0;
	deltaX = xy2[0] - xy[0];
	deltaY = xy2[1] - xy[1];
	if (get_abs(deltaX) < get_abs(deltaY))
	{
		swap = deltaX;
		deltaX = deltaY;
		deltaY = swap;
		swap = 1;
	}
	a = get_abs(deltaY);
	b = -get_abs(deltaX);
	ax = xy[0];
	ay = xy[1];
	d = 2 * a + b;
	s = 1;
	q = 1;
	if (ax > xy2[0])
		q = -1;
	if (ay > xy2[1])
		s = -1;
	k = 0;
	while (k++ < -b)
	{
		if (d > 0)
		{
			ax += q;
			ay += s;
			d += 2 * (a + b);
		}
		else
		{
			ax += q;
			if (swap)
			{
				ay += s;
				ax -= q;
			}
			d += 2 * a;
		}
		mlx_pixel_put(rules->mlx, rules->mlx_win, ax, ay, color);
	}
}
