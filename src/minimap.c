/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 18:33:06 by ddelladi          #+#    #+#             */
/*   Updated: 2022/07/17 21:35:42 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// eliminare dalla map il newline alla fine della riga... è inutile

void	draw_view_rays(t_rules *rules)
{
	// float	mv_unit;
	// float	angle;

	// mv_unit = (float)(2 * PI) / 360;
	// angle = rules->player.dir - (mv_unit * 30);
	// while (angle < rules->player.dir + (mv_unit * 30))
	// {
	// 	raycast_bresenham(angle, rules);
	// 	angle += mv_unit;
	// }
	// testing-only one-ray
	raycast_bresenham(rules->player.dir, rules);
}

void	draw_mini_player(t_rules *rules)
{
	t_frame	pl;
	int		i;
	int		j;

	i = 0;
	j = 0;
	pl.img = mlx_new_image(rules->mlx, rules->mini_block_width / 3, rules->mini_block_width / 3);
	pl.addr = mlx_get_data_addr(pl.img, &pl.bpp, &pl.line_length, &pl.endian);
	while (i < rules->mini_block_width / 3)
	{
		j = 0;
		while (j < rules->mini_block_width / 3)
			easy_pixel_put(&pl, i, j++, 0x000000FF);
		i++;
	}
	mlx_put_image_to_window(rules->mlx, rules->mlx_win, pl.img, rules->player.x - ((rules->mini_block_width / 3) / 2), rules->player.y - ((rules->mini_block_width / 3) / 2));
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


void	minimap(t_rules *rules)
{
	int	i;
	int	j;
	int	coord[2];

	i = 0;
	coord[0] = 0;
	coord[1] = 0;
	while (rules->map[i])
	{
		j = 0;
		while (rules->map[i][j])
		{
			if (rules->map[i][j] == '1')
				draw_mini_block(rules, coord, 0x00FF0000);
			else if (rules->map[i][j] == '0')
				draw_mini_block(rules, coord, 0x0000FF00);
			else if (rules->map[i][j] == ' ')
				draw_mini_block(rules, coord, 0x00000000);
			// else if (rules->map[i][j] != 32 && rules->map[i][j] != '\n')
			// 	draw_mini_block(rules, coord, 0x000000FF);
			j++;
		}
		i++;
		coord[1] += rules->mini_block_width;
		coord[0] = 0;
	}
	draw_mini_player(rules);
}
