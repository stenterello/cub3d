/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 14:35:18 by gimartin          #+#    #+#             */
/*   Updated: 2022/10/07 17:38:54 by ddelladi         ###   ########.fr       */
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
	t_image			*sprite;
}				t_draw_coord;

t_draw_coord	*define_sprite_info(t_rules *rules, double trans_y,
					int s_x, int i);
void			draw_sprite_col(t_rules *rules, t_draw_coord *info,
					t_image *view, double trans_y);
#endif
