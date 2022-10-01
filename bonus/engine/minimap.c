/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 17:49:20 by ddelladi          #+#    #+#             */
/*   Updated: 2022/10/01 16:58:19 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static unsigned int	choose_color(char c)
{
	if (c == '0' || c == '3' || c == '4')
		return (0x0000FF00);
	else if (c == '1' || c == '2' || c == ' ')
		return (0x00FF0000);
	return (0x00000000);
}

static void	draw_mini_player(t_rules *rules, t_image *image)
{
	float	start_x;
	float	start_y;
	float	end_x;
	float	end_y;

	start_x = (rules->player.x / 4) - (rules->map.mini_block_width / 10);
	start_y = (rules->player.y / 4) - (rules->map.mini_block_width / 10);
	end_x = (rules->player.x / 4) + (rules->map.mini_block_width / 10);
	end_y = (rules->player.y / 4) + (rules->map.mini_block_width / 10);
	while (start_y < end_y)
	{
		start_x = (rules->player.x / 4) - (rules->map.mini_block_width / 10);
		while (start_x < end_x)
			easy_pxl(image, start_x++, start_y, 0x000000FF);
		start_y++;
	}
}

static void	draw_mini_block(t_rules *rules, int i, int j, t_image *image)
{
	unsigned int	color;
	int				start_end_x[2];
	int				start_end_y[2];
	int				back;

	color = choose_color(rules->map.map[i][j]);
	start_end_x[0] = j * rules->map.mini_block_width;
	start_end_x[1] = start_end_x[0] + rules->map.mini_block_width;
	start_end_y[0] = i * rules->map.mini_block_width;
	start_end_y[1] = start_end_y[0] + rules->map.mini_block_width;
	back = start_end_x[0];
	while (start_end_y[0] <= start_end_y[1])
	{
		start_end_x[0] = back;
		while (start_end_x[0] <= start_end_x[1])
			easy_pxl(image, start_end_x[0]++, start_end_y[0], color);
		start_end_y[0]++;
	}
	if (rules->map.map[i][j] == '4')
	{
		color = 0x000000FF;
		start_end_y[0] = i * rules->map.mini_block_width + rules->map.mini_block_width / 5;
		start_end_y[1] = start_end_y[0] + rules->map.mini_block_width / 8 * 5;
		while (start_end_y[0] <= start_end_y[1])
		{
			back += rules->map.mini_block_width / 8;
			start_end_x[0] = back + 1;
			start_end_x[1] = start_end_x[0] + rules->map.mini_block_width / 2;
			while (start_end_x[0] <= start_end_x[1])
				easy_pxl(image, start_end_x[0]++, start_end_y[0], color);
			start_end_y[0]++;
		}
	}

}

void	minimap2d(t_rules *rules, t_image *minimap)
{
	int		i;
	int		j;

	i = -1;
	while (++i < rules->map.map_height_len[1])
	{
		j = -1;
		while (++j < rules->map.map_height_len[0])
			draw_mini_block(rules, i, j, minimap);
	}
	draw_mini_player(rules, minimap);
}
