/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 16:57:44 by ddelladi          #+#    #+#             */
/*   Updated: 2022/09/02 01:08:59 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned int choose_color(char c)
{
	if (c == '0')
		return (0x0000FF00);
	else if (c == '1')
		return (0x00FF0000);
	else if (c == ' ')
		return (0x00000000);
	else
		return (0x00000000);
}

void my_mlx_pixel_put(t_image *image, int x, int y, int color)
{
	char *dst;

	dst = image->addr + (y * image->line_length + x * (image->bpp / 8));
	*(unsigned int *)dst = color;
}

void draw_mini_block(t_rules *rules, int i, int j, t_image *image)
{
	unsigned int color;
	int start_end_x[2];
	int start_end_y[2];
	int back;

	color = choose_color(rules->map.map[i][j]);
	start_end_x[0] = j * rules->map.mini_block_width;
	start_end_x[1] = start_end_x[0] + rules->map.mini_block_width;
	start_end_y[0] = i * rules->map.mini_block_width;
	start_end_y[1] = start_end_y[0] + rules->map.mini_block_width;
	back = start_end_x[0];
	while (start_end_y[0] <= start_end_y[1])
	{
		start_end_x[0] = back;
		while (start_end_x[0] <= start_end_x[1])
			my_mlx_pixel_put(image, start_end_x[0]++, start_end_y[0], color);
		start_end_y[0]++;
	}
}

void draw_mini_player(t_rules *rules, t_image *image)
{
	float start_x;
	float start_y;
	float end_x;
	float end_y;

	start_x = (rules->player.x / 4) - (rules->map.mini_block_width / 10);
	start_y = (rules->player.y / 4) - (rules->map.mini_block_width / 10);
	end_x = (rules->player.x / 4) + (rules->map.mini_block_width / 10);
	end_y = (rules->player.y / 4) + (rules->map.mini_block_width / 10);
	while (start_y < end_y)
	{
		start_x = (rules->player.x / 4) - (rules->map.mini_block_width / 10);
		while (start_x < end_x)
			my_mlx_pixel_put(image, start_x++, start_y, 0x000000FF);
		start_y++;
	}
}

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

void minimap(t_rules *rules)
{
	int i;
	int j;
	t_image view;
	t_image minimap;

	view.img = mlx_new_image(rules->mlx.mlx, rules->mlx.win_width, rules->mlx.win_height);
	view.addr = mlx_get_data_addr(view.img, &view.bpp, &view.line_length,
								   &view.endian);
	minimap.img = mlx_new_image(rules->mlx.mlx, rules->map.map_height_len[0] * rules->map.mini_block_width, rules->map.map_height_len[1] * rules->map.mini_block_width);
	minimap.addr = mlx_get_data_addr(minimap.img, &minimap.bpp, &minimap.line_length,
									 &minimap.endian);
	i = -1;
	while (++i < rules->map.map_height_len[1])
	{
		j = -1;
		while (++j < rules->map.map_height_len[0])
			draw_mini_block(rules, i, j, &minimap);
	}
	draw_mini_player(rules, &minimap);
	raycast(rules, &view, &minimap);
	// mlx_put_image_to_window(rules->mlx.mlx, rules->mlx.mlx_win,
	// image.img, 0, 0);
	mlx_put_image_to_window(rules->mlx.mlx, rules->mlx.mlx_win, view.img, 0, 0);
	mlx_put_image_to_window(rules->mlx.mlx, rules->mlx.mlx_win,
							minimap.img, 0, 0);
	rules->player.img = load_player();
	draw_player(rules->player.img, rules);
}
