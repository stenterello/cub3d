/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 12:29:02 by ddelladi          #+#    #+#             */
/*   Updated: 2022/06/22 14:37:56 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *next)
{
	t_list	*tmp;

	if (!next)
		return ;
	if (!*lst)
		*lst = next;
	else
	{
		tmp = ft_lstlast(*lst);
		tmp->next = next;
	}
}
