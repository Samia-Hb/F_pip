/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shebaz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:16:31 by shebaz            #+#    #+#             */
/*   Updated: 2023/11/21 12:00:58 by shebaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shebaz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 13:30:07 by shebaz            #+#    #+#             */
/*   Updated: 2023/11/20 15:08:31 by shebaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*courant;
	t_list	*precedent;

	if (!lst || !del || !*lst)
		return ;
	courant = *lst;
	while (courant != NULL)
	{
		del(courant -> content);
		precedent = courant;
		courant = courant -> next;
		free(precedent);
	}
	*lst = NULL;
}
