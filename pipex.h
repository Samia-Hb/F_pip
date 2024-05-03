/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shebaz <shebaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 01:23:19 by shebaz            #+#    #+#             */
/*   Updated: 2024/05/03 16:27:46 by shebaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <stddef.h>
# include <sys/types.h>
# include <stddef.h>
# include <sys/stat.h>
# include "ft_printf/ft_printf.h"
# include "libft/libft.h"

char	*ft_strcpy(char *dest, char *src);
char	*ft_strcat(char *dest, char *src);
char    *get_executable(char *command, char *path);
char    *find_path(char **envp);
void    check_cmds(char **arr);
void    execute_commands(char *cmd1, char *cmd2, char *infile, char *outfile,char **envp);
char    **arr(char *cmd);
void    ft_clean (char **arr1, char **arr2);
#endif
