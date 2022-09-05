/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gimartin <gimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 12:40:31 by ddelladi          #+#    #+#             */
/*   Updated: 2022/09/05 11:05:31 by gimartin         ###   ########.fr       */
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
