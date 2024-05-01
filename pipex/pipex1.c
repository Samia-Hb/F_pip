/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shebaz <shebaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 16:35:00 by shebaz            #+#    #+#             */
/*   Updated: 2024/05/01 20:41:12 by shebaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


void execute_cmd1(int pipe_fd_0, int pipe_fd_1, char *cmd1, char *infile, char **envp)
{
	int		infile_fd;
	char	**new_arr;
    char	*command_path;
    (void)(pipe_fd_0);
    
    close(pipe_fd_0);
    dup2(pipe_fd_1, STDOUT_FILENO);// Redirect stdout to the pipe : anything write to stdout will git into the pipe's buffer
    close(pipe_fd_1);
    infile_fd = open(infile, O_RDONLY,0777);
    if (infile_fd == -1)
    {
        perror("zsh");
        exit(0);
    }
    dup2(infile_fd, STDIN_FILENO); // Redirect stdin to the input file
    close(infile_fd);
    new_arr = arr(cmd1);
    command_path = get_executable(new_arr[0], find_path(envp));
    execve(command_path,new_arr,envp);
    free(new_arr);
    exit(1);//get out of the process
}
void execute_cmd2(int pipe_fd_0,int pipe_fd_1,char *cmd2,char *outfile,char **envp)
{
    int outfile_fd;
    char **new_arr;
    char *command_path;

    close(pipe_fd_1);
    dup2(pipe_fd_0, STDIN_FILENO); // Redirect stdin to the pipe
    close(pipe_fd_0);
    outfile_fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0777);
    if (outfile_fd == -1)
        exit(1);
    dup2(outfile_fd, STDOUT_FILENO);
    close(outfile_fd);
    new_arr = arr(cmd2); 
    command_path = get_executable(new_arr[0], find_path(envp));
    execve(command_path, new_arr, envp);
    free(new_arr);
    exit(1);
}

void norm(int pipe_fd_0, int pipe_fd_1,int pid1,int pid2)
{
    close(pipe_fd_0);
    close(pipe_fd_1);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
}
void execute_commands(char *cmd1, char *cmd2, char *infile, char *outfile,char **envp)
{
    int pipefd[2];
    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        exit(1);
    }
    int pid1 = fork();
    if (pid1 == -1)
    {
        perror("fork");
        exit(1);
    }
    else if(pid1 == 0)
        execute_cmd1(pipefd[0], pipefd[1], cmd1, infile, envp); 
    else
    {
        int pid2 = fork();
        if (pid2 == -1) 
        {
            perror("fork");
            exit(1);
        }
        else if (pid2 == 0)
          execute_cmd2(pipefd[0],pipefd[1],cmd2,outfile,envp);
        else
            norm(pipefd[0],pipefd[1],pid1,pid2);
    }
}


