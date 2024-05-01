/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shebaz <shebaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:29:39 by shebaz            #+#    #+#             */
/*   Updated: 2024/04/26 17:29:26 by shebaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_path(char **envp)
{
	char	*path_env;
	int		i;

	path_env = NULL;
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path_env = envp[i] + 5;
			break ;
		}
		i++;
	}
	return (path_env);
}


int main(int argc, char **argv,char **envp)
{
	if (argc == 5)
	{
		check_param(argv[1], argv[2], argv[3], envp);
		execute_commands(argv[2], argv[3], argv[1], argv[4], envp);
	}
	else
		ft_printf("Usage:  <infile> <cmd1> <cmd2> <outfile>\n");
	return 0;
}
//=>"Redirect the standard output to the writing end of the pipe" means that the standard output of a process is set to write its output into the writing end of a pipe (pipefd[1])