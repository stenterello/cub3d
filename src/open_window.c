/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 16:33:17 by ddelladi          #+#    #+#             */
/*   Updated: 2022/08/26 18:10:24 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_window(t_rules *rules)
{
	rules->mlx.mlx = mlx_init();
	if (!rules->mlx.mlx)
		die("Error initializing Minilibx. Aborting");
	rules->mlx.mlx_win = mlx_new_window(rules->mlx.mlx,
			rules->mlx.win_width, rules->mlx.win_height, "Cub3d");
}
