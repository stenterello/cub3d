/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 00:22:27 by ddelladi          #+#    #+#             */
/*   Updated: 2022/07/25 22:41:08 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	take_encoded_xpm(t_texture *texture, int fd)
{
	char	*tmp;
	int		i;
	int		j;
	int		k;
	int		l;

	texture->encoded = malloc(sizeof(char **) * (texture->size[0] + 1));
	if (!texture->encoded)
		die("Malloc error");
	tmp = get_next_line(fd);
	free(tmp);
	tmp = get_next_line(fd);
	i = 0;
	while (i < texture->size[0])
	{
		texture->encoded[i] = malloc(sizeof(char *) * (texture->size[1] + 1));
		if (!texture->encoded[i])
			die("Malloc error");
		j = 0;
		k = 2;
		while (j < texture->size[1])
		{
			l = k - 1;
			texture->encoded[i][j] = malloc(sizeof(char) * 3);
			if (ft_strchr(texture->delimiters, tmp[k]) != NULL)
			{
				ft_strlcpy(texture->encoded[i][j++], &tmp[l], 3);
				k += 2;
			}
			else
			{
				ft_strlcpy(texture->encoded[i][j++], &tmp[l], 2);
				k++;
			}
		}
		texture->encoded[i][j] = NULL;
		i++;
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

int	name_len(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '"')
		i++;
	return (i);
}

int	found(char *tmp, char *str)
{
	int		i;
	char	*key;

	i = 0;
	if (tmp[i] == '{')
		return (0);
	while (tmp[i] && tmp[i] != '\"')
		i++;
	if (tmp[i] != '"')
		return (0);
	i++;
	key = malloc(sizeof(char) * (name_len(&tmp[i]) + 1));
	if (!key)
		die("Malloc error");
	ft_strlcpy(key, &tmp[i], name_len(&tmp[i]) + 1);
	if (!ft_strncmp(key, str, ft_strlen(key)))
	{
		free(key);
		return (1);
	}
	free(key);
	return (0);
}

char	*to_lower_str(char *str)
{
	char	*ret;
	int		i;

	ret = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!ret)
		die("Malloc error");
	i = -1;
	while (str[++i])
		ret[i] = ft_tolower(str[i]);
	ret[i] = '\0';
	return (ret);
}

char	*only_color(char *str)
{
	int		i;
	char	*ret;

	i = 0;
	while (str[i] && str[i] != '#')
		i++;
	if (str[i] != '#')
		return (NULL);
	i++;
	ret = malloc(sizeof(char) * 7);
	if (!ret)
		die("Malloc error");
	ft_strlcpy(ret, &str[i], 7);
	return (ret);
}

char	*manual_color(char *str)
{
	char	*ret;
	char	*tmp;
	char	*color;
	int		fd;

	fd = open("utils/css-color-names.json", O_RDONLY);
	if (fd < 0)
		die("Error while opening css-color-names.json");
	color = to_lower_str(str);
	tmp = get_next_line(fd);
	while (tmp && !found(tmp, color))
	{
		free(tmp);
		tmp = NULL;
		tmp = get_next_line(fd);
	}
	if (!tmp)
	{
		free(color);
		return (NULL);
	}
	free(color);
	color = only_color(tmp);
	ret = malloc(sizeof(char) * 7);
	if (!ret)
		die("Malloc error");
	ft_strlcpy(ret, only_color(tmp), 7);
	free(tmp);
	free(color);
	close(fd);
	return (ret);
}

int	gray(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != ' ')
		i++;
	while (str[i] == ' ' || str[i] == 'c')
		i++;
	if (!ft_strncmp("gray", &str[i], 4) && ft_isdigit(str[i + 4]))
		return (1);
	return (0);
}

char	*gray_rgb(int rgb[3], char *tmp)
{
	int		i;
	int		percent;
	char	*ret;
	int		res;

	i = 0;
	while (tmp[i] && tmp[i] != ' ')
		i++;
	while (tmp[i] == ' ' || tmp[i] == 'c')
		i++;
	i += 4;
	percent = ft_atoi(&tmp[i]);
	i = 0;
	while (i < 3)
	{
		rgb[i] = (int)(((float)256 / 100) * percent);
		i++;
	}
	res = encode_rgb(0, rgb[0], rgb[1], rgb[2]);
	ret = ft_itoa(res);
	return (ret);
}

void	adjust_color_names(t_texture *texture, int fd)
{
	char	*tmp;
	t_xpm	*ptr;
	char	*result;
	int		i;

	ptr = texture->pairs;
	i = 0;
	while (i++ < 4)
	{
		tmp = get_next_line(fd);
		free(tmp);
	}
	tmp = get_next_line(fd);
	while (ptr && tmp)
	{
		result = manual_color(ptr->value);
		if (result)
		{
			free(ptr->value);
			ptr->value = malloc(sizeof(char) * 7);
			ft_strlcpy(ptr->value, result, 7);
			free(result);
		}
		ptr = ptr->next;
		free(tmp);
		tmp = NULL;
		tmp = get_next_line(fd);
	}
	if (tmp)
		free(tmp);
}

void	read_pairs(t_texture *texture, int fd, char *path)
{
	char	*tmp;
	int		j;
	t_xpm	*ptr;
	int		i;
	char	*manual;
	int		rgb[3];

	
	j = 0;
	texture->delimiters = malloc(sizeof(char) * (texture->n_colors / 94 + 1));
	if (!texture->delimiters)
		die("Malloc error");
	texture->delimiters[0] = '\0';
	texture->pairs = malloc(sizeof(t_xpm));
	if (!texture->pairs)
		die("Malloc error");
	ptr = texture->pairs;
	while (j++ < texture->n_colors)
	{
		i = 1;
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
		ft_strlcpy(ptr->key, &tmp[i], 3);
		if (ft_strchr(texture->delimiters, tmp[i + 1]) == NULL)
			ft_strlcat(texture->delimiters, &tmp[i + 1], ft_strlen(texture->delimiters) + 2);
		if (tmp[i] == 'c')
			i++;
		while (ft_isascii(tmp[i]) && tmp[i] != 'c')
			i++;
		if (tmp[i] == 'c')
			i++;
		while (tmp[i] == ' ' || tmp[i] == '#')
			i++;
		ptr->value = malloc(sizeof(char) * 7);
		if (!ptr->value)
			die("Malloc error");
		if (tmp[i - 1] == '#')
			ft_strlcpy(ptr->value, &tmp[i], 7);
		else if (!gray(tmp))
		{
			free(ptr->value);
			ptr->value = malloc(sizeof(char) * (name_len(&tmp[i]) + 1));
			if (!ptr->value)
				die("Malloc error");
			ft_strlcpy(ptr->value, &tmp[i], name_len(&tmp[i]) + 1);
		}
		else
		{
			manual = gray_rgb(rgb, tmp);
			if (manual)
			{
				ft_strlcpy(ptr->value, manual, 7);
				free(manual);
			}
		}
		free(tmp);
	}
	ptr->next = NULL;
	take_encoded_xpm(texture, fd);
	close(fd);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		die("Error while opening texture file");
	adjust_color_names(texture, fd);
	close(fd);
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
	if (texture->n_colors > 70)
		printf("One texture exceeds 70 colors: slow running of cub3d is predictable.\n");
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
	//	printf("%s", tmp);
		free(tmp);
	}
	tmp = get_next_line(fd);
	texture->size[0] = 0;
	texture->size[1] = 0;
	texture->n_colors = 0;
	texture->last_x = 0;
	take_size(tmp, texture);
	free(tmp);
	read_pairs(texture, fd, path);
}
