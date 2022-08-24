/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 13:07:44 by ddelladi          #+#    #+#             */
/*   Updated: 2022/07/26 19:21:13 by ddelladi         ###   ########.fr       */
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

static void	define_bg(t_rules *rules, char ***dst)
{
	int	i;

	i = -1;
	*dst = malloc(sizeof(char *) * (rules->map.map_height + 1));
	if (!*dst)
		die("Malloc error");
	while (++i < rules->map.map_width)
	{
		(*dst)[i] = malloc(sizeof(char) * (rules->map.map_width + 1));
		if (!(*dst)[i])
			die("Malloc error");
		ft_memset((*dst)[i], '0', rules->map.map_width);
	}
}

static void	define_textures(t_rules *rules)
{
	int	i;

	i = -1;
	while (++i < 4)
		define_texture(rules->paths[i], &rules->textures[i]);
}

void	print_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		printf("%s\n", map[i]);
		i++;
	}
}

void	define_map(int fd, t_rules *rules)
{
	char	*tmp;
	int		i;

	tmp = get_next_line(fd);
	i = 1;
	while (tmp)
	{
		rules->map.map[i] = malloc(sizeof(char) * ft_strlen_rl(tmp) + 1);
		if (!rules->map.map[i])
			die("Malloc error");
		check_player(tmp, rules, i);
		ft_strlcpy(rules->map.map[i++], tmp, ft_strlen_rl(tmp) + 1);
		free(tmp);
		tmp = get_next_line(fd);
	}
	if (tmp)
	{
		free(tmp);
		tmp = NULL;
	}
	rules->map.map[i] = NULL;
	define_bg(rules, &rules->map.ceiling);
	define_bg(rules, &rules->map.floor);
	define_textures(rules);
	print_map(rules->map.map);
}
