#include "pipex.h"

int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv; 
    char **arr = malloc(3) ;
    arr[0] = "ls";
    arr[1] = "-l";
    arr[2] = NULL;
    if (execve("/usr/bin/ls", arr , envp) == -1)
        perror("execve");
}