/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CUB3D_engine.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 11:35:18 by ddelladi          #+#    #+#             */
/*   Updated: 2022/10/07 14:58:27 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_ENGINE_H
# define CUB3D_ENGINE_H

typedef struct s_ray
{
	double		angle;
	float		x;
	float		y;
	float		xyoff[2];
}				t_ray;

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

typedef struct s_player
{
	float	x;
	float	y;
	double	d_x;
	double	d_y;
	double	dir;
	float	speed;
}				t_player;

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

typedef struct s_rules
{
	t_map			map;
	t_mlx			mlx;
	t_player		player;
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
}				t_rules;

typedef struct s_bres_data
{
	float			xy[2];
	float			xy2[2];
	unsigned int	color;
	int				x;
	double			ray_angle;
}				t_bres_data;

typedef struct s_bres_info
{
	int				swap;
	double			ab[2];
	double			d;
	int				sq[2];
	int				axy[2];
	unsigned int	color;
}				t_bres_info;

void			bresenham(t_bres_data *d, t_image *min, t_image *view,
					t_rules *rules);
void			move_player(t_rules *rules, char *dir);
void			add_events(t_rules *rules);
int				loop_events(t_rules *rules);
void			minimap2d(t_rules *rules, t_image *minimap);
void			raycast(t_rules *rules, t_image *view, t_image *minimap);
int				virtual_horizontal_colliding(int ray_x, int ray_y,
					t_rules *rules, int dir);
int				virtual_vertical_colliding(int ray_x, int ray_y,
					t_rules *rules, int dir);
int				press(int keycode, t_rules *rules);
int				release(int keycode, t_rules *rules);
void			draw_view(t_bres_data *d, t_image *view,
					t_rules *rules, t_image *tex);
int				colliding(t_rules *rules, float ray_cos,
					float ray_sin, int plus);
void			calc_ray(t_bres_data *data, t_rules *rules,
					t_image *view, t_image *minimap);
int				define_hor_ray_and_offset(t_rules *rules, t_ray *ray,
					double a_tan, float xy[2]);
int				define_ver_ray_and_offset(t_rules *rules, t_ray *ray,
					double n_tan, float xy[2]);
void			game(t_rules *rules);

#endif
