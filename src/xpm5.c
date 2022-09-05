/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm5.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gimartin <gimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 11:22:34 by gimartin          #+#    #+#             */
/*   Updated: 2022/09/05 11:27:30 by gimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	copy_get_couples(char *tmp, t_couples *act)
{
	if (tmp && ft_strncmp("/* pixels */", tmp, 12))
	{
		act->next = malloc(sizeof(t_couples));
		if (!act->next)
			die("Malloc error");
		act = act->next;
		act->next = NULL;
	}
}

void	get_couples(int fd, t_xpm *ret)
{
	t_couples	*act;
	char		*tmp;
	int			i;

	act = &ret->couples;
	act->next = NULL;
	tmp = get_next_line(fd);
	while (tmp && ft_strncmp("/* pixels */", tmp, 12))
	{
		act->key = malloc(sizeof(char) * (ret->char_n + 1));
		if (!act->key)
			die("Malloc error");
		ft_strlcpy(act->key, &tmp[1], ret->char_n + 1);
		i = ret->char_n + 1;
		i = to_color(i, tmp);
		act->value = get_hex_color(&tmp[i]);
		free(tmp);
		tmp = get_next_line(fd);
		copy_get_couples(tmp, act);
	}
	if (tmp)
		free(tmp);
}

void	get_encoded(int fd, t_xpm *ret)
{
	int		i;
	char	*tmp;

	ret->encoded = malloc(sizeof(char *) * (ret->size[0] + 1));
	if (!ret->encoded)
		die("Malloc error");
	i = 0;
	tmp = get_next_line(fd);
	while (tmp && i < ret->size[0])
	{
		ret->encoded[i] = malloc(sizeof(char) * (ret->size[0]
					* ret->char_n + 1));
		if (!ret->encoded[i])
			die("Malloc error");
		ft_strlcpy(ret->encoded[i], &tmp[1], ft_strlen(tmp) - 3);
		printf("%s\n", ret->encoded[i++]);
		free(tmp);
		tmp = get_next_line(fd);
	}
	if (tmp)
		free(tmp);
	ret->encoded[i] = NULL;
}

t_xpm	get_texture(t_rules *rules)
{
	int		fd;
	t_xpm	ret;

	fd = open(rules->north_path, O_RDONLY);
	if (fd < 0)
		die("Can't read texture file. Aborting");
	get_size_and_colors(fd, &ret);
	get_couples(fd, &ret);
	get_encoded(fd, &ret);
	close(fd);
	return (ret);
}
