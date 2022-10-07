/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 15:30:19 by ddelladi          #+#    #+#             */
/*   Updated: 2022/10/07 15:01:36 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_window(t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		die("Error initializing Minilibx. Aborting");
	mlx->mlx_win = mlx_new_window(mlx->mlx,
			mlx->win_width, mlx->win_height, "Cub3d");
}

void	easy_pxl(t_image *image, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0)
		return ;
	dst = image->addr + (y * image->line_length + x * (image->bpp / 8));
	*(unsigned int *)dst = color;
	return ;
}

void	init_xpm_img(t_rules *rules, t_image **img, char *path)
{
	(*img) = malloc(sizeof(t_image));
	if (!(*img))
		die("Malloc error");
	(*img)->img = mlx_xpm_file_to_image(rules->mlx.mlx, path,
			&(*img)->width, &(*img)->height);
	if (!(*img)->img)
		die("Error initializing image");
	(*img)->addr = mlx_get_data_addr((*img)->img, &(*img)->bpp,
			&(*img)->line_length, &(*img)->endian);
}

void	init_img(t_rules *rules, t_image *img, int w, int h)
{
	img->img = mlx_new_image(rules->mlx.mlx, w, h);
	if (!img->img)
		die("Error initializing image");
	img->addr = mlx_get_data_addr(img->img, &img->bpp,
			&img->line_length, &img->endian);
}
