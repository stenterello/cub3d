/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gimartin <gimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 13:28:39 by ddelladi          #+#    #+#             */
/*   Updated: 2022/09/05 11:53:33 by gimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned int	find_color(t_rules *rules, t_xpm *north, int c, int n)
{
	(void)rules;
	(void)north;
	(void)c;
	(void)n;
	return (1);
}

unsigned int	get_xpm_color(t_rules *rules, float dst[2], int y, double line_height, int off)
{
	unsigned int	ret;
	int				color_unit_x;
	// CAMBIARE GLI IF DI MODO CHE SCELGA LA TEXTURE CORRETTA
	if (!our_modulo(dst[0], rules->map.block_width) && (rules->player.dir < M_PI / 2 || rules->player.dir > 3 * M_PI / 2))
	{
		color_unit_x = rules->north.size[0] * round(((int)dst[1]
				% (int)rules->map.block_width)) / (int)rules->map.block_width;
		ret = find_color(rules, &rules->north, color_unit_x, (y - off) * rules->north.size[0] / line_height);
	}
	else if (!our_modulo(dst[0], rules->map.block_width) && rules->player.dir > M_PI / 2 && rules->player.dir < 3 * M_PI / 2)
	{
		color_unit_x = rules->north.size[0] * round(((int)dst[1]
				% (int)rules->map.block_width)) / (int)rules->map.block_width;
		ret = find_color(rules, &rules->north, color_unit_x, (y - off) * rules->north.size[0] / line_height);
	}
	else if (!our_modulo(dst[1], rules->map.block_width) && rules->player.dir > M_PI / 2 && rules->player.dir < 3 * M_PI / 2)
	{
		color_unit_x = rules->north.size[0] * round(((int)dst[0]
				% (int)rules->map.block_width)) / (int)rules->map.block_width;
		ret = find_color(rules, &rules->north, color_unit_x, (y - off) * rules->north.size[0] / line_height);
	}
	else
	{
		color_unit_x = rules->north.size[0] * round(((int)dst[0]
				% (int)rules->map.block_width)) / (int)rules->map.block_width;
		ret = find_color(rules, &rules->north, color_unit_x, (y - off) * rules->north.size[0] / line_height);
	}
	return (ret);
}

void	print_xpm(t_xpm xpm)
{
	int			i;
	t_couples	*act;

	i = 0;
	printf("\n");
	while (xpm.encoded[i])
		printf("%s\n", xpm.encoded[i++]);
	act = &xpm.couples;
	while (act)
	{
		printf("%s c %d\n", act->key, act->value);
		act = act->next;
	}
	exit(0);
}

char	**take_encoded_xpm(int fd, int size[2])
{
	char	*tmp;
	char	**ret;
	int		i;

	ret = malloc(sizeof(char *) * (size[1] + 1));
	if (!ret)
		die("Malloc error");
	i = 0;
	tmp = get_next_line(fd);
	while (tmp && ft_strncmp("};", tmp, 2))
	{
		ret[i] = malloc(sizeof(char) * (ft_strlen(tmp) - 1));
		if (!ret[i])
			die("Malloc error");
		ft_strlcpy(ret[i++], &tmp[1], ft_strlen(tmp) - 3);
		free(tmp);
		tmp = get_next_line(fd);
	}
	if (tmp)
		free(tmp);
	ret[i] = NULL;
	return (ret);
}

void	get_size_and_colors(int fd, t_xpm *ret)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = get_next_line(fd);
	while (tmp && i++ < 3)
	{
		free(tmp);
		tmp = get_next_line(fd);
	}
	i = 1;
	ret->size[0] = ft_atoi(&tmp[i]);
	i = next_num(i, tmp);
	ret->size[1] = ft_atoi(&tmp[i]);
	if (ret->size[0] != ret->size[1])
		die("Textures must be square. Aborting");
	i = next_num(i, tmp);
	ret->n_colors = ft_atoi(&tmp[i]);
	i = next_num(i, tmp);
	ret->char_n = ft_atoi(&tmp[i]);
	if (tmp)
		free(tmp);
}
