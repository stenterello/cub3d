/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 18:32:43 by ddelladi          #+#    #+#             */
/*   Updated: 2022/07/26 12:37:29 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_window(t_rules *rules)
{
	rules->mlx.mlx = mlx_init();
	rules->mlx.mlx_win = mlx_new_window(rules->mlx.mlx,
			rules->mlx.win_width, rules->mlx.win_height, "Cub3d");
}

void	easy_pixel_put(t_frame *frame, int x, int y, int color)
{
	char	*dst;

	dst = frame->addr + (y * frame->line_length + x * (frame->bpp / 8));
	*(unsigned int *)dst = color;
}
