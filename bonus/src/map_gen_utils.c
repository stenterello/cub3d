/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_gen_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 17:13:13 by ddelladi          #+#    #+#             */
/*   Updated: 2022/07/22 18:59:48 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	count_map_height_and_max_width(int fd, t_rules *rules)
{
	char	*tmp;
	int		count;

	count = 0;
	tmp = get_next_line(fd);
	while (tmp)
	{
		if ((int)ft_strlen(tmp) - 1 > rules->map_width)
			rules->map_width = ft_strlen(tmp) - 1;
		free(tmp);
		count++;
		tmp = get_next_line(fd);
	}
	return (count);
}

int	encode_rgb(u_int8_t alpha, u_int8_t red, u_int8_t green, u_int8_t blue)
{
	return (alpha << 24 | red << 16 | green << 8 | blue);
}

void	define_player(char *tmp, t_rules *rules, int y)
{
	int	i;

	i = 0;
	while (tmp[i])
	{
		if (tmp[i] == 'N')
		{
			rules->player.dir = PI / 2;
			break ;
		}
		if (tmp[i] == 'S')
		{
			rules->player.dir = 3 * PI / 2;
			break ;
		}
		if (tmp[i] == 'E')
		{
			rules->player.dir = 0;
			break ;
		}
		if (tmp[i] == 'W')
		{
			rules->player.dir = PI;
			break ;
		}
		i++;
	}
	tmp[i] = '0';
	rules->player.x = i * (rules->block_width) + rules->block_width / 2;
	rules->player.y = y * (rules->block_width) + rules->block_width / 2;
	rules->player.d_x = cos(rules->player.dir) * 5;
	if (rules->player.dir == (double)PI)
		rules->player.d_y = 0;
	else
		rules->player.d_y = -sin(rules->player.dir) * 5;
	rules->player.miniplayer.x = rules->mini_block_width * rules->player.x / rules->block_width;
	rules->player.miniplayer.y = rules->mini_block_width * rules->player.y / rules->block_width;
	rules->player.speed = rules->block_width / 10;
}

void	check_player(char *tmp, t_rules *rules, int y)
{
	if (ft_strchr(tmp, 'N') != NULL ||
		ft_strchr(tmp, 'S') != NULL ||
		ft_strchr(tmp, 'W') != NULL ||
		ft_strchr(tmp, 'E') != NULL)
		define_player(tmp, rules, y);
	return;
}

void	define_map(int fd, t_rules *rules)
{
	char	*tmp;
	int		i;

	tmp = get_next_line(fd);
	i = 1;
	while (tmp)
	{
		rules->map[i] = malloc(sizeof(char) * ft_strlen(tmp) + 1);
		if (!rules->map[i])
			die("Malloc error");
		check_player(tmp, rules, i);
		ft_strlcpy(rules->map[i++], tmp, ft_strlen(tmp) + 1);
		free(tmp);
		tmp = get_next_line(fd);
	}
	if (tmp)
	{
		free(tmp);
		tmp = NULL;
	}
	rules->map[i] = NULL;
}
