#ifndef PIPEX_H
#define PIPEX_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
// #include "libft/libft.h"

char    *get_full_path(char **envp);
char    *get_path(char *argv,char **envp);
int     get_executable(char *cmd, char *command_path);
void    check_argument(int argc, char **argv, char **envp);
int     ft_strncmp(char *s1, char *s2, int n);
char	*ft_strjoin(char *s1, char *s2, char *s3);
char	**ft_split(char *s, char c);
char	*ft_strdup(char *s1);
int     ft_strlen(char *str);
char	*ft_strtrim(char *s1, char *set);
void    execute_commands(char **argv, char **envp ,char *full_path);
#endif