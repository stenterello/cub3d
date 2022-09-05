/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 18:26:00 by ddelladi          #+#    #+#             */
/*   Updated: 2022/09/02 22:12:01 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	next_num(int i, char *s)
{
	while (s[i] != ' ')
		i++;
	return (++i);
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

int	to_color(int i, char *tmp)
{
	while (tmp && tmp[i] != 'c')
		i++;
	i += 3;
	return (i);
}

int	ft_hexlen(char *str)
{
	int	i;

	i = 0;
	while (ft_isdigit(str[i]) || ft_strchr("ABCDEF", str[i]))
		i++;
	return (i);
}

unsigned int	get_hex_color(char *str)
{
	int		i;
	int		ret;
	int		n;
	int		n_len;
	char	base[16];

	ft_strlcpy(base, "0123456789ABCDEF", 16);
	base[15] = 'F';
	if (!ft_strncmp("ffffff", str, 6) || !ft_strncmp("FFFFFF", str, 6))
		return (16777215);
	n_len = ft_hexlen(str) - 1;
	if (!str)
		return (0x0);
	i = 0;
	ret = 0;
	while (str[i])
	{
		if (str[i] >= 48 && str[i] <= 57)
			n = str[i] - 48;
		else if (ft_isalpha(str[i]))
			n = ft_toupper(str[i] - 55);
		else
			break ;
		ret += (n * pow(16, n_len--));
		i++;
	}
	return (ret);
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
		if (tmp && ft_strncmp("/* pixels */", tmp, 12))
		{
			act->next = malloc(sizeof(t_couples));
			if (!act->next)
				die("Malloc error");
			act = act->next;
			act->next = NULL;
		}
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
		ret->encoded[i] = malloc(sizeof(char) * (ret->size[0] * ret->char_n + 1));
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
