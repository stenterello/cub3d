/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 13:05:11 by ddelladi          #+#    #+#             */
/*   Updated: 2022/10/07 14:25:04 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_UTILS_H
# define CUB3D_UTILS_H

typedef struct s_draw_info
{
	t_bres_data	d;
	t_image		*view;
	t_image		*tex;
	double		l_h;
	double		off;
}				t_draw_info;

void			die(char *str);
void			init_window(t_mlx *mlx);
void			init_rules(t_rules *rules);
void			init_player(t_rules *rules, char c, int i, int j);
double			our_modulo(double x, double y);
int				get_abs(int n);
double			get_abs_double(double n);
int				choose_x(t_draw_info *info, float ref, t_rules *rules);
int				choose_y(int var, t_draw_info *info);
t_image			*get_rule(char *str, t_rules *rules, t_image *chosen);
void			init_img(t_rules *rules, t_image *img, int w, int h);
void			init_xpm_img(t_rules *rules, t_image **img, char *path);
double			increment_angle(double angle, int t);
double			decrement_angle(double angle, int t);
double			final_length(float start_x, float start_y, float rxy[2]);
t_image			*choose_texture(t_rules *rules, t_bres_data *d);
double			get_dist(t_rules *rules, t_bres_data *d);
double			get_fix(double angle);
void			easy_pxl(t_image *image, int x, int y, int color);
unsigned int	get_color(t_image *tex, int x, int y, t_rules *rules);
unsigned int	get_color_arr(unsigned char arr[3]);

#endif
