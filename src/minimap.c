/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 16:57:44 by ddelladi          #+#    #+#             */
/*   Updated: 2022/09/01 18:49:21 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned int	choose_color(char c)
{
	if (c == '0')
		return (0x0000FF00);
	else if (c == '1')
		return (0x00FF0000);
	else if (c == ' ')
		return (0x00000000);
	else
		return (0x00000000);
}

void	my_mlx_pixel_put(t_image *image, int x, int y, int color)
{
	char	*dst;

	dst = image->addr + (y * image->line_length + x * (image->bpp / 8));
	*(unsigned int *)dst = color;
}

void	draw_mini_block(t_rules *rules, int i, int j, t_image *image)
{
	unsigned int	color;
	int				start_end_x[2];
	int				start_end_y[2];
	int				back;

	color = choose_color(rules->map.map[i][j]);
	start_end_x[0] = j * rules->map.block_width;
	start_end_x[1] = start_end_x[0] + rules->map.block_width;
	start_end_y[0] = i * rules->map.block_width;
	start_end_y[1] = start_end_y[0] + rules->map.block_width;
	back = start_end_x[0];
	while (start_end_y[0] < start_end_y[1])
	{
		start_end_x[0] = back;
		while (start_end_x[0] < start_end_x[1])
			my_mlx_pixel_put(image, start_end_x[0]++, start_end_y[0], color);
		start_end_y[0]++;
	}
}

void	draw_mini_player(t_rules *rules, t_image *image)
{
	float	start_x;
	float	start_y;
	float	end_x;
	float	end_y;

	start_x = rules->player.x - (rules->map.block_width / 10);
	start_y = rules->player.y - (rules->map.block_width / 10);
	end_x = rules->player.x + (rules->map.block_width / 10);
	end_y = rules->player.y + (rules->map.block_width / 10);
	while (start_y < end_y)
	{
		start_x = rules->player.x - (rules->map.block_width / 10);
		while (start_x < end_x)
			my_mlx_pixel_put(image, start_x++, start_y, 0x000000FF);
		start_y++;
	}	
}

void	minimap(t_rules *rules)
{
	int		i;
	int		j;
	t_image	image;

	image.img = mlx_new_image(rules->mlx.mlx, rules->map.map_height_len[0]
			* rules->map.block_width, rules->map.map_height_len[1]
			* rules->map.block_width);
	image.addr = mlx_get_data_addr(image.img, &image.bpp, &image.line_length,
			&image.endian);
	i = -1;
	while (++i < rules->map.map_height_len[1])
	{
		j = -1;
		while (++j < rules->map.map_height_len[0])
			draw_mini_block(rules, i, j, &image);
	}
	draw_mini_player(rules, &image);
	raycast(rules, &image);
	mlx_put_image_to_window(rules->mlx.mlx, rules->mlx.mlx_win,
		image.img, 0, 0);
}
