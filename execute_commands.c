/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shebaz <shebaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 23:07:09 by shebaz            #+#    #+#             */
/*   Updated: 2024/05/01 22:07:55 by shebaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void execute_cmd1(char *cmd ,char **envp, int fd_read, int fd_write, char *infile)
{
    char *command_path;
    /////make the second parameter
    int i = 0;
    char **arr = ft_split(cmd, ' ');
    while (arr[i])
        i++;
    char **new_arr = malloc(i + 1);
    i = 0;
    while (arr[i])
    {
        new_arr[i] = arr[i];
        i++;
    }
    new_arr[i] = NULL;

    command_path = ft_strjoin(get_path(cmd, envp), "/", arr[0]);
    printf("path = %s\n", command_path);
    close (fd_read);
    dup2 (fd_write , STDIN_FILENO);
    close (fd_write);
    int fd = open(infile,O_RDWR , 0777);
    if (fd == -1)
        perror("open");
    dup2(fd,STDOUT_FILENO);
    close(fd);
    if (execve(command_path, new_arr, envp) == -1)
        perror("execve 1");
}

void execute_cmd2(char *cmd ,char **envp, int fd_read, int fd_write, char *outfile)
{
    char *command_path;
    char **arr = ft_split(cmd, ' ');
    /////make the second parameter
    int i = 0;
    while (arr[i])
        i++;
    char **new_arr = malloc(i + 1);
    i = 0;
    while (arr[i])
    {
        new_arr[i] = arr[i];
        i++;
    }
    new_arr[i] = NULL;

    command_path = ft_strjoin(get_path(cmd, envp), "/", arr[0]);
    // printf("command_path = %s\n",command_path);
    close(fd_write);
    dup2(fd_read, STDIN_FILENO);
    close(fd_read);
    int fd = open(outfile,O_RDWR | O_TRUNC, 0777);
    if(fd == -1)
        perror("fd_cmd2");
    dup2(fd , STDOUT_FILENO);
    if(execve(command_path, new_arr , envp) == -1)
        perror("execve2");
}

void execute_commands(char **argv, char **envp ,char *full_path)
{
    (void)full_path;
    char *infile = argv[1];
    char *cmd1 = argv[2];
    char *cmd2 = argv[3];
    char *outfile = argv[4];
    int pipe_fd [2];
    if (pipe(pipe_fd) == -1)
    {
        perror("pipe");
        exit(1);
    }
    int pid = fork();
    if (pid == -1)
    {
        perror("fork");
        exit(1);
    }
    else if(pid == 0)
        execute_cmd1(cmd1, envp , pipe_fd[0],pipe_fd[1], infile);
    else 
    {
        int pid1 = fork();
        if (pid1 == 0)
            execute_cmd1(cmd2, envp, pipe_fd[0],pipe_fd[1], outfile);
        else if(pid1 == -1)
            perror("pid1");
        else
        {
            close(pipe_fd[0]);
            close(pipe_fd[1]);
            waitpid(pid, NULL, 0);
            waitpid(pid1, NULL, 0);
        }
    }
}

// Redirect stdout to the pipe : anything write to stdout will git into the pipe's buffer