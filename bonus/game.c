/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 16:57:44 by ddelladi          #+#    #+#             */
/*   Updated: 2022/09/22 16:24:07 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

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

void	load_gun(t_rules *rules, const char *path)
{
	t_image	*gun;

	gun = &rules->player.gun.gun_img;
	gun->img = mlx_xpm_file_to_image(rules->mlx.mlx, (char *)path, &gun->width, &gun->height);
	mlx_put_image_to_window(rules->mlx.mlx, rules->mlx.mlx_win, gun->img, rules->mlx.win_width / 2 - gun->width / 2, rules->mlx.win_height - gun->height + rules->player.gun.off);
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
	minimap_2d(rules, &minimap);
	draw_mini_player(rules, &minimap);
	raycast(rules, &view, &minimap);
	raycast_enemies(rules, &view);
	mlx_put_image_to_window(rules->mlx.mlx, rules->mlx.mlx_win, view.img, 0, 0);
	mlx_put_image_to_window(rules->mlx.mlx, rules->mlx.mlx_win,
		minimap.img, 0, 0);
	load_gun(rules, rules->player.gun.path);
}
