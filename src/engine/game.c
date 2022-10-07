/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 16:57:44 by ddelladi          #+#    #+#             */
/*   Updated: 2022/10/07 16:23:49 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	game(t_rules *rules)
{
	t_image	view;
	t_image	minimap;

	init_img(rules, &view, rules->mlx.win_width, rules->mlx.win_height);
	init_img(rules, &minimap,
		rules->map.map_height_len[0] * rules->map.mini_block_width,
		rules->map.map_height_len[1] * rules->map.mini_block_width);
	raycast(rules, &view, &minimap);
	mlx_put_image_to_window(rules->mlx.mlx, rules->mlx.mlx_win, view.img, 0, 0);
}
