/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shebaz <shebaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:48:12 by shebaz            #+#    #+#             */
/*   Updated: 2024/05/03 15:14:35 by shebaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*check_str(char *s1, char *s2, char *s3)
{
	if (!s1 && s2 && !s3)
		return (ft_strdup(s2));
	if (s1 && !s2 && !s3)
		return (ft_strdup(s1));
	if (!s1 && !s1 && s3)
		return(ft_strdup(s3));
	return (NULL);
}

char	*ft_strjoin(char *s1, char *s2, char *s3)
{
	int		i;
	char	*new;
	int		j;

	i = 0;
	j = 0;
	if (s1 == NULL || s2 == NULL || s3 == NULL)
		return (check_str(s1, s2, s3));
	new = (char *) malloc(ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + 1);
	if (!new)
		return (NULL);
	while (s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		new[i++] = s2[j++];
	}
	j = 0;
	while(s3[j])
		new[i++] = s3[j++];
	new[i] = '\0';
	return (new);
}
