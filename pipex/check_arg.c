/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shebaz <shebaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:21:26 by shebaz            #+#    #+#             */
/*   Updated: 2024/04/26 18:20:28 by shebaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void    ft_clean (char **arr1, char **arr2)
{
	free(arr1);
	free(arr2);
}

void    check_cmds(char **arr)
{
    int     i;
    char    cmp;

    i = 0;
    cmp = 39;
    while (arr[i] != NULL)
    {
        if (arr[i][0] == cmp)
            arr[i] = ft_strtrim(arr[i], "'");
        i++;
    }
}

char    **arr(char *cmd)
{
    int     arr_count;
    int     i;
    char    **arr;
    char    **new_arr;

    arr = ft_split(cmd,' ');
    i = 0;
    arr_count = 0;
    check_cmds(arr);
    while (arr[arr_count] != NULL)
        arr_count++;
    new_arr = malloc((arr_count + 2) * sizeof(char *));
    if (new_arr == NULL)
    {
        perror("malloc");
        exit(1);
    }
    while (i < arr_count)
    {
        new_arr[i] = arr[i];
        i++;
    }
    new_arr[arr_count] = NULL;
    return (new_arr);
}

void check_param(char *infile, char *cmd1, char *cmd2, char **envp)
{
	int     count;
	char    **arr1;
	char    **arr2;

	count = 1;
	arr1 = ft_split(cmd1,' ');
	arr2 = ft_split(cmd2,' ');
	check_cmds(arr1);
	check_cmds(arr2);
	if (access(infile,F_OK) != 0)
	{
		ft_printf("zsh: no such file or directory: %s\n",infile);
		count = 0;
	}
	if (get_executable(arr2[0],find_path(envp)) == NULL)
	{
		ft_printf("zsh: command not found: %s\n", arr2[0]);
		if (count == 0)
		{
			ft_clean(arr1,arr2);        
			exit(0);
		}
	}
	if (get_executable(arr1[0],find_path(envp)) == NULL)
		ft_printf("zsh: command not found: %s\n", arr1[0]);
	ft_clean(arr1,arr2);
}

