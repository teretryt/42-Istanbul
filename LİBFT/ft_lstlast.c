/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturker <rturker@42istanbul.com.tr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 18:17:33 by rturker           #+#    #+#             */
/*   Updated: 2022/10/07 18:26:42 by rturker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list *ft_lstlast(t_list *lst)
{
	int	i;
	t_list *current;

	if (!lst)
		return NULL;
	current = lst->next;
	i = 0;
	while (current->next != NULL)
	{
		current = current->next;
	}
	return (current);
}
