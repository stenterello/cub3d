/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 13:34:25 by ddelladi          #+#    #+#             */
/*   Updated: 2022/07/21 22:22:14 by ddelladi         ###   ########.fr       */
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

typedef struct s_xpm t_xpm;

typedef struct s_texture
{
	char	**encoded;
	t_xpm	*pairs;
	int		last_x;
	int		size[2];
	int		n_colors;
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
	t_miniplayer	miniplayer;
}				t_player;

typedef struct s_rules
{
	char		**map;
	char		*north_texture_path;
	char		*south_texture_path;
	char		*east_texture_path;
	char		*west_texture_path;
	int			floor_color[3];
	int			ceiling_color[3];
	t_texture	north_texture;
	t_texture	south_texture;
	t_texture	east_texture;
	t_texture	west_texture;
	void		*mlx;
	void		*mlx_win;
	int			win_width;
	int			win_height;
	int			map_height;
	int			map_width;
	int			mini_block_width;
	int			block_width;
	t_player	player;
	double		d_angle;
}				t_rules;

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
void	raycast_bresenham(double angle, t_rules *rules, int *counter, t_frame *scene);
int		colliding(t_rules *rules, char *dir);
int		get_abs(int n);
void	bresenham(float xy[2], float xy2[2], unsigned int color, t_rules *rules);
int		virtual_horizontal_colliding(int rayX, int rayY, t_rules *rules, int dir);
int		virtual_vertical_colliding(int rayX, int rayY, t_rules *rules, int dir);
void	draw_3d(t_rules *rules, double dist, int *x, double ray_angle);//, int color);
int		get_hex_color(int rgb[3]);
void	check_player(char *tmp, t_rules *rules, int y);
void	mini_raycast(double angle, t_rules *rules);
double	decrement_angle(double angle, int off);
double	increment_angle(double angle, int off);
void	define_texture(char *path, t_texture *texture);
int		get_nbr_hex(char *str);
void	draw_texture(int x, float y1, float y2, t_rules *rules, t_frame *scene);
int		get_line_width(t_rules *rules);
void	game(t_rules *rules);
void	draw_view_rays(t_rules *rules);

#endif
