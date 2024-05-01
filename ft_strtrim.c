/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shebaz <shebaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 21:10:09 by shebaz            #+#    #+#             */
/*   Updated: 2024/04/30 21:11:19 by shebaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	check(char *set, char s)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == s)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char *s1, char *set)
{
	int	start;
	int	end;
	int		i;
	char	*trimmed;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	end = ft_strlen(s1);
	start = 0;
	while (check(set, s1[start]))
		start++;
	while (end > start && check(set, s1[end - 1]))
		end--;
	trimmed = (char *)malloc(((end - start) + 1) * sizeof(char));
	if (!trimmed)
		return (NULL);
	while (start < end)
	{
		trimmed[i] = s1[start];
		i++;
		start++;
	}
	trimmed[i] = '\0';
	return (trimmed);
}
