/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 16:57:44 by ddelladi          #+#    #+#             */
/*   Updated: 2022/09/02 17:51:56 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	easy_pxl(t_image *image, int x, int y, int color)
{
	char	*dst;

	dst = image->addr + (y * image->line_length + x * (image->bpp / 8));
	*(unsigned int *)dst = color;
}

void	game(t_rules *rules)
{
	t_image	view;
	t_image	minimap;

	view.img = mlx_new_image(rules->mlx.mlx, rules->mlx.win_width,
			rules->mlx.win_height);
	view.addr = mlx_get_data_addr(view.img, &view.bpp, &view.line_length,
			&view.endian);
	minimap.img = mlx_new_image(rules->mlx.mlx,
			rules->map.map_height_len[0] * rules->map.mini_block_width,
			rules->map.map_height_len[1] * rules->map.mini_block_width);
	minimap.addr = mlx_get_data_addr(minimap.img, &minimap.bpp,
			&minimap.line_length, &minimap.endian);
	copy_game(rules, &minimap);
	draw_mini_player(rules, &minimap);
	raycast(rules, &view, &minimap);
	mlx_put_image_to_window(rules->mlx.mlx, rules->mlx.mlx_win, view.img, 0, 0);
	mlx_put_image_to_window(rules->mlx.mlx, rules->mlx.mlx_win,
		minimap.img, 0, 0);
}
