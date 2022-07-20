/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 18:33:06 by ddelladi          #+#    #+#             */
/*   Updated: 2022/07/20 11:43:37 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// eliminare dalla map il newline alla fine della riga... è inutile

void	draw_view_rays(t_rules *rules)
{
	float	angle;
	int		counter;

	angle = rules->player.dir - (ANGLE_UNIT * 45);
	counter = 0;
	while (angle < rules->player.dir + (ANGLE_UNIT * 45))
	{
		raycast_bresenham(angle, rules, &counter);
		angle += ANGLE_UNIT / 4;
	}
	// testing-only one-ray
	// raycast_bresenham(rules->player.dir, rules);
}

void	draw_mini_player(t_rules *rules)
{
	// t_frame	pl;
	// int		i;
	// int		j;

	// i = 0;
	// j = 0;
	// pl.img = mlx_new_image(rules->mlx, rules->mini_block_width / 3, rules->mini_block_width / 3);
	// pl.addr = mlx_get_data_addr(pl.img, &pl.bpp, &pl.line_length, &pl.endian);
	// while (i < rules->mini_block_width / 3)
	// {
	// 	j = 0;
	// 	while (j < rules->mini_block_width / 3)
	// 		easy_pixel_put(&pl, i, j++, 0x000000FF);
	// 	i++;
	// }
	// mlx_put_image_to_window(rules->mlx, rules->mlx_win, pl.img, rules->player.x - ((rules->mini_block_width / 3) / 2), rules->player.y - ((rules->mini_block_width / 3) / 2));
	draw_view_rays(rules);
}

void	draw_mini_block(t_rules *rules, int coord[2], int color)
{
	t_frame	img;
	int		i;
	int		j;

	i = 0;
	j = 0;
	img.img = mlx_new_image(rules->mlx, rules->mini_block_width, rules->mini_block_width);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_length, &img.endian);
	while (i < rules->mini_block_width - 1)
	{
		j = 0;
		while (j < rules->mini_block_width - 1)
			easy_pixel_put(&img, i, j++, color);
		i++;
	}
	mlx_put_image_to_window(rules->mlx, rules->mlx_win, img.img, coord[0], coord[1]);
	coord[0] += rules->mini_block_width;
}

void	paint_bg(t_rules *rules)
{
	int		i;
	int		j;
	t_frame	bg;

	bg.img = mlx_new_image(rules->mlx, rules->win_width, rules->win_height);
	bg.addr = mlx_get_data_addr(bg.img, &bg.bpp, &bg.line_length, &bg.endian);
	i = -1;
	printf("ceiling_color: %0x\n", get_hex_color(rules->ceiling_color));
	printf("floor_color: %0x\n", get_hex_color(rules->floor_color));
	while (++i < rules->win_height / 2)
	{
		j = 0;
		while (j < rules->win_width)
			easy_pixel_put(&bg, j++, i, get_hex_color(rules->ceiling_color));
	}
	while (i++ < rules->win_height)
	{
		j = 0;
		while (j < rules->win_width)
			easy_pixel_put(&bg, j++, i, get_hex_color(rules->floor_color));
	}
	mlx_put_image_to_window(rules->mlx, rules->mlx_win, bg.img, 0, 0);
}

void	minimap(t_rules *rules)
{
	// int	i;
	// int	j;
	// int	coord[2];

	paint_bg(rules);
	// i = 0;
	// coord[0] = 0;
	// coord[1] = 0;
	// while (rules->map[i])
	// {
	// 	j = 0;
	// 	while (rules->map[i][j])
	// 	{
	// 		if (rules->map[i][j] == '1')
	// 			draw_mini_block(rules, coord, 0x00FF0000);
	// 		else if (rules->map[i][j] == '0')
	// 			draw_mini_block(rules, coord, 0x0000FF00);
	// 		else if (rules->map[i][j] == ' ')
	// 			draw_mini_block(rules, coord, 0x00000000);
	// 		// else if (rules->map[i][j] != 32 && rules->map[i][j] != '\n')
	// 		// 	draw_mini_block(rules, coord, 0x000000FF);
	// 		j++;
	// 	}
	// 	i++;
	// 	coord[1] += rules->mini_block_width;
	// 	coord[0] = 0;
	// }
	draw_mini_player(rules);
}
