/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 17:49:20 by ddelladi          #+#    #+#             */
/*   Updated: 2022/09/07 16:42:35 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

unsigned int	choose_color(char c)
{
	if (c == '0')
		return (0x0000FF00);
	else if (c == '1' || c == '2')
		return (0x00FF0000);
	else if (c == ' ')
		return (0x00000000);
	else
		return (0x00000000);
}

void	draw_mini_block(t_rules *rules, int i, int j, t_image *image)
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
}

void	draw_mini_player(t_rules *rules, t_image *image)
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

void	minimap_2d(t_rules *rules, t_image *minimap)
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
}
