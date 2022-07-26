/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 13:34:25 by ddelladi          #+#    #+#             */
/*   Updated: 2022/07/26 15:32:58 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../include/libft/libft.h"
# include "../include/mlx_linux/mlx.h"
# include <stdio.h>
# include <math.h>
# include <limits.h>
# define PI 3.1415926535
# define ANGLE_UNIT 0.0174533

typedef struct s_bres_info
{
	int				swap;
	double			ab[2];
	double			d;
	int				sq[2];
	int				axy[2];
	unsigned int	color;
}				t_bres_info;

typedef struct s_xpm	t_xpm;

typedef struct s_texture
{
	char	***encoded;
	t_xpm	*pairs;
	int		last_x;
	int		size[2];
	int		n_colors;
	char	*delimiters;
}				t_texture;

typedef struct s_xpm
{
	char	*key;
	char	*value;
	t_xpm	*next;
}				t_xpm;

typedef struct s_ray
{
	double		angle;
	float		x;
	float		y;
	float		xyoff[2];
}				t_ray;

typedef struct s_frame
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}				t_frame;

typedef struct s_miniplayer
{
	int	x;
	int	y;
}				t_miniplayer;

typedef struct s_player
{
	int				x;
	int				y;
	double			d_x;
	double			d_y;
	double			dir;
	float			speed;
	t_miniplayer	miniplayer;
}				t_player;

typedef struct s_map
{
	char	**map;
	char	**floor;
	char	**ceiling;
	int		map_width;
	int		map_height;
	int		block;
	int		mini_block;
}				t_map;

typedef struct s_keys
{
	int			w_pressed;
	int			a_pressed;
	int			s_pressed;
	int			d_pressed;
	int			l_pressed;
	int			r_pressed;
}				t_keys;

typedef struct s_mlx
{
	void		*mlx;
	void		*mlx_win;
	int			win_width;
	int			win_height;
}				t_mlx;

typedef struct s_rules
{
	t_mlx		mlx;
	t_map		map;
	t_player	player;
	t_texture	textures[4];
	t_keys		keys;
	char		**paths;
	int			floor_color[3];
	int			ceiling_color[3];
	double		d_angle;
	int			nframes;
	int			rate;
	int			counter;
}				t_rules;

typedef struct s_texture_info
{
	t_rules		*rules;
	t_frame		*scene;
	t_texture	*texture;
	int			flag;
}				t_texture_info;

void	usage(void);
void	die(char *str);
void	input_check_and_rules_gen(int argc, char **argv, t_rules *rules);
void	generate_rules(int fd, t_rules *rules, char *file);
int		is_parameter(char *str);
int		is_path(char *str);
void	insert_rule(char *rul, t_rules *rules);
void	malloc_c(char **dst, int len);
int		count_map_height_and_max_width(int fd, t_rules *rules);
void	define_map(int fd, t_rules *rules);
void	add_events(t_rules *rules);
void	minimap(t_rules *rules);
void	init_window(t_rules *rules);
void	easy_pixel_put(t_frame *frame, int x, int y, int color);
void	draw_mini_block(t_rules *rules, int coord[2], int color);
void	free_rules(t_rules *rules);
void	raycast_bresenham(double angle, t_rules *rules, t_frame *scene);
int		colliding(t_rules *rules, char *dir);
int		get_abs(int n);
void	bresenham(float xy[2], float xy2[2],
			unsigned int color, t_rules *rules);
int		virtual_horizontal_colliding(int ray_x, int ray_y,
			t_rules *rules, int dir);
int		virtual_vertical_colliding(int ray_x, int ray_y,
			t_rules *rules, int dir);
void	draw_3d(t_rules *rules, double dist, int *x,
			double ray_angle);
int		get_hex_color(int rgb[3]);
void	check_player(char *tmp, t_rules *rules, int y);
void	mini_raycast(double angle, t_rules *rules);
double	decrement_angle(double angle, int off);
double	increment_angle(double angle, int off);
void	define_texture(char *path, t_texture *texture);
int		get_nbr_hex(char *str);
void	draw_texture(int x, double dist,
			t_texture_info *info, int color_unit_x);
int		get_line_width(t_rules *rules);
void	game(t_rules *rules);
void	draw_view_rays(t_rules *rules);
int		colliding2(t_rules *rules, float ray_cos, float ray_sin, int plus);
void	update_pov(t_rules *rules);
int		verify_collide2(t_rules *rules, int next_c[2]);
int		get_xpm_color(t_texture *texture, int y, int x);
int		encode_rgb(u_int8_t alpha, u_int8_t red, u_int8_t green, u_int8_t blue);
void	skip_to_benchmark(int fd, char *benchmark);
void	define_player(char *tmp, t_rules *rules, int y);
void	define_map(int fd, t_rules *rules);
void	define_paint(t_texture_info *info, float pts[3],
			double angle);
void	move_player(t_rules *rules, char *dir);
double	final_length(float start_x, float start_y, float rxy[2]);
int		choose_texture(int n, int flag);
int		mini_virtual_horizontal_colliding(float ray_x, float ray_y,
			t_rules *rules, int dir);
int		mini_virtual_vertical_colliding(int ray_x, int ray_y,
			t_rules *rules, int dir);
void	get_next_plus(t_rules *rules, float ray_cos,
			float ray_sin, int next[2]);
void	get_next_minus(t_rules *rules, float ray_cos,
			float ray_sin, int next[2]);
void	get_next_c_plus(t_rules *rules, float ray_cos,
			float ray_sin, int next_c[2]);
void	get_next_c_minus(t_rules *rules, float ray_cos,
			float ray_sin, int next_c[2]);

#endif
