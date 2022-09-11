/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 16:57:44 by ddelladi          #+#    #+#             */
/*   Updated: 2022/09/10 13:55:32 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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

// void	draw_floor(t_rules *rules, t_image *view)
// {
// 	int		y;
// 	int		x;
// 	double	ray_dir_x0;
// 	double	ray_dir_y0;
// 	double	ray_dir_x1;
// 	double	ray_dir_y1;
// 	int		p;
// 	double	z;
// 	double	dist;
// 	double	step_x;
// 	double	step_y;
// 	double	floor_x;
// 	double	floor_y;
// 	int		cell_x;
// 	int		cell_y;
// 	int		tx;
// 	int		ty;

// 	y = rules->mlx.win_height / 2 + 1;
// 	while (y < rules->mlx.win_height)
// 	{
// 		ray_dir_x0 = rules->player.d_x - rules->player.plane_x;
// 		ray_dir_y0 = rules->player.d_y - rules->player.plane_y;
// 		ray_dir_x1 = rules->player.d_x + rules->player.plane_x;
// 		ray_dir_y1 = rules->player.d_y + rules->player.plane_y;
// 		p = y - rules->mlx.win_height / 2;
// 		z = rules->mlx.win_height * 0.5;
// 		dist = z / p;
// 		step_x = dist * (ray_dir_x1 - ray_dir_x0) / rules->mlx.win_width;
// 		step_y = dist * (ray_dir_y1 - ray_dir_y0) / rules->mlx.win_width;
// 		floor_x = rules->player.x + dist * ray_dir_x0;
// 		floor_y = rules->player.y + dist * ray_dir_y0;
// 		x = 0;
// 		while (x < rules->mlx.win_width)
// 		{
// 			cell_x = (int)floor_x;
// 			cell_y = (int)floor_y;
// 			tx = (int)(rules->floor->width * (floor_x - cell_x)) & (rules->floor->width - 1);
// 			ty = (int)(rules->floor->height * (floor_y - cell_y)) & (rules->floor->height - 1);
// 			easy_pxl(view, x, y, get_color(rules->floor, tx, ty, rules));
// 			floor_x += step_x;
// 			floor_y += step_y;
// 			x++;
// 		}
// 		y++;
// 	}
// }

void	load_gun(t_rules *rules)
{
	t_image	gun;

	gun.img = mlx_xpm_file_to_image(rules->mlx.mlx, "img/fps_player.xpm", &gun.width, &gun.height);
	mlx_put_image_to_window(rules->mlx.mlx, rules->mlx.mlx_win, gun.img, rules->mlx.win_width / 2 - gun.width / 2, rules->mlx.win_height - gun.height + rules->player.gun.off);
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
	// draw_ceiling(rules, &view);
	// draw_floor(rules, &view);
	raycast(rules, &view, &minimap);
	mlx_put_image_to_window(rules->mlx.mlx, rules->mlx.mlx_win, view.img, 0, 0);
	mlx_put_image_to_window(rules->mlx.mlx, rules->mlx.mlx_win,
		minimap.img, 0, 0);
	load_gun(rules);
}
