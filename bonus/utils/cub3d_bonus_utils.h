/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus_utils.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 13:05:11 by ddelladi          #+#    #+#             */
/*   Updated: 2022/10/06 15:03:26 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_UTILS_H
# define CUB3D_BONUS_UTILS_H
# define ENEMY_TEX_1	"./img/sprites/enemy1.xpm"
# define ENEMY_TEX_2	"./img/sprites/enemy2.xpm"
# define ENEMY_TEX_3	"./img/sprites/enemy3.xpm"
# define ENEMY_ATTK_1	"./img/sprites/enemy4.xpm"
# define ENEMY_ATTK_2	"./img/sprites/enemy5.xpm"
# define ENEMY_ATTK_3	"./img/sprites/enemy6.xpm"
# define ENEMY_DIE_1	"./img/sprites/enemy7.xpm"
# define ENEMY_DIE_2	"./img/sprites/enemy8.xpm"
# define ENEMY_DIE_3	"./img/sprites/enemy9.xpm"
# define AMMO_TEX		"./img/sprites/ammo_storage.xpm"

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
void			load_gun(t_rules *rules);
void			restore_gun(t_rules *rules);
void			move_gun(t_gun *gun, int i);
void			shoot(t_rules *rules);
double			our_modulo(double x, double y);
int				get_abs(int n);
double			get_abs_double(double n);
int				choose_x(t_draw_info *info, float ref, t_rules *rules);
int				choose_y(int var, t_draw_info *info);
void			load_sprites(t_rules *rules);
void			reload_sprites(t_rules *rules);
int				count_sprites(t_map map);
int				*find_indexes(t_rules *rules);
void			fill_sort_spr(t_rules *rules, int *arr);
t_image			*get_rule(char *str, t_rules *rules, t_image *chosen);
void			init_img(t_rules *rules, t_image *img, int w, int h);
void			init_xpm_img(t_rules *rules, t_image **img, char *path);
double			increment_angle(double angle, int t);
double			decrement_angle(double angle, int t);
double			final_length(float start_x, float start_y, float rxy[2]);
double			final_length_double(double start_x, double start_y, double rxy[2]);
t_image			*choose_texture(t_rules *rules, t_bres_data *d);
double			get_dist(t_rules *rules, t_bres_data *d);
double			get_fix(double angle);
void			easy_pxl(t_image *image, int x, int y, int color);
unsigned int	get_color(t_image *tex, int x, int y, t_rules *rules);
unsigned int	get_color_arr(unsigned char arr[3]);
unsigned int	get_sprite_color(t_image *tex, int x, int y, t_rules *rules);

#endif
