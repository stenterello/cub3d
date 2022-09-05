/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gimartin <gimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 18:26:00 by ddelladi          #+#    #+#             */
/*   Updated: 2022/09/05 11:54:51 by gimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	next_num(int i, char *s)
{
	while (s[i] != ' ')
		i++;
	return (++i);
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

int	copy_get_hex_color(char *str, int i, int ret, int n_len)
{
	int	n;

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

unsigned int	get_hex_color(char *str)
{
	int		i;
	int		ret;
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
	ret = copy_get_hex_color(str, i, ret, n_len);
	return (ret);
}
