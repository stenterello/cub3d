/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 13:07:44 by ddelladi          #+#    #+#             */
/*   Updated: 2022/07/26 13:10:35 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	define_player_dir(t_rules *rules, int c)
{
	if (c == 'N')
		rules->player.dir = PI / 2;
	else if (c == 'S')
		rules->player.dir = 3 * PI / 2;
	else if (c == 'E')
		rules->player.dir = 0;
	else
		rules->player.dir = PI;
}

void	define_player(char *tmp, t_rules *rules, int y)
{
	int	i;

	i = -1;
	while (tmp[++i])
	{
		if (ft_strchr("NSEW", tmp[i]) != NULL)
			break ;
	}
	define_player_dir(rules, tmp[i]);
	tmp[i] = '0';
	rules->player.x = i * (rules->map.block) + rules->map.block / 2;
	rules->player.y = y * (rules->map.block) + rules->map.block / 2;
	rules->player.d_x = cos(rules->player.dir) * 5;
	if (rules->player.dir == (double)PI)
		rules->player.d_y = 0;
	else
		rules->player.d_y = -sin(rules->player.dir) * 5;
	rules->player.miniplayer.x = rules->map.mini_block
		* rules->player.x / rules->map.block;
	rules->player.miniplayer.y = rules->map.mini_block
		* rules->player.y / rules->map.block;
	rules->player.speed = rules->map.block / 10;
}

void	define_map(int fd, t_rules *rules)
{
	char	*tmp;
	int		i;

	tmp = get_next_line(fd);
	i = 1;
	while (tmp)
	{
		rules->map.map[i] = malloc(sizeof(char) * ft_strlen(tmp) + 1);
		if (!rules->map.map[i])
			die("Malloc error");
		check_player(tmp, rules, i);
		ft_strlcpy(rules->map.map[i++], tmp, ft_strlen(tmp) + 1);
		free(tmp);
		tmp = get_next_line(fd);
	}
	if (tmp)
	{
		free(tmp);
		tmp = NULL;
	}
	rules->map.map[i] = NULL;
}

void	define_ceiling(t_rules *rules)
{
	int	i;

	i = -1;
	rules->map.ceiling = malloc(sizeof(char *) * (rules->map.map_height + 1));
	if (!rules->map.ceiling)
		die("Malloc error");
	while (++i < rules->map.map_width)
	{
		rules->map.ceiling[i] = malloc(sizeof(char)
				* (rules->map.map_width + 1));
		if (!rules->map.ceiling[i])
			die("Malloc error");
		ft_memset(rules->map.ceiling[i], '0', rules->map.map_width);
	}
}

void	define_floor(t_rules *rules)
{
	int	i;

	i = -1;
	rules->map.floor = malloc(sizeof(char *) * (rules->map.map_height + 1));
	if (!rules->map.floor)
		die("Malloc error");
	while (++i < rules->map.map_width)
	{
		rules->map.floor[i] = malloc(sizeof(char) * (rules->map.map_width + 1));
		if (!rules->map.floor[i])
			die("Malloc error");
		ft_memset(rules->map.floor[i], '0', rules->map.map_width);
	}
}

void	define_textures(t_rules *rules)
{
	int	i;

	i = -1;
	while (++i < 4)
		define_texture(rules->paths[i], &rules->textures[i]);
}
