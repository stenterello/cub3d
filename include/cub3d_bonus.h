/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 14:35:18 by gimartin          #+#    #+#             */
/*   Updated: 2022/09/29 22:43:06 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "libft/libft.h"
# include <mlx.h>
# include <stdlib.h>
# include <stdio.h>
# define _USE_MATH_DEFINES
# include <math.h>
# include <limits.h>
# define ANGLE_UNIT 0.00174
# define SPEED 3

typedef struct s_map
{
	char	**map;
	int		map_height_len[2];
	float	block_width;
	float	mini_block_width;
}				t_map;

typedef struct s_mlx
{
	void		*mlx;
	void		*mlx_win;
	int			win_width;
	int			win_height;
}				t_mlx;

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}				t_image;

typedef struct s_keys
{
	int	w_pressed;
	int	a_pressed;
	int	s_pressed;
	int	d_pressed;
	int	l_pressed;
	int	r_pressed;
	int	shift_pressed;
	int	e_pressed;
}				t_keys;

typedef struct s_bres_info
{
	int				swap;
	double			ab[2];
	double			d;
	int				sq[2];
	int				axy[2];
	unsigned int	color;
}				t_bres_info;

typedef struct s_ray
{
	double		angle;
	float		x;
	float		y;
	float		xyoff[2];
}				t_ray;

typedef struct s_gun
{
	char	*path;
	t_image	gun_img;
	int		off;
	int		counter;
	int		counted;
	int		last_shoot;
}				t_gun;

typedef struct s_player
{
	float	x;
	float	y;
	double	d_x;
	double	d_y;
	double	dir;
	float	speed;
	t_gun	gun;
	double	plane;
	double	plane_x;
	double	plane_y;
}				t_player;

typedef struct s_mouse
{
	int	last_x;
	int	last_y;
	int	moved;
}				t_mouse;

typedef struct s_sprite
{
	double	x;
	double	y;
	int		mini_x;
	int		mini_y;
	double	dist;
}				t_sprite;

typedef struct s_rules
{
	t_map			map;
	t_player		player;
	t_mlx			mlx;
	t_keys			keys;
	t_mouse			mouse;
	t_image			*north;
	t_image			*east;
	t_image			*south;
	t_image			*west;
	t_image			*door;
	t_image			*floor;
	t_image			*ceiling;
	t_image			enemy;
	int				line_offset;
	int				n_frames;
	int				last_door_action;
	double			*dist_array;
	int				n_sprites;
	t_sprite		*spr;
	t_sprite		*sort_spr;
}				t_rules;

typedef struct s_bres_data
{
	float			xy[2];
	float			xy2[2];
	unsigned int	color;
	int				x;
	double			dir1;
}				t_bres_data;

typedef struct s_draw_info
{
	t_bres_data	d;
	t_image		*view;
	t_image		*tex;
	double		l_h;
	double		off;
}				t_draw_info;

void			map_save(char *file, int fd, t_rules *rules);
void			map_checks(t_rules *rules);
void			init_rules(t_rules *rules);
void			init_window(t_mlx *mlx);
void			add_events(t_rules *rules);
int				loop_events(t_rules *rules);
int				press(int keycode, t_rules *rules);
int				release(int keycode, t_rules *rules);
void			game(t_rules *rules);
int				take_rgb(char *str, unsigned char rgb[3]);
void			read_file(char *file, t_rules *rules);
void			get_measures(int fd, int hl[2]);
int				rules_completed(t_rules *rules);
void			take_rules(int fd, t_rules *rules);
void			die(char *str);
void			raycast(t_rules *rules, t_image *view, t_image *minimap);
void			raycast_enemies(t_rules *rules);
int				colliding(t_rules *rules, float ray_cos,
					float ray_sin, int plus);
void			bresenham(t_bres_data *data, t_image *minimap,
					t_image *view, t_rules *rules);
int				get_abs(int n);
void			easy_pxl(t_image *image, int x, int y, int color);
double			final_length(float start_x, float start_y, float rxy[2]);
double			final_length_double(double start_x, double start_y, double rxy[2]);
void			draw_view(t_bres_data *d, t_image *view,
					t_rules *rules, t_image *tex);
void			move_player(t_rules *rules, char *dir);
double			our_modulo(double x, double y);
void			get_next_plus(t_rules *rules, float r_cos,
					float r_sin, int next[2]);
void			get_next_minus(t_rules *rules, float r_cos,
					float r_sin, int next[2]);
void			get_next_c_plus(t_rules *rules, float r_cos,
					float r_sin, int next_c[2]);
void			get_c_minus(t_rules *rules, float r_cos,
					float r_sin, int next_c[2]);
void			draw_mini_player(t_rules *rules, t_image *image);
void			minimap_2d(t_rules *rules, t_image *minimap);
double			increment_angle(double angle, int t);
double			decrement_angle(double angle, int t);
void			vertical_lines_check(double angle,
					t_rules *rules, float ret[3]);
void			horizontal_lines_check(double angle, t_rules *rules,
					float ret[3]);
int				virtual_horizontal_colliding(int ray_x, int ray_y,
					t_rules *rules, int dir);
int				virtual_vertical_colliding(int ray_x, int ray_y,
					t_rules *rules, int dir);
t_image			*choose_texture(t_rules *rules, t_bres_data *d);
int				choose_x(t_draw_info *info, float ref, t_rules *rules);
int				choose_y(int var, t_draw_info *info);
unsigned int	get_color(t_image *tex, int x, int y, t_rules *rules);
void			try_open_door(t_rules *rules);
int				is_door(int x, int y, t_rules *rules);
int				is_open_door(int x, int y, t_rules *rules);
void			try_open_door(t_rules *rules);
void			close_door(t_rules *rules);
void			open_door(t_rules *rules);
int				in_front_of_open_door(t_rules *rules);
int				in_front_of_door(t_rules *rules);
void			restore_gun(t_rules *rules);
void			insert_rule(char *str, t_rules *rules);
int				is_map(char *line);
void			insert_rule(char *str, t_rules *rules);
int				define_hor_ray_and_offset(t_rules *rules, t_ray *ray,
					double a_tan, float xy[2]);
int				define_ver_ray_and_offset(t_rules *rules, t_ray *ray,
					double n_tan, float xy[2]);
double			get_dist(t_rules *rules, t_bres_data *d);
double			get_fix(double angle);
void			shoot(t_rules *rules);
void			load_gun(t_rules *rules);
void			draw_sprites(t_rules *rules, t_image *view);
void			load_sprites(t_rules *rules);
int				count_sprites(t_map map);
void			save_sprites(t_rules *rules);
void			define_sprite(t_sprite *spr, int i, int j);
void			reload_sprites(t_rules *rules);

#endif
