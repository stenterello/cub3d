/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 14:35:18 by gimartin          #+#    #+#             */
/*   Updated: 2022/09/02 17:05:04 by ddelladi         ###   ########.fr       */
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
}				t_image;

typedef struct s_keys
{
	int	w_pressed;
	int	a_pressed;
	int	s_pressed;
	int	d_pressed;
	int	l_pressed;
	int	r_pressed;
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
	t_map		map;
	t_player	player;
	t_mlx		mlx;
	t_keys		keys;
	char		*north_path;
	char		*east_path;
	char		*south_path;
	char		*west_path;
	int			floor_color[3];
	int			ceiling_color[3];
	int			floor;
	int			ceiling;
	int			line_offset;
	int			n_frames;
}				t_rules;

void	map_save(char *file, int fd, t_rules *rules);
void	map_checks(t_rules *rules);
void	init_rules(t_rules *rules);
void	init_window(t_rules *rules);
void	add_events(t_rules *rules);
int		loop_events(t_rules *rules);
int		press(int keycode, t_rules *rules);
int		release(int keycode, t_rules *rules);
void	game(t_rules *rules);
int		path_start(char *str);
int		take_rgb(char *str, int rgb[3]);
void	read_file(char *file, t_rules *rules);
void	get_measures(int fd, int hl[2]);
int		rules_completed(t_rules *rules);
void	take_rules(int fd, t_rules *rules);
void	copy_rule(char *str, char **str2);
void	insert_rule(char *str, t_rules *rules);
void	die(char *str);
void	raycast(t_rules *rules, t_image *view, t_image *minimap);
int		wall_coll(t_rules rules);
int		colliding(t_rules *rules, float ray_cos, float ray_sin, int plus);
void	bresenham(float xy[2], float xy2[2], unsigned int color, t_image *minimap, t_image *view, int x, t_rules *rules, double dir1);
int		get_abs(int n);
void	my_mlx_pixel_put(t_image *image, int x, int y, int color);
double	final_length(float start_x, float start_y, float rxy[2]);
void	draw_view(float xy[2], float xy2[2], t_image *view, int x, t_rules *rules, double dir1);
void	move_player(t_rules *rules, char *dir);
double	our_modulo(double x, double y);

#endif
