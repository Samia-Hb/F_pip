/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shebaz <shebaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:29:39 by shebaz            #+#    #+#             */
/*   Updated: 2024/05/03 15:58:20 by shebaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// char	*find_path(char **envp)
// {
// 	char	*path_env;
// 	int		i;

// 	path_env = NULL;
// 	i = 0;
// 	while (envp[i])
// 	{
// 		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
// 		{
// 			path_env = envp[i] + 5;
// 			break ;
// 		}
// 		i++;
// 	}
// 	return (path_env);
// }

// void	check_command(char *cmd)
// {
// 	char c = 39;;
// 	if (cmd[0] == c && cmd[ft_strlen(cmd) - 1] == c && ft_counter(cmd , ' ') > 1)
// 		ft_printf("zsh: command not found: %s\n", ft_strtrim(cmd, "'"));
// 	else if (((cmd[0] < 'a' && cmd[0] > 'z') || (cmd[0] < 'A' && cmd[0] > 'Z')) && cmd[1] == '"')
// 		ft_printf("zsh: command not found: %s\n",cmd);
// }

// int	main(int argc, char **argv,char **envp)
// {
// 	(void)(envp);
// 	if (argc == 5)
// 	{
// 		check_param(argv[1], argv[2], argv[3], envp);
// 		execute_commands(argv[2], argv[3], argv[1], argv[4], envp);
// 	}
// 	else{
// 		ft_printf("zsh: parse error near `\\n' ");
// 	}return 0;
// }
//=>"Redirect the standard output to the writing end of the pipe" means that the standard output of a process is set to write its output into the writing end of a pipe (pipefd[1])