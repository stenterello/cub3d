#include "cub3D.h"

static int	ft_fl_c(t_tex *tex, t_pt_d *floor, t_pt_d floor_step)
{
	int		color;
	t_pt	cell;
	t_pt	t;

	cell = ft_point((int)floor->x, (int)floor->y);
	t.x = (int)(tex->w * (floor->x - cell.x)) & (tex->w - 1);
	t.y = (int)(tex->h * (floor->y - cell.y)) & (tex->h - 1);
	floor->x += floor_step.x;
	floor->y += floor_step.y;
	color = ft_get_tex_color(t, tex);
	return (color);
}

static void	ft_floor_ycast(t_hold *hold, t_tex *tex, t_pt_d r1, t_pt_d r2)
{
	int		i;
	int		j;
	float	row_dis;
	t_pt_d	floor;
	t_pt_d	floor_step;

	i = WIN_HEIGHT / 2 + 1;
	while (i < WIN_HEIGHT)
	{
		row_dis = (float)(0.5 * WIN_HEIGHT) / (int)(i - WIN_HEIGHT / 2);
		floor_step.x = row_dis * (r2.x - r1.x) / WIN_WIDTH;
		floor_step.y = row_dis * (r2.y - r1.y) / WIN_WIDTH;
		floor.x = hold->pl_w.x + row_dis * r1.x;
		floor.y = hold->pl_w.y + row_dis * r1.y;
		j = 0;
		while (j < WIN_WIDTH)
		{
			ft_mlx_pixel_put(hold->img, j, i, ft_fl_c(tex, &floor, floor_step));
			++j;
		}
		++i;
	}
}

void	ft_floor_cast(t_hold *hold, t_tex *tex)
{
	t_pt_d	ray_dir1;
	t_pt_d	ray_dir2;

	ray_dir1.x = cos(hold->pos_a) - cos(hold->pos_a + M_PI_2) * FOV_R;
	ray_dir1.y = sin(hold->pos_a) - sin(hold->pos_a + M_PI_2) * FOV_R;
	ray_dir2.x = cos(hold->pos_a) + cos(hold->pos_a + M_PI_2) * FOV_R;
	ray_dir2.y = sin(hold->pos_a) + sin(hold->pos_a + M_PI_2) * FOV_R;
	ft_floor_ycast(hold, tex, ray_dir1, ray_dir2);
}