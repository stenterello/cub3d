/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 16:33:17 by ddelladi          #+#    #+#             */
/*   Updated: 2022/09/07 15:49:07 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	init_window(t_mlx *mlx)
{

	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		die("Error initializing Minilibx. Aborting");
	mlx->mlx_win = mlx_new_window(mlx->mlx,
			mlx->win_width, mlx->win_height, "Cub3d");
}
