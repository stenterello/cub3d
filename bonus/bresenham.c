/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 02:45:13 by ddelladi          #+#    #+#             */
/*   Updated: 2022/09/28 14:47:42 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

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

void	minimap_rays(t_bres_info *info, t_image *minimap)
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
		easy_pxl(minimap, (info->axy[0] / 4), (info->axy[1] / 4), info->color);
	}
}

void	bresenham(t_bres_data *d, t_image *min, t_image *view, t_rules *rules)
{
	double		delta_x;
	double		delta_y;
	t_bres_info	info;
	t_image		*tex;

	info.swap = 0;
	delta_x = d->xy2[0] - d->xy[0];
	delta_y = d->xy2[1] - d->xy[1];
	bres_swap(&delta_x, &delta_y, &info.swap);
	info.ab[0] = get_abs(delta_y);
	info.ab[1] = -get_abs(delta_x);
	info.axy[0] = d->xy[0];
	info.axy[1] = d->xy[1];
	info.d = 2 * info.ab[0] + info.ab[1];
	info.sq[0] = 1;
	info.sq[1] = 1;
	info.color = d->color;
	bres_define(info.axy, d->xy2, info.sq);
	minimap_rays(&info, min);
	tex = choose_texture(rules, d);
	draw_view(d, view, rules, tex);
}
