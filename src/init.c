/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 14:36:12 by gimartin          #+#    #+#             */
/*   Updated: 2022/09/01 16:13:14 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_rules(t_rules *rules)
{
	rules->map.map = NULL;
	rules->north_path = NULL;
	rules->east_path = NULL;
	rules->south_path = NULL;
	rules->west_path = NULL;
	rules->floor = 0;
	rules->ceiling = 0;
	rules->line_offset = 0;
	rules->mlx.win_width = 1280;
	rules->mlx.win_height = 720;
	rules->keys.w_pressed = 0;
	rules->keys.a_pressed = 0;
	rules->keys.s_pressed = 0;
	rules->keys.d_pressed = 0;
	rules->keys.l_pressed = 0;
	rules->keys.r_pressed = 0;
	rules->n_frames = 0;
}
