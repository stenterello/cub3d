/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 00:22:27 by ddelladi          #+#    #+#             */
/*   Updated: 2022/07/21 13:55:59 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	take_encoded_xpm(t_texture *texture, int fd)
{
	char	*tmp;
	int		i;

	texture->encoded = malloc(sizeof(char *) * (texture->size[0] + 1));
	if (!texture->encoded)
		die("Malloc error");
	tmp = get_next_line(fd);
	free(tmp);
	tmp = get_next_line(fd);
	i = 0;
	while (i < texture->size[1])
	{
		texture->encoded[i] = malloc(sizeof(char) * (texture->size[1] + 1));
		if (!texture->encoded[i])
			die("Malloc error");
		ft_strlcpy(texture->encoded[i++], &tmp[1], texture->size[1] + 1);
		free(tmp);
		tmp = get_next_line(fd);
	}
	texture->encoded[i] = NULL;
	free(tmp);
}

void	take_key(char *dst, char *src, int k, int j)
{
	int	i;

	i = 1;
	printf("k -> %d\n", k);
	printf("j -> %d\n", j);
	dst[0] = src[i++];
	dst[1] = src[i];
}

void	read_pairs(t_texture *texture, int fd)
{
	char	*tmp;
	int		j;
	t_xpm	*ptr;

	
	j = 0;
	texture->pairs = malloc(sizeof(t_xpm));
	if (!texture->pairs)
		die("Malloc error");
	ptr = texture->pairs;
	while (j++ < texture->n_colors)
	{
		if (j > 1)
		{
			ptr->next = malloc(sizeof(t_xpm));
			ptr = ptr->next;
			if (!ptr)
				die("Malloc error");
		}
		tmp = get_next_line(fd);
		ptr->key = malloc(sizeof(char) * 3);
		if (!ptr->key)
			die("Malloc error");
		ft_strlcpy(ptr->key, &tmp[1], 3);
		ptr->value = malloc(sizeof(char) * 7);
		if (!ptr->value)
			die("Malloc error");
		ft_strlcpy(ptr->value, &tmp[6], 7);
		free(tmp);
	}
	ptr->next = NULL;
	take_encoded_xpm(texture, fd);
}

void	take_size(char *tmp, t_texture *texture)
{
	int	i;

	i = 1;
	texture->size[0] = 0;
	texture->size[1] = 0;
	texture->size[0] = ft_atoi(&tmp[i]);
	while (ft_isdigit(tmp[i]))
		i++;
	while (tmp[i] == 32)
		i++;
	texture->size[1] = ft_atoi(&tmp[i]);
	while (ft_isdigit(tmp[i]))
		i++;
	while (tmp[i] == 32)
		i++;
	texture->n_colors = ft_atoi(&tmp[i]);
	if (!texture->size[0] || !texture->size[1] || !texture->n_colors)
		die("Empty texture or no colors at all!");
}

void	define_texture(char *path, t_texture *texture)
{
	int		fd;
	int		i;
	char	*tmp;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		die("Error while opening texture");
	i = 0;
	while (i++ < 3)
	{
		tmp = get_next_line(fd);
		printf("%s", tmp);
		free(tmp);
	}
	tmp = get_next_line(fd);
	texture->size[0] = 0;
	texture->size[1] = 0;
	texture->n_colors = 0;
	texture->last_x = 0;
	take_size(tmp, texture);
	free(tmp);
	read_pairs(texture, fd);
	close(fd);
}
