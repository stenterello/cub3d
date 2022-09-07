/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 16:57:44 by ddelladi          #+#    #+#             */
/*   Updated: 2022/09/07 14:50:16 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	easy_pxl(t_image *image, int x, int y, int color)
{
	char	*dst;

	dst = image->addr + (y * image->line_length + x * (image->bpp / 8));
	*(unsigned int *)dst = color;
}

unsigned int	get_color_arr(unsigned char arr[3])
{
	return (*(unsigned int *)(unsigned char [4]){arr[2], arr[1], arr[0], 0});
}

void	draw_ceiling(t_rules *rules, t_image *view)
{
	int	x;
	int	y;

	x = -1;
	while (++x < rules->mlx.win_width)
	{
		y = 0;
		while (y < rules->mlx.win_height / 2)
			easy_pxl(view, x, y++, get_color_arr(rules->ceiling_color));
	}
}

void	draw_floor(t_rules *rules, t_image *view)
{
	int	x;
	int	y;

	x = -1;
	while (++x < rules->mlx.win_width)
	{
		y = rules->mlx.win_height / 2 - 1;
		while (++y < rules->mlx.win_height)
			easy_pxl(view, x, y, get_color_arr(rules->floor_color));
	}
}

void	game(t_rules *rules)
{
	t_image	view;

	view.img = mlx_new_image(rules->mlx.mlx, rules->mlx.win_width,
			rules->mlx.win_height);
	view.addr = mlx_get_data_addr(view.img, &view.bpp, &view.line_length,
			&view.endian);
	draw_ceiling(rules, &view);
	draw_floor(rules, &view);
	raycast(rules, &view);
	mlx_put_image_to_window(rules->mlx.mlx, rules->mlx.mlx_win, view.img, 0, 0);
}
