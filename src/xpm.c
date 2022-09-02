/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 12:40:31 by ddelladi          #+#    #+#             */
/*   Updated: 2022/09/02 12:41:04 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_n_colors_and_size(char *s, int size[2])
{
	int	ret;
	int	i;
	int	i2;

	i = 0;
	i2 = 1;
	while (i < 2)
	{
		size[i++] = ft_atoi(&s[i2]);
		while (s[i2] != ' ')
			i2++;
		i2++;
	}
	ret = ft_atoi(&s[i2]);
	return (ret);
}

char	*take_key(char *s)
{
	int		i;
	int		i2;
	char	*ret;

	i = 1;
	i2 = 0;
	ret = malloc(sizeof(char) * 3);
	if (!ret)
		die("Malloc error");
	while (s[i] != 'c' && i < 3)
		ret[i2++] = s[i++];
	ret[i2] = '\0';
	return (ret);
}

int	get_nbr_hex(char *str)
{
	int	i;
	int	ret;
	int	n;
	int	n_len;

	if (!ft_strncmp("ffffff", str, 6))
		return (16777215);
	n_len = ft_strlen(str) - 1;
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

int	take_value(char *s)
{
	int		i;
	int		i2;
	char	*ter;

	i = 3;
	i2 = 0;
	ter = malloc(sizeof(char) * 7);
	if (!ter)
		die("Malloc error");
	while (s[i] && s[i] != '#')
		i++;
	i++;
	while (s[i] && s[i] != '"')
		ter[i2++] = s[i++];
	ter[i2] = '\0';
	return (get_nbr_hex(ter));
}

t_couples	take_rgb_couples(int fd)
{
	char		*tmp;
	t_couples	ret;
	t_couples	*act;

	act = &ret;
	tmp = get_next_line(fd);
	while (tmp && ft_strncmp("/* pixels */", tmp, 12))
	{
		act->key = take_key(tmp);
		act->value = take_value(tmp);
		act->next = NULL;
		free(tmp);
		tmp = get_next_line(fd);
		if (tmp && ft_strncmp("/* pixels */", tmp, 12))
		{
			act->next = malloc(sizeof(t_couples));
			if (!act->next)
				die("Malloc error");
			act = act->next;
		}
	}
	if (tmp)
		free(tmp);
	return (ret);
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

t_xpm	load_player(void)
{
	int		fd;
	char	*tmp;
	int		i;
	int		n_colors;
	t_xpm	xpm;

	fd = open("img/fps_player.xpm", O_RDONLY);
	if (fd < 0)
		printf("Error: missing fps_player.xpm file!\n");
	i = 0;
	while (i++ < 3)
	{
		tmp = get_next_line(fd);
		free(tmp);
	}
	tmp = get_next_line(fd);
	n_colors = get_n_colors_and_size(tmp, xpm.size);
	if (n_colors > 70)
		printf("Texture with too many colors... It could go slower\n");
	free(tmp);
	xpm.couples = take_rgb_couples(fd);
	xpm.encoded = take_encoded_xpm(fd, xpm.size);
	close(fd);
	return (xpm);
}

t_couples	*get_pair(char *encoded, t_xpm xpm)
{
	t_couples	*act;

	act = &xpm.couples;
	while (act)
	{
		if (act->key[1] == ' ' && !ft_strncmp(act->key, encoded, 1))
			return (act);
		else if (!ft_strncmp(act->key, encoded, 2))
			return (act);
		act = act->next;
	}
	return (NULL);
}

int	get_xpm_color(char *encoded, t_xpm xpm)
{
	t_couples		*match;

	match = get_pair(encoded, xpm);
	if (!match)
		return (200);
	if (match->value == 0)
		return (100);
	return ((int)match->value);
}

void	draw_player(t_xpm xpm, t_rules *rules)
{
	t_image	*pl;
	int		start_x;
	int		start_y;
	int		end_x;
	int		end_y;
	int		b_y;

	pl = mlx_new_image(rules->mlx.mlx, xpm.size[0], xpm.size[1]);
	pl->addr = mlx_get_data_addr(&rules->mlx, &pl->bpp, &pl->line_length, &pl->endian);
	start_x = rules->mlx.win_width / 2 - (xpm.size[0] / 2);
	end_x = rules->mlx.win_width / 2 + (xpm.size[0] / 2);
	start_y = rules->mlx.win_height - xpm.size[1];
	end_y = rules->mlx.win_height;
	b_y = start_y;
	while (start_x < end_x)
	{
		start_y = b_y;
		while (start_y < end_y)
		{
			if (get_xpm_color(&xpm.encoded[start_y % xpm.size[1]][start_x % xpm.size[0]], xpm) != -1)
			{
						my_mlx_pixel_put(pl, start_x, start_y, get_xpm_color(&xpm.encoded[start_y % xpm.size[1]][start_x % xpm.size[0]], xpm));
						printf("%x\n", get_xpm_color(&xpm.encoded[start_y % xpm.size[1]][start_x % xpm.size[0]], xpm));
			}
			start_y++;
		}
		start_x++;
	}
	mlx_put_image_to_window(rules->mlx.mlx, rules->mlx.mlx_win, pl, rules->mlx.win_width / 2, rules->mlx.win_height / 2);
}