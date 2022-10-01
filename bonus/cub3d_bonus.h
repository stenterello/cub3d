/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 14:35:18 by gimartin          #+#    #+#             */
/*   Updated: 2022/10/01 13:21:06 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "engine/cub3d_bonus_engine.h"
# include "map_parser/cub3d_bonus_map.h"
# include "utils/cub3d_bonus_utils.h"
# include "libft.h"
# include <mlx.h>
# include <stdlib.h>
# include <stdio.h>
# define _USE_MATH_DEFINES
# include <math.h>
# include <limits.h>
# define ANGLE_UNIT 0.00174
# define SPEED 3

typedef struct s_ray
{
	double		angle;
	float		x;
	float		y;
	float		xyoff[2];
}				t_ray;

typedef struct s_draw_coord
{
	double			start_x;
	double			end_x;
	double			start_y;
	double			end_y;
	double			width;
	double			height;
	double			bench_x;
	double			bench_y;
	unsigned int	color;
	int				t_x;
	int				t_y;
}				t_draw_coord;

#endif
