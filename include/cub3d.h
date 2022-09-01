/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 14:35:18 by gimartin          #+#    #+#             */
/*   Updated: 2022/09/01 17:51:15 by ddelladi         ###   ########.fr       */
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
# define ANGLE_UNIT 0.008727

typedef struct s_player
{
	float	x;
	float	y;
	double	dir;
}				t_player;

typedef struct s_map
{
	char	**map;
	int		map_height_len[2];
	float	block_width;
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

void	map_save(char *file, int fd, t_rules *rules);
void	map_checks(t_rules *rules);
void	init_rules(t_rules *rules);
void	init_window(t_rules *rules);
void	add_events(t_rules *rules);
int		loop_events(t_rules *rules);
int		press(int keycode, t_rules *rules);
int		release(int keycode, t_rules *rules);
void	minimap(t_rules *rules);
int		path_start(char *str);
int		take_rgb(char *str, int rgb[3]);
void	read_file(char *file, t_rules *rules);
void	get_measures(int fd, int hl[2]);
void	print_map(char **map);
int		rules_completed(t_rules *rules);
void	take_rules(int fd, t_rules *rules);
void	copy_rule(char *str, char **str2);
void	insert_rule(char *str, t_rules *rules);
void	die(char *str);
void	raycast(t_rules *rules, t_image *image);
void	bresenham(float xy[2], float xy2[2], unsigned int color, t_image *image);
int		get_abs(int n);
void	my_mlx_pixel_put(t_image *image, int x, int y, int color);

#endif