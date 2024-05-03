/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shebaz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 15:09:04 by shebaz            #+#    #+#             */
/*   Updated: 2023/11/21 16:19:51 by shebaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*courant;

	if (lst != NULL && f != NULL)
	{
		courant = lst;
		while (courant != NULL)
		{
			f(courant -> content);
			courant = courant -> next;
		}
	}
}
