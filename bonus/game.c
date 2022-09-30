/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 16:57:44 by ddelladi          #+#    #+#             */
/*   Updated: 2022/09/30 18:24:14 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	easy_pxl(t_image *image, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0)
		return ;
	dst = image->addr + (y * image->line_length + x * (image->bpp / 8));
	*(unsigned int *)dst = color;
	return ;
}

unsigned int	get_color_arr(unsigned char arr[3])
{
	return (*(unsigned int *)(unsigned char [4]){arr[2], arr[1], arr[0], 0});
}

unsigned int	get_sprite_color(t_image *tex, int x, int y, t_rules *rules)
{
	if ((x > 0 || x < rules->mlx.win_width
			|| y > 0 || y < rules->mlx.win_height) 
			&& *(unsigned int *)(tex->addr + (4 * (tex->width * y + x))))
	{
		return (*(unsigned int *)(tex->addr + (4 * (tex->width * y + x))));
	}
	return (0x0);
}

void	draw_gun(t_rules *rules, t_image *view)
{
	t_draw_coord	info;

	info.width = rules->mlx.win_width / 5;
	info.start_x = rules->mlx.win_width / 2 - info.width / 2;
	info.end_x = info.start_x + info.width;
	info.height = info.width * rules->player.gun.gun_img.height / rules->player.gun.gun_img.width;
	info.start_y = rules->mlx.win_height - info.height + rules->player.gun.off;
	info.end_y = info.start_y + info.height;
	info.bench_x = info.start_x;
	info.bench_y = info.start_y;
	while (info.start_x < info.end_x)
	{
		info.start_y = info.bench_y;
		info.t_x = (int)((info.start_x - info.bench_x) * rules->player.gun.gun_img.width / info.width);
		while (info.start_y < info.end_y)
		{
			info.t_y = (int)((info.start_y - info.bench_y) * rules->player.gun.gun_img.height / info.height);
			info.color = get_sprite_color(&rules->player.gun.gun_img, info.t_x, info.t_y, rules);
			if (info.color && info.start_x > 0 && info.start_x < rules->mlx.win_width && info.start_y > 0 && info.start_y < rules->mlx.win_height)
				easy_pxl(view, info.start_x, info.start_y, info.color);
			info.start_y++;
		}
		info.start_x++;
	}
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
	draw_sprites(rules, &view);
	draw_gun(rules, &view);
	mlx_put_image_to_window(rules->mlx.mlx, rules->mlx.mlx_win, view.img, 0, 0);
	mlx_put_image_to_window(rules->mlx.mlx, rules->mlx.mlx_win,
		minimap.img, 0, 0);
}
