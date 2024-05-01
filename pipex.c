/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shebaz <shebaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 15:12:24 by shebaz            #+#    #+#             */
/*   Updated: 2024/05/01 10:31:01 by shebaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char *get_full_path(char **envp)
{
	int	i;
	
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i]);
		i++;
	}
	return (NULL);
}

char *get_path(char *argv,char **envp)
{
	int		i;
	char	*full_path;
	char	**arr;
	char	*command_path;
	char	**path_arr;
	char	*cmd;

	full_path = get_full_path(envp);
	arr = ft_split(argv,' ');
	cmd = arr[0];
	i = 0;
	path_arr = ft_split(full_path, ':');
	while (path_arr[i])
	{
		command_path = ft_strjoin(path_arr[i], "/", cmd);
		if (access(command_path , X_OK) == 0)
			return (path_arr[i]);
		free(command_path);
		i++;
	}
	return (NULL);
}
int get_executable(char *cmd, char *command_path)
{
	char *full_path;
	
	full_path = ft_strjoin(command_path, "/" , cmd);
	if (access(full_path, X_OK) == 0)
		return (1);
	return (0);
}
void	check_cmd(char **arr)
{
	int	i;
	char c;
	
	i = 0;
	c = 39;
	while(arr[i])
	{
		if(arr[i][0] == c)
			ft_strtrim(arr[i], "'");
		i++;
	}
}
void	check_full_command(char **argv,char **arr1,char **arr2)
{
	char c = 39;
	
	if (argv[2][0] == '/' )
		printf("zsh: no such file or directory: %s\n",arr1[0]);
	else if (argv[2][0] == c)
		printf("zsh: command not found: %s\n", argv[2]);
	if (argv[3][0] == '/')
		printf("zsh: no such file or directory: %s\n",arr2[0]);
	else if (argv[3][0] == c)
		printf("zsh: command not found: %s\n", argv[3]);
}

void check_argument(int argc, char **argv, char **envp)
{
	(void)(argc);
	char **arr1 = ft_split(argv[2], ' ');
	char **arr2 = ft_split(argv[3], ' ');
	check_full_command(argv, arr1, arr2);
	check_cmd(arr1);
	check_cmd(arr2);
	if (access(argv[1], F_OK) != 0)
	{
		printf("zsh: no such file or directory: %s\n",argv[1]);
		if (get_executable(arr2[0], get_path(argv[3],envp)) == 0)
			printf("zsh: command not found: %s\n",arr2[0]);
		printf("check1\n");
		exit(1);
	}
	else
	{
		if (get_executable(arr1[0], get_path(argv[2],envp)) == 0)
		{
			printf("zsh: command not found: %s\n",arr1[0]);			
			exit(1);
		}
		if (get_executable(arr2[0], get_path(argv[3],envp)) == 0)
		{	
			printf("zsh: command not found: %s\n",arr2[0]);
			exit(1);
		}
	}
}


int main(int argc , char **argv, char **envp)
{
    if (argc == 5)
	{
        check_argument(argc, argv, envp);
		execute_commands(argv,envp,get_full_path(envp));
	}
	else
        printf(" five arguments needed\n");
}