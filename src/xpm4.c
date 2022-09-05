/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm4.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 10:55:47 by gimartin          #+#    #+#             */
/*   Updated: 2022/09/05 21:16:49 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int	get_xpm_color2(char *encoded, t_xpm xpm)
{
	t_couples		*match;

	match = get_pair(encoded, xpm);
	if (!match)
		return (200);
	if (match->value == 0)
		return (100);
	return ((int)match->value);
}

void	copy_draw_player(int s_e[4], int b_y, t_xpm xpm, t_image *pl)
{
	while (s_e[0] < s_e[2])
	{
		s_e[1] = b_y;
		while (s_e[1] < s_e[3])
		{
			if (get_xpm_color2(&xpm.encoded[s_e[1] % xpm.size[1]][s_e[0]
					% xpm.size[0]], xpm) != -1)
			{
				easy_pxl(pl, s_e[0], s_e[1], get_xpm_color2(&xpm.encoded[s_e[1]
						% xpm.size[1]][s_e[0] % xpm.size[0]], xpm));
				printf("%x\n", get_xpm_color2(&xpm.encoded[s_e[1]
						% xpm.size[1]][s_e[0] % xpm.size[0]], xpm));
			}
			s_e[1]++;
		}
		s_e[0]++;
	}
}

void	draw_player(t_xpm xpm, t_rules *rules)
{
	t_image	*pl;
	int		s_e[4];
	int		b_y;

	pl->img = mlx_new_image(rules->mlx.mlx, xpm.size[0], xpm.size[1]);
	pl->addr = mlx_get_data_addr(&rules->mlx, &pl->bpp, &pl->line_length,
			&pl->endian);
	s_e[0] = rules->mlx.win_width / 2 - (xpm.size[0] / 2);
	s_e[2] = rules->mlx.win_width / 2 + (xpm.size[0] / 2);
	s_e[1] = rules->mlx.win_height - xpm.size[1];
	s_e[3] = rules->mlx.win_height;
	b_y = s_e[1];
	copy_draw_player(s_e, b_y, xpm, pl);
	mlx_put_image_to_window(rules->mlx.mlx, rules->mlx.mlx_win, pl,
		rules->mlx.win_width / 2, rules->mlx.win_height / 2);
}
