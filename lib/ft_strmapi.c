/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shebaz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 21:18:38 by shebaz            #+#    #+#             */
/*   Updated: 2023/11/20 10:11:25 by shebaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	int		j;
	char	*string;

	i = 0;
	j = 0;
	if (s == NULL || f == NULL)
		return (NULL);
	while (s[i])
		i++;
	string = (char *)malloc((i + 1) * sizeof(char));
	if (!string)
		return (NULL);
	while (j < i)
	{
		string[j] = f(j, s[j]);
		j++;
	}
	string[j] = '\0';
	return (string);
}
