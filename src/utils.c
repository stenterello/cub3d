/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 02:52:07 by ddelladi          #+#    #+#             */
/*   Updated: 2022/07/25 22:40:05 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

int	get_hex_color(int rgb[3])
{
	int	ret;

	ret = 0;
	ret = (int)rgb[0] * 256 * 256 + rgb[1] * 256 + rgb[2];
	return (ret);
}

int	get_nbr_hex(char *str)
{
	int	base_len;
	int	i;
	int	ret;
	int	n;
	int	n_len;

	if (!ft_strncmp("ffffff", str, 6))
		return (16777215);
	base_len = 16;
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
		ret += (n * pow(base_len, n_len--));
		i++;
	}
	return (ret);
}
