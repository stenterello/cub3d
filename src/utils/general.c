/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 14:57:51 by ddelladi          #+#    #+#             */
/*   Updated: 2022/10/07 15:01:36 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	die(char *str)
{
	ft_putendl_fd(str, 2);
	exit(1);
}

static char	*get_path(char *str)
{
	char	*ret;
	int		i;

	i = 0;
	while (str[i] != ' ')
		i++;
	while (str[i] == ' ')
		i++;
	ret = malloc(sizeof(char) * (ft_strlen(&str[i])));
	if (!ret)
		die("Malloc error");
	ft_strlcpy(ret, &str[i], (ft_strlen(&str[i])));
	return (ret);
}

t_image	*get_rule(char *str, t_rules *rules, t_image *chosen)
{
	char	*path;
	t_image	*ret;

	if (chosen)
		die("Double rule definition in .cub file. Aborting");
	path = get_path(str);
	ret = malloc(sizeof(t_image));
	if (!ret)
		die("Malloc error");
	ret->img = mlx_xpm_file_to_image(rules->mlx.mlx, path,
			&ret->width, &ret->height);
	if (!ret->img)
		die("Could not load textures. Aborting");
	ret->addr = mlx_get_data_addr(ret->img, &ret->bpp,
			&ret->line_length, &ret->endian);
	free(path);
	return (ret);
}
