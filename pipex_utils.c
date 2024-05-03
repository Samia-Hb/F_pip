/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shebaz <shebaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 01:23:19 by shebaz            #+#    #+#             */
/*   Updated: 2024/05/03 15:59:00 by shebaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strcat(char *dest, char *src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (dest[i])
		i++;
	while (src[j])
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
}


// char *get_executable(char *command, char *path)
// {
//     int  i;
//     char *full_path;
//     char **dir;

//     i = 0;
//     dir = ft_split(path,':');
    
//     while (dir[i])
//     {
//         full_path = malloc(strlen(dir[i]) + strlen(command) + 2);
//         if(full_path == NULL)
//         {
//             perror("malloc");
//         	exit(1);
//         }
//         strcpy(full_path, dir[i]);
//         strcat(full_path, "/");
//         strcat(full_path, command);
//         if (access(full_path, X_OK) == 0)
//             break;
//         free(full_path);
//         i++;
//     }
//     //free(dir);
//     if(dir[i])
//         return (full_path);
//     return (NULL);
// }



