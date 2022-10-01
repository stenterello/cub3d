/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus_utils.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 13:05:11 by ddelladi          #+#    #+#             */
/*   Updated: 2022/10/01 13:28:31 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_UTILS_H
# define CUB3D_BONUS_UTILS_H

typedef struct s_draw_info
{
	t_bres_data	d;
	t_image		*view;
	t_image		*tex;
	double		l_h;
	double		off;
}				t_draw_info;

void			die(char *str);
void			take_rules(int fd, t_rules *rules);
void			init_window(t_mlx *mlx);
void			init_rules(t_rules *rules);
int				rules_completed(t_rules *rules);
void			load_gun(t_rules *rules);
double			our_modulo(double x, double y);
int				get_abs(int n);
int				choose_x(t_draw_info *info, float ref, t_rules *rules);
int				choose_y(int var, t_draw_info *info);
unsigned int	get_color(t_image *tex, int x, int y, t_rules *rules);
void			shoot(t_rules *rules);

#endif
