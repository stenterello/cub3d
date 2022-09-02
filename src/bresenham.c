/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 02:45:13 by ddelladi          #+#    #+#             */
/*   Updated: 2022/09/02 13:26:00 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	bres_swap(double *delta_x, double *delta_y, int *swap)
{
	if (get_abs(*delta_x) < get_abs(*delta_y))
	{
		*swap = *delta_x;
		*delta_x = *delta_y;
		*delta_y = *swap;
		*swap = 1;
	}
}

void	bres_define(int axy[2], float xy2[2], int sq[2])
{
	if (axy[0] > xy2[0])
		sq[1] = -1;
	if (axy[1] > xy2[1])
		sq[0] = -1;
}

void	bres_draw(t_bres_info *info, t_image *image)
{
	int	k;

	k = 0;
	while (k++ < -info->ab[1])
	{
		if (info->d > 0)
		{
			info->axy[0] += info->sq[1];
			info->axy[1] += info->sq[0];
			info->d += 2 * (info->ab[0] + info->ab[1]);
		}
		else
		{
			info->axy[0] += info->sq[1];
			if (info->swap == 1)
			{
				info->axy[1] += info->sq[0];
				info->axy[0] -= info->sq[1];
			}
			info->d += 2 * info->ab[0];
		}
		my_mlx_pixel_put(image, (info->axy[0] / 4), (info->axy[1] / 4), info->color);
	}
}

void	bresenham(float xy[2], float xy2[2], unsigned int color, t_image *minimap, t_image *view, int x, t_rules *rules)//, double dir1)
{
	double		delta_x;
	double		delta_y;
	t_bres_info	info;

	info.swap = 0;
	delta_x = xy2[0] - xy[0];
	delta_y = xy2[1] - xy[1];
	bres_swap(&delta_x, &delta_y, &info.swap);
	info.ab[0] = get_abs(delta_y);
	info.ab[1] = -get_abs(delta_x);
	info.axy[0] = xy[0];
	info.axy[1] = xy[1];
	info.d = 2 * info.ab[0] + info.ab[1];
	info.sq[0] = 1;
	info.sq[1] = 1;
	info.color = color;
	bres_define(info.axy, xy2, info.sq);
	bres_draw(&info, minimap);
	draw_view(xy, xy2, view, x, rules);//, dir1);
}
