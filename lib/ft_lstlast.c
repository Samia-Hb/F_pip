/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shebaz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 22:15:55 by shebaz            #+#    #+#             */
/*   Updated: 2023/11/20 14:15:28 by shebaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*courant;

	if (lst == NULL)
		return (NULL);
	courant = lst;
	while (courant -> next != NULL)
	{
		courant = courant -> next;
	}
	return (courant);
}
