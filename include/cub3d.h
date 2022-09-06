/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 14:35:18 by gimartin          #+#    #+#             */
/*   Updated: 2022/09/06 17:24:39 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft/libft.h"
# include <mlx.h>
# include <stdlib.h>
# include <stdio.h>
# define _USE_MATH_DEFINES
# include <math.h>
# include <limits.h>
# define ANGLE_UNIT 0.00174
# define SPEED 2

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

typedef struct s_couples
{
	char			*key;
	unsigned int	value;
	void			*next;
}				t_couples;

typedef struct s_xpm
{
	char		**encoded;
	t_couples	couples;
	int			size[2];
	int			n_colors;
	int			char_n;
}				t_xpm;

typedef struct s_player
{
	float	x;
	float	y;
	double	d_x;
	double	d_y;
	double	dir;
	float	speed;
	t_xpm	img;
}				t_player;

typedef struct s_rules
{
	t_map			map;
	t_player		player;
	t_mlx			mlx;
	t_keys			keys;
	t_image			*north;
	t_image			*east;
	t_image			*south;
	t_image			*west;
	unsigned char	floor_color[3];
	unsigned char	ceiling_color[3];
	int				floor;
	int				ceiling;
	int				line_offset;
	int				n_frames;
	int				x_counter;
}				t_rules;

typedef struct s_bres_data
{
	float			xy[2];
	float			xy2[2];
	unsigned int	color;
	int				x;
	double			dir1;
	t_xpm			texture;
}				t_bres_data;

void			map_save(char *file, int fd, t_rules *rules);
void			map_checks(t_rules *rules);
void			init_rules(t_rules *rules);
void			init_window(t_rules *rules);
void			add_events(t_rules *rules);
int				loop_events(t_rules *rules);
int				press(int keycode, t_rules *rules);
int				release(int keycode, t_rules *rules);
void			game(t_rules *rules);
int				path_start(char *str);
int				take_rgb(char *str, unsigned char rgb[3]);
void			read_file(char *file, t_rules *rules);
void			get_measures(int fd, int hl[2]);
int				rules_completed(t_rules *rules);
void			take_rules(int fd, t_rules *rules);
void			die(char *str);
void			raycast(t_rules *rules, t_image *view, t_image *minimap);
int				wall_coll(t_rules rules);
int				colliding(t_rules *rules, float ray_cos,
					float ray_sin, int plus);
void			bresenham(t_bres_data data, t_image *minimap,
					t_image *view, t_rules *rules);
int				get_abs(int n);
void			easy_pxl(t_image *image, int x, int y, int color);
double			final_length(float start_x, float start_y, float rxy[2]);
void			draw_view(t_bres_data d, t_image *view, t_rules *rules, t_image *tex);
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
int				times(double dir1, double dir2);
void			vertical_lines_check(double angle,
					t_rules *rules, float ret[3]);
void			horizontal_lines_check(double angle, t_rules *rules,
					float ret[3]);
int				virtual_horizontal_colliding(int ray_x, int ray_y,
					t_rules *rules, int dir);
int				virtual_vertical_colliding(int ray_x, int ray_y,
					t_rules *rules, int dir);
t_xpm			get_texture(t_rules *rules);
unsigned int	get_xpm_color(t_rules *rules, float dst[2], int y,
					double line_height, int off);
int				get_xpm_color2(char *encoded, t_xpm xpm);
t_couples		take_rgb_couples(int fd);
unsigned int	find_color(t_rules *rules, t_xpm *north, int c, int n);
int				get_n_colors_and_size(char *s, int size[2]);
char			**take_encoded_xpm(int fd, int size[2]);
int				next_num(int i, char *s);
void			get_size_and_colors(int fd, t_xpm *ret);
unsigned int	get_hex_color(char *str);
int				to_color(int i, char *tmp);
t_image			*choose_texture(t_rules *rules, float xy[2]);

#endif
